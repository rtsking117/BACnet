#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/AlarmAndEvent/BACnetRecipientProcess.inl>

//Get Enrollment Summary
class GetEnrollmentSummaryRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType>,
		BACnetSequenceElement<1, BACnetRecipientProcess, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType, true>,
		BACnetSequenceElement<3, BACnetEnumeratedType, true>,
		BACnetSequenceElement<4,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsigned8Type>,
				BACnetSequenceElement<1, BACnetUnsigned8Type>
			>, true
		>,
		BACnetSequenceElement<5, BACnetUnsignedType, true>
	>
{
public:

};
