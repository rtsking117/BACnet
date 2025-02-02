#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Assigned Landing Calls
class BACnetAssignedLandingCalls : public 
	BACnetSequence<
		BACnetSequenceElement<0, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetUnsigned8Type>,
					BACnetSequenceElement<1, BACnetLiftCarDirectionType>
				>
			>
		>
	>
{
public:

};
