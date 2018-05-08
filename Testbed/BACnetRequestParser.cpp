#include "BACnetRequestParser.h"
#include <BACnetAPDU.h>
#include <ASN1.h>

enum ConfirmedServiceChoice
{
	CS_AcknowledgeAlarm,
	CS_ConfirmedCOVNotification,
	CS_ConfirmedEventNotification,
	CS_GetAlarmSummary,
	CS_GetEnrollmentSummary,
	CS_SubscribeCOV,
	CS_AtomicReadFile,
	CS_AtomicWriteFile,
	CS_AddListElement,
	CS_RemoveListElement,
	CS_CreateObject,
	CS_DeleteObject,
	CS_ReadProperty,
	CS_ReadPropertyMultiple = 14,
	CS_WriteProperty,
	CS_WritePropertyMultiple,
	CS_DeviceCommunicationControl,
	CS_ConfirmedPrivateTransfer,
	CS_ConfirmedTextMessage,
	CS_ReinitializeDevice,
	CS_VTOpen,
	CS_VTClose,
	CS_VTData,
	CS_ReadRange = 26,
	CS_LifeSafetyOperation,
	CS_SubscribeCOVProperty,
	CS_GetEventInformation,
};

template<typename T>
BACnetResult DecodeRequest(CObjectPtr<IBACnetBuffer> buffer, T& RequestData)
{
	//static_assert(is_bacnet_template<T>::value == true, "T must be a BACnet Template.");
	BACnetValue v;
	BACnetResult r = ASN1::Decode(buffer, v);
	if(BCE_FAILED(r))
	{
		return r;
	}
	//if(DisplayCallbackFunction)DisplayCallbackFunction(tx->GetServiceChoice(), true, v);
	r = RequestData.Decode(v);
	if(BCE_FAILED(r))
	{
		return r;
	}
	if(!RequestData.IsValid())
	{
		return BCE_REJECT_MISSING_REQUIRED_PARAMETER;
	}
	return BC_OK;
}

#define DEFAULT_INIT_VALUE 32

template<typename T>
BACnetResult EncodeRequest(CObjectPtr<IBACnetBuffer>& buffer, T& RequestData)
{
	//static_assert(is_bacnet_template<T>::value == true, "T must be a BACnet Template.");
	BACnetValue vo(true);
	BACnetResult r = RequestData.Encode(vo);
	if(BCE_FAILED(r))
	{
		return r;
	}
	buffer = CreateBACnetBuffer(DEFAULT_INIT_VALUE);
	return ASN1::Encode(buffer, vo);
}

BACnetResult BACnetRequestParser::OnConfirmedRequest(CObjectPtr<IBACnetTransaction> tx)
{
	switch(tx->GetServiceChoice())
	{
	case CS_CreateObject:
		{
			CreateObjectRequest cor;
			BACnetResult r = DecodeRequest(tx->GetTransactionData(), cor);
			if(BCE_FAILED(r))
			{
				return tx->Reject((RejectCode)BCNRESULT_CODE(r));
			}


			//Set up an error.
			CreateObjectError coe;
			coe.SetError(ErrorClass::Object, ErrorCode::DynamicCreationNotSupported);
			//Encoding an error.
			CObjectPtr<IBACnetBuffer> buf;
			r = EncodeRequest(buf, coe);
			if(BCE_FAILED(r))
			{
				return tx->Reject(Reject_Other);
			}
			return tx->SendError(buf);
		}
	case CS_ReadProperty:
		{
			ReadPropertyRequest req;
			BACnetResult r = DecodeRequest(tx->GetTransactionData(), req);
			if(BCE_FAILED(r))
			{
				return tx->Reject((RejectCode)BCNRESULT_CODE(r));
			}
			BACnetError err;
			err.SetError(ErrorClass::Property, ErrorCode::UnknownProperty);
			CObjectPtr<IBACnetBuffer> buf;
			r = EncodeRequest(buf, err);
			if(BCE_FAILED(r))
			{
				tx->Reject(Reject_Other);
				return r;
			}
			return tx->SendError(buf);
		}
	case CS_ReadRange:
		{
			ReadRangeRequest req;
			BACnetResult r = DecodeRequest(tx->GetTransactionData(), req);
			if (BCE_FAILED(r))
			{
				return tx->Reject((RejectCode)BCNRESULT_CODE(r));
			}

		}
	default:
		return tx->Reject(Reject_UnrecognizedService);
	}
	return BC_OK;
}

