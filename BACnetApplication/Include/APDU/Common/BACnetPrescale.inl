#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Prescale
class BACnetPrescale : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsignedType>,
		BACnetSequenceElement<1, BACnetUnsignedType>
	>
{
public:

};
