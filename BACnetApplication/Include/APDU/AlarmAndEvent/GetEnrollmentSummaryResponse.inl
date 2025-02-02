#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Get Enrollement Summary Ack
class GetEnrollmentSummaryResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType, true>
	>
{
public:

};
