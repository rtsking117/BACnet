#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Who Has
class WhoHasRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsignedType>
			>, true
		>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<2, BACnetObjectIDType>,
				BACnetChoiceElement<3, BACnetCharacterStringType>
			>
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
