#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>

//Accumulator Record
class BACnetAccumulatorRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1, BACnetUnsignedType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetEnumeratedType>
	>
{
public:

};
