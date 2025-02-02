#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Date Range
class BACnetDateRange : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetDateType>,
		BACnetSequenceElement<NoTag, BACnetDateType>
	>
{
public:

};