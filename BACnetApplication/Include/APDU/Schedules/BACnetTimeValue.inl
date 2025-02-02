#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Time Value
class BACnetTimeValue : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetTimeType>,
		BACnetSequenceElement<NoTag, BACnetApplicationAnyType>
	>
{
public:

};
