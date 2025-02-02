#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>

//Time Stamp
class BACnetTimeStamp : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetTimeType>,
		BACnetSequenceElement<1, BACnetUnsigned16Type>,
		BACnetSequenceElement<2, BACnetDateTimeType>
	>
{
public:

};