#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Landing Door Status
class BACnetLandingDoorStatus : public
	BACnetSequence<
		BACnetSequenceElement<0,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetUnsigned8Type>,
					BACnetSequenceElement<1, BACnetDoorStatusType>
				>
			>
		>
	>
{
public:

};