enum UnconfirmedServiceChoice
{
	US_IAm,
	US_IHave,
	US_UnconfirmedCOVNotification,
	US_UnconfirmedEventNotification,
	US_UnconfirmedPrivateTransfer,
	US_UnconfirmedTextMessage,
	US_TimeSynchronization,
	US_WhoHas,
	US_WhoIs,
	US_UTCTimeSynchronization,
	US_WriteGroup,
};

BACnetResult BACnetRequestParser::OnUnconfirmedRequest(CObjectPtr<IBACnetNetworkAddress> src, U8 svc, CObjectPtr<IBACnetBuffer> msg)
{
	//parse the parameters contained within the Message block.
	BACnetValue v;
	BACnetResult r = ASN1::Decode(msg, v);
	if(BCE_FAILED(r))return r;
	if(DisplayCallbackFunction)DisplayCallbackFunction(svc, false, v);
	switch(svc)
	{
	case US_WhoIs:
		{
			WhoIsRequest wir;
			wir.Decode(v);
			if(GetInstanceIDFromObjectID(DeviceID) >= wir.GetLowLimit() &&
			   GetInstanceIDFromObjectID(DeviceID) <= wir.GetHighLimit())
			{
				IAmRequest iar;
				iar.SetObjectID(DeviceID);
				iar.SetMaxAPDUSize(1476);
				iar.SetSegmentationSettings(Segmentation_Both);
				iar.SetVendorID(10);
				BACnetValue vo(true);
				iar.Encode(vo);
				CObjectPtr<IBACnetBuffer> ret = CreateBACnetBuffer(16);
				r = ASN1::Encode(ret, vo);
				if(BCE_FAILED(r))
				{
					return r;
				}
				//broadcast the response on the local network.
				return tsm->SendUnconfirmedRequest(tsm->GetNetwork()->GetBroadcastAddress(src->GetNetworkID()), US_IAm, ret);
			}
		}
	default:
		break;
	}
	return BC_OK;
}

BACnetRequestParser::BACnetRequestParser() : DeviceID(CreateBACnetObjectID(8, 661540)), live(false)
{
}

BACnetRequestParser::~BACnetRequestParser()
{
}

BACnetResult BACnetRequestParser::Start()
{
	if(!tsm)
	{
		return BCE_NOT_INITIALIZED;
	}
	if(!live)
	{
		BACnetResult r = tsm->Start();
		if(BCE_FAILED(r)) return r;
		live = true;
	}
	return BC_OK;
}

BACnetResult BACnetRequestParser::Stop()
{
	if(live)
	{
		if(!tsm)
		{
			return BCE_NOT_INITIALIZED;
		}
		BACnetResult r = tsm->Stop();
		if(BCE_FAILED(r)) return r;
	}
	live = false;
	return BC_OK;
}

BACnetResult BACnetRequestParser::AttachTransactionManager(CObjectPtr<IBACnetTransactionManager> pTransactionManager)
{
	if(tsm)
	{
		DetachTransactionManager();
	}
	tsm = pTransactionManager;
	tsm->RegisterConfirmedRequestHandler([this](CObjectPtr<IBACnetTransaction> pTransaction) -> BACnetResult
	{
		return OnConfirmedRequest(pTransaction);
	});
	tsm->RegisterUnconfirmedRequestHandler([this](CObjectPtr<IBACnetNetworkAddress> pSource, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pData) -> BACnetResult
	{
		return OnUnconfirmedRequest(pSource,ServiceChoice,pData);
	});
	return BC_OK;
}

CObjectPtr<IBACnetTransactionManager> BACnetRequestParser::GetTransactionManager()
{
	return tsm;
}

BACnetResult BACnetRequestParser::DetachTransactionManager(void)
{
	if(!tsm)
	{
		return BCE_NOT_INITIALIZED;
	}
	Stop();
	tsm->RemoveConfirmedRequestHandler();
	tsm->RemoveUnconfirmedRequestHandler();
	tsm = nullptr;
	return BC_OK;
}

BACnetResult BACnetRequestParser::RegisterPreliminaryDisplayCallback(DisplayCallback pCallback)
{
	if(!pCallback)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(DisplayCallbackFunction)
	{
		return BCE_HANDLER_ALREADY_BOUND;
	}
	DisplayCallbackFunction = pCallback;
	return BC_OK;
}

CObjectPtr<BACnetRequestParser> CreateRequestParser()
{
	return CObjectPtr<BACnetRequestParser>(new BACnetRequestParser(), true);
}