#include "SegmentAssembler.h"
#include "ServerTransaction.h"
#include "ClientTransaction.h"

U8 CSegmentAssembler::GetNextInstanceID()
{
	U8 ret = LastInstanceID++;
	if(LastInstanceID == 0)
	{
		++LastInstanceID;
	}
	return ret;
}

BACnetResult CSegmentAssembler::ProcessAPDU(CObjectPtr<IBACnetNetworkAddress> pAddr, CObjectPtr<IBACnetBuffer> msg)
{
	U8 PDUType;
	if(msg->GetRemainingSize() < 2)
	{
		return BCE_NOT_ENOUGH_DATA;
	}
	msg->ReadByte(PDUType);
	switch((PDUType & 0xF0) >> 4)
	{
	case PDUType_ConfirmedRequest:
		{
			if(msg->GetRemainingSize() < 3)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			 //pull all data from it.
			U8 extra=0, invokeid=0, sequencenum=0, proposedsize=0, service=0;
			msg->ReadByte(extra);
			msg->ReadByte(invokeid);
			if(PDUType & PDUFlag_IsSegmented)
			{
				if(msg->GetRemainingSize() < 3)
				{
					return BCE_NOT_ENOUGH_DATA;
				}
				msg->ReadByte(sequencenum);
				msg->ReadByte(proposedsize);
			}
			msg->ReadByte(service);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx == nullptr)
			{
				//create a new Server Transaction.
				trx = CreateServerTransaction(invokeid, pAddr);
			}
			return trx->OnConfirmedRequest(PDUType, extra, sequencenum, proposedsize, service, msg);
		}
	case PDUType_UnconfirmedRequest:
		{
			//pull the data.
			U8 service = 0;
			msg->ReadByte(service);
			return OnUnconfirmedRequest(pAddr, service, msg);
		}
	case PDUType_SimpleAck:
		{
			//pull the data.
			if(msg->GetRemainingSize() < 2)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			U8 invokeid = 0, service = 0;
			msg->ReadByte(invokeid);
			msg->ReadByte(service);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx != nullptr)
			{
				return trx->OnSimpleAck();
			}
			//drop it.
			return BC_OK;
		}
	case PDUType_ComplexAck:
		{
			U8 invokeid = 0, sequencenum = 0, proposedsize = 0, service = 0;
			if(msg->GetRemainingSize() < 3)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			msg->ReadByte(invokeid);
			if(PDUType & PDUFlag_IsSegmented)
			{
				if(msg->GetRemainingSize() < 4)
				{
					return BCE_NOT_ENOUGH_DATA;
				}
				msg->ReadByte(sequencenum);
				msg->ReadByte(proposedsize);
			}
			msg->ReadByte(service);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx != nullptr)
			{
				return trx->OnComplexAck(PDUType,sequencenum,proposedsize,msg);
			}
			//drop it.
			return BC_OK;
		}
	case PDUType_SegmentAck:
		{
			if(msg->GetRemainingSize() < 3)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			U8 invokeid = 0, sequencenum = 0, proposedsize = 0;
			msg->ReadByte(invokeid);
			msg->ReadByte(sequencenum);
			msg->ReadByte(proposedsize);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx != nullptr)
			{
				return trx->OnSegmentAck(PDUType, sequencenum, proposedsize);
			}
			//drop it.
			return BC_OK;
		}
	case PDUType_Error:
		{
			if(msg->GetRemainingSize() < 2)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			U8 invokeid = 0, service = 0;
			msg->ReadByte(invokeid);
			msg->ReadByte(service);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx != nullptr)
			{
				return trx->OnError(msg);
			}
			//drop it.
			return BC_OK;
		}
	case PDUType_Abort:
		{
			if(msg->GetRemainingSize() < 2)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			U8 invokeid = 0, reason = 0;
			msg->ReadByte(invokeid);
			msg->ReadByte(reason);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx != nullptr)
			{
				return trx->OnAbort(PDUType & PDUFlag_IsServer, (AbortCode)reason);
			}
			//drop it.
			return BC_OK;
		}
	case PDUType_Reject:
		{
			if(msg->GetRemainingSize() < 2)
			{
				return BCE_NOT_ENOUGH_DATA;
			}
			U8 invokeid = 0, reason = 0;
			msg->ReadByte(invokeid);
			msg->ReadByte(reason);
			auto trx = activetrx->Find(invokeid, pAddr);
			if(trx != nullptr)
			{
				return trx->OnReject((RejectCode)reason);
			}
			//drop it.
			return BC_OK;
		}
		BACNET_UNREACHABLECASE;
	}
}

CObjectPtr<CTransaction> CSegmentAssembler::CreateServerTransaction(U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pDest)
{
	CObjectPtr<CServerTransaction> ret = CObjectPtr<CServerTransaction>(new CServerTransaction(CObjectPtr<CSegmentAssembler>(this), InvokeID, pDest), true);
	activetrx->Add(ret);
	ret->StartServerTSM();
	return ret;
}

CObjectPtr<CTransaction> CSegmentAssembler::CreateClientTransaction(U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pDest, U8 ServiceChoice, MaxAPDU MaxAPDUSize, CObjectPtr<IBACnetBuffer> tx)
{
	CObjectPtr<CClientTransaction> ret = CObjectPtr<CClientTransaction>(new CClientTransaction(CObjectPtr<CSegmentAssembler>(this),InvokeID, pDest), true);
	activetrx->Add(ret);
	ret->StartClientTSM(ServiceChoice, MaxAPDUSize, tx);
	return ret;
}

