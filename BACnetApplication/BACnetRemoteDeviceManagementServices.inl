#pragma once 

#include "BACnetComplexTypes.inl"

//=============================================================================================
//						CONFIRMED REMOTE DEVICE MANAGEMENT SERVICES
//=============================================================================================

//Confirmed Private Transfer
class ConfirmedPrivateTransferRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>,
	BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:
	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	bool HasServiceParameters()
	{
		return is_present<2>();
	}

	BACnetValue GetServiceParameters()
	{
		if(HasServiceParameters())
		{
			return BACnetValue();
		}
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetServiceParameters(BACnetValue EncodedServiceParameters)
	{
		make_present<2>(true);
		get<2>().set(EncodedServiceParameters);
	}
};

//Confirmed Private Transfer Ack
class ConfirmedPrivateTransferResponse : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>,
	BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:
	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	bool HasResultParameters()
	{
		return is_present<2>();
	}

	BACnetValue GetResultParameters()
	{
		if(HasResultParameters())
		{
			return BACnetValue();
		}
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetResultParameters(BACnetValue EncodedServiceParameters)
	{
		make_present<2>(true);
		get<2>().set(EncodedServiceParameters);
	}
};

//Confirmed Text Message
class ConfirmedTextMessageRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0, BACnetUnsignedType>,
	BACnetChoiceElement<1, BACnetCharacterStringType>
	>
	, true>,
	BACnetSequenceElement<2, BACnetEnumeratedType, false>,
	BACnetSequenceElement<3, BACnetCharacterStringType, false>
	>
{
public:
	BACnetObjectID GetMessageSource()
	{
		return get<0>().get();
	}

	bool HasMessageClass()
	{
		return is_present<1>();
	}

	bool IsMessageClassNumeric()
	{
		if(!HasMessageClass())
		{
			return false;
		}
		return get<1>().is_selected(0);
	}

	bool IsMessageClassString()
	{
		if(!HasMessageClass())
		{
			return false;
		}
		return get<1>().is_selected(1);
	}

	U32 GetMessageClassID()
	{
		if(!IsMessageClassNumeric())
		{
			return 0;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetMessageClassString()
	{
		if(!IsMessageClassString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	U32 GetMessagePriority()
	{
		return get<2>().get();
	}

	BACnetString GetMessageText()
	{
		return get<3>().get();
	}

	void SetMessageSource(BACnetObjectID SourceObject)
	{
		get<0>().set(SourceObject);
	}

	void SetMessageClassID(U32 MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(0);
		get<1>().get<0>().set(MessageClass);
	}

	void SetMessageClassString(BACnetString MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(1);
		get<1>().get<1>().set(MessageClass);
	}

	void ClearMessageClass()
	{
		make_present<1>(false);
	}

	void SetMessagePriority(U32 Priority)
	{
		get<2>().set(Priority);
	}

	void SetMessageText(BACnetString MessageText)
	{
		get<3>().set(MessageText);
	}
};

//Device Communication Control
class DeviceCommunicationControlRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned16Type, true>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetCharacterStringType, true>
	>
{
public:
	bool HasTimeDuration()
	{
		return is_present<0>();
	}

	U16 GetTimeDuration()
	{
		if(!HasTimeDuration())
		{
			return 0;
		}
		return get<0>().get();
	}

	U32 GetEnableState()
	{
		return get<1>().get();
	}

	bool HasPassword()
	{
		return is_present<2>();
	}

	BACnetString GetPassword()
	{
		if(!HasPassword())
		{
			return BACnetString("");
		}
		return get<2>().get();
	}

	void SetTimeDuration(U16 TimeDuration)
	{
		make_present<0>(true);
		get<0>().set(TimeDuration);
	}

	void ClearTimeDuration()
	{
		make_present<0>(false);
	}

	void SetEnableState(U32 EnableState)
	{
		get<1>().set(EnableState);
	}

	void SetPassword(BACnetString Password)
	{
		make_present<2>(true);
		get<2>().set(Password);
	}

	void ClearPassword()
	{
		make_present<2>(false);
	}
};

//Reinitialize Device
class ReinitializeDeviceRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetEnumeratedType, false>,
	BACnetSequenceElement<1, BACnetCharacterStringType, true>
	>
{
public:
	U32 GetReinitializationState()
	{
		return get<0>().get();
	}

	bool HasPassword()
	{
		return is_present<1>();
	}

	BACnetString GetPassword()
	{
		if(!HasPassword())
		{
			return BACnetString("");
		}
		return get<1>().get();
	}

	void SetReinitalizationState(U32 ReinitializationState)
	{
		get<0>().set(ReinitializationState);
	}

	void SetPassword(BACnetString Password)
	{
		make_present<1>(true);
		get<1>().set(Password);
	}

	void ClearPassword()
	{
		make_present<1>(false);
	}
};

//=============================================================================================
//						UNCONFIRMED REMOTE DEVICE MANAGEMENT SERVICES
//=============================================================================================

//I Am
class IAmRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
	BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
	BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
	BACnetSequenceElement<NoTag, BACnetUnsigned16Type, false>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetMaxAPDUSize()
	{
		return get<1>().get();
	}

	BACnetSegmentation GetSegmentationSettings()
	{
		return (BACnetSegmentation)get<2>().get();
	}

	U16 GetVendorID()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ID)
	{
		get<0>().set(ID);
	}

	void SetMaxAPDUSize(U32 APDUSize)
	{
		get<1>().set(APDUSize);
	}

	void SetSegmentationSettings(BACnetSegmentation segmentation)
	{
		get<2>().set((U32)segmentation);
	}

	void SetVendorID(U16 VendorID)
	{
		get<3>().set(VendorID);
	}
};

//I Have
class IHaveRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
	BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
	BACnetSequenceElement<NoTag, BACnetCharacterStringType, false>
	>
{
public:

	BACnetObjectID GetDeviceID()
	{
		return get<0>().get();
	}

	BACnetObjectID GetObjectID()
	{
		return get<1>().get();
	}

	BACnetString GetCharString()
	{
		return get<2>().get();
	}

	void SetDeviceID(BACnetObjectID DeviceID)
	{
		get<0>().set(DeviceID);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<1>().set(ObjectID);
	}

	void SetCharStringID(BACnetString CharString)
	{
		get<2>().set(CharString);
	}
};

//Unconfirmed Private Transfer
class UnconfirmedPrivateTransferRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>,
	BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:

	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	BACnetValue GetServiceParameters()
	{
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetServiceParameters(const BACnetValue& ServiceParams)
	{
		get<2>().set(ServiceParams);
	}

};

//Unconfirmed Text Message
class UnconfirmedTextMessageRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0, BACnetUnsignedType>,
	BACnetChoiceElement<1, BACnetCharacterStringType>
	>, true>,
	BACnetSequenceElement<2, BACnetEnumeratedType, false>,
	BACnetSequenceElement<3, BACnetCharacterStringType, false>
	>
{
public:

	bool IsValid()
	{
		return !is_present<1>() || get<1>().IsValid();
	}

	BACnetObjectID GetSourceDevice()
	{
		return get<0>().get();
	}

	bool HasMessageClass()
	{
		return is_present<1>();
	}

	bool IsMessageClassNumeric()
	{
		return HasMessageClass() && get<1>().is_selected(0);
	}

	bool IsMessageClassString()
	{
		return HasMessageClass() && get<1>().is_selected(1);
	}

	U32 GetMessageClassID()
	{
		if(!IsMessageClassNumeric())
		{
			return 0;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetMessageClassString()
	{
		if(!IsMessageClassString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	U32 GetMessagePriority()
	{
		return get<2>().get();
	}

	BACnetString GetMessageText()
	{
		return get<3>().get();
	}

	void SetSourceDevice(BACnetObjectID SourceDevice)
	{
		get<0>().set(SourceDevice);
	}

	void SetMessageClassID(U32 MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(0);
		get<1>().get<0>().set(MessageClass);
	}

	void SetMessageClassString(BACnetString MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(1);
		get<1>().get<1>().set(MessageClass);
	}

	void ClearMessageClass()
	{
		make_present<1>(false);
	}

	void SetMessagePriority(U32 Priority)
	{
		get<2>().set(Priority);
	}

	void SetMessageText(const BACnetString& MessageText)
	{
		get<3>().set(MessageText);
	}
};

//Time Synchronization
class TimeSynchronizationRequest : public
	BACnetSequence<BACnetSequenceElement<NoTag, BACnetDateTimeType, false>>
{
	U32 GetDate()
	{
		return get<0>().GetDate();
	}

	U32 GetTime()
	{
		return get<0>().GetTime();
	}

	void SetDate(U32 Date)
	{
		get<0>().SetDate(Date);
	}

	void SetTime(U32 Time)
	{
		get<0>().SetTime(Time);
	}
};

//UTC Time Synchronization
class UTCTimeSynchronizationRequest : public
	BACnetSequence<BACnetSequenceElement<NoTag, BACnetDateTimeType, false>>
{
	U32 GetDate()
	{
		return get<0>().GetDate();
	}

	U32 GetTime()
	{
		return get<0>().GetTime();
	}

	void SetDate(U32 Date)
	{
		get<0>().SetDate(Date);
	}

	void SetTime(U32 Time)
	{
		get<0>().SetTime(Time);
	}
};

//Who Has
class WhoHasRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsignedType, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>
	>, true
	>,
	BACnetSequenceElement<NoTag,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<2, BACnetObjectIDType>,
	BACnetChoiceElement<3, BACnetCharacterStringType>
	>, false
	>
	>
{
public:

	bool HasLimits()
	{
		return is_present<0>();
	}

	U32 GetLowLimit()
	{
		if(!HasLimits())
		{
			return 0;
		}
		return get<0>().get<0>().get();
	}

	U32 GetHighLimit()
	{
		if(!HasLimits())
		{
			return 4194303;
		}
		return get<0>().get<1>().get();
	}

	bool IsObjectID()
	{
		return get<1>().is_selected(0);
	}

	bool IsObjectString()
	{
		return get<1>().is_selected(1);
	}

	BACnetObjectID GetObjectID()
	{
		if(!IsObjectID())
		{
			return InvalidObjectID;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetObjectString()
	{
		if(!IsObjectString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	void SetLimits(U32 LowLimit, U32 HighLimit)
	{
		make_present<0>(true);
		get<0>().get<0>().set(LowLimit);
		get<0>().get<1>().set(HighLimit);
	}

	void ClearLimits()
	{
		make_present<0>(false);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().set(ObjectID);
	}

	void SetObjectString(BACnetString ObjectString)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().set(ObjectString);
	}
};


//Who Is
class WhoIsRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsignedType, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>
	>, true
	>
	>
{
public:

	bool HasLimits()
	{
		return is_present<0>();
	}

	U32 GetLowLimit()
	{
		if(!HasLimits())
		{
			return 0;
		}
		return get<0>().get<0>().get();
	}

	U32 GetHighLimit()
	{
		if(!HasLimits())
		{
			return 4194303;
		}
		return get<0>().get<0>().get();
	}

	void SetLimits(U32 LowLimit = 0, U32 HighLimit = 4194303)
	{
		make_present<0>(true);
		get<0>().get<0>().set(LowLimit);
		get<0>().get<1>().set(HighLimit);
	}

	void RemoveLimits()
	{
		make_present<0>(false);
	}

};