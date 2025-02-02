#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//VT Data Ack
class VTDataResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetBooleanType>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>
	>
{
public:
	bool IsValid()
	{
		if(WasAllDataAccepted())
		{
			return !HasAcceptedOctetCount();
		}
		return HasAcceptedOctetCount();
	}

	bool WasAllDataAccepted()
	{
		return get<0>().get();
	}

	bool HasAcceptedOctetCount()
	{
		return is_present<1>();
	}

	U32 GetAcceptedOctetCount()
	{
		if(!HasAcceptedOctetCount())
		{
			return (U32)-1;
		}
		return get<1>().get();
	}

	void SetAllDataAcceptedFlag(bool WasAllDataAccepted)
	{
		get<0>().set(WasAllDataAccepted);
		if(WasAllDataAccepted)
		{
			make_present<1>(false);
		}
	}

	void SetAcceptedOctetCount(U32 AcceptedOctetCount)
	{
		get<0>().set(false);
		make_present<1>(true);
		get<1>().set(AcceptedOctetCount);
	}
};
