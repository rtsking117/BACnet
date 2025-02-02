#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Who Is
class WhoIsRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsignedType>
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