CSegmentAssembler::CSegmentAssembler(U16 MaxSegs) : 
	live(false),
	activetrx(new TransactionSet(), true),
	OnConfirmedRequest(nullptr),
	OnUnconfirmedRequest(nullptr),
	LastInstanceID(1)
{
	//compute the maximum number of segments available to send.
	if(!MaxSegs)
	{
		MaxSegmentsAllowed = MaxSeg_Infinite;
	}
	U32 index = Log2(MaxSegs);
	if(index > MaxSeg_64)
	{
		MaxSegmentsAllowed = MaxSeg_Infinite;
	}
	MaxSegmentsAllowed = (MaxSegments)index;

}


CSegmentAssembler::~CSegmentAssembler()
{
	Stop();
}

BACnetResult CSegmentAssembler::Start()
{
	if(!net ||
	   OnConfirmedRequest == nullptr ||
	   OnUnconfirmedRequest == nullptr)
	{
		return BCE_NOT_INITIALIZED;
	}
	if(!live)
	{
		net->Start();
		live = true;
	}
	return BC_OK;
}

BACnetResult CSegmentAssembler::Stop()
{
	if(!net)
	{
		return BCE_NOT_INITIALIZED;
	}
	if(live)
	{
		net->Stop();
	}
	live = false;
	return BC_OK;
}

BACnetResult CSegmentAssembler::AttachNetwork(CObjectPtr<IBACnetNetwork> pNetwork)
{
	bool t = live;
	if(net)
	{
		DetachNetwork();
	}
	net = pNetwork;
	pNetwork->RegisterAPDUHandler([this](CObjectPtr<IBACnetNetworkAddress> addr, CObjectPtr<IBACnetBuffer> buf) -> BACnetResult
	{
		return ProcessAPDU(addr, buf);
	});
	if(t)
	{
		Start();
	}
	return BC_OK;
}

CObjectPtr<IBACnetNetwork> CSegmentAssembler::GetNetwork() const
{
	return net;
}

BACnetResult CSegmentAssembler::DetachNetwork()
{
	Stop();
	net->RemoveAPDUHandler();
	net = nullptr;
	return BC_OK;
}

BACnetResult CSegmentAssembler::RegisterConfirmedRequestHandler(ConfirmedRequestHandler pHandler)
{
	if(!pHandler)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(OnConfirmedRequest)
	{
		return BCE_HANDLER_ALREADY_BOUND;
	}
	OnConfirmedRequest = pHandler;
	return BC_OK;
}

BACnetResult CSegmentAssembler::RemoveConfirmedRequestHandler()
{
	if(OnConfirmedRequest)
	{
		Stop();
		OnConfirmedRequest = nullptr;
	}
	return BC_OK;
}

BACnetResult CSegmentAssembler::RegisterUnconfirmedRequestHandler(UnconfirmedRequestHandler pHandler)
{
	if(!pHandler)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(OnUnconfirmedRequest)
	{
		return BCE_HANDLER_ALREADY_BOUND;
	}
	OnUnconfirmedRequest = pHandler;
	return BC_OK;
}

BACnetResult CSegmentAssembler::RemoveUnconfirmedRequestHandler()
{
	if(OnUnconfirmedRequest)
	{
		Stop();
		OnUnconfirmedRequest = nullptr;
	}
	return BC_OK;
}

BACnetResult CSegmentAssembler::SendConfirmedRequest(CObjectPtr<IBACnetNetworkAddress> pDestination, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pMessage, CObjectPtr<IBACnetTransaction>& pTransaction)
{
	//assume the receiving device can take all segments.
	U32 masz = net->GetMaxAPDUSize(pDestination);
	U8 i = Log2(masz);
	if(i == -1)
	{
		return BCE_ABORT_BUFFER_OVERFLOW;
	}
	MaxAPDU sz = (MaxAPDU)i;
	auto ret = CreateClientTransaction(GetNextInstanceID(), pDestination, ServiceChoice, sz, pMessage);
	if(!ret)
	{
		return BCE_CANNOT_CREATE_TSM;
	}
	if(BCE_FAILED(ret->GetTransactionResult()))
	{
		return ret->GetTransactionResult();
	}
	pTransaction = ret;
	return BC_OK;
}

BACnetResult CSegmentAssembler::SendUnconfirmedRequest(CObjectPtr<IBACnetNetworkAddress> pDestination, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pMessage) const
{
	if(net->GetMaxAPDUSize(pDestination) < (pMessage->GetSize() + 2))
	{
		return BCE_BUFFER_OVERFLOW;
	}
	U8 tmp[2] = {
		(PDUType_UnconfirmedRequest << 4),
		ServiceChoice,
	};
	CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
	CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(tmp), tmp);
	tx->Push(pMessage);
	tx->Push(buf);
	return net->WriteAPDU(pDestination, tx, Message_PriorityNormal | Message_WaitForTransmit);
}

BACnetResult CSegmentAssembler::RemoveTransaction(CObjectPtr<CTransaction> trx)
{
	activetrx->Remove(trx);
	return BC_OK;
}
