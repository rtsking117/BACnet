#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Lift Call Car State
class BACnetLiftCallCarState : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetUnsigned8Type>>
	>
{
public:

};
