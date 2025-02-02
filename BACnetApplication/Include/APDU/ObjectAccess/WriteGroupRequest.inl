#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetGroupChannelValue.inl>

//Write Group
class WriteGroupRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetUnsignedType>,
		BACnetSequenceElement<2, BACnetSequenceOf<BACnetGroupChannelValue>>,
		BACnetSequenceElement<3, BACnetBooleanType, true>
	>
{
public:
	U32 GetGroupNumber()
	{
		return get<0>().get();
	}

	U32 GetWritePriority()
	{
		return get<1>().get();
	}

	std::vector<BACnetGroupChannelValue> GetChangeList()
	{
		return get<2>().get_list();
	}

	bool HasInhibitDelay()
	{
		return is_present<3>();
	}

	bool IsInhibitDelaySet()
	{
		if (!HasInhibitDelay())
		{
			return false;
		}
		return get<3>().get();
	}
};