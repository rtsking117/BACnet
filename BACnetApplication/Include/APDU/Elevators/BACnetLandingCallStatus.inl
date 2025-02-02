#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Landing Call Status
class BACnetLandingCallStatus : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type>,
		BACnetSequenceElement<NoTag, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<1, BACnetLiftCarDirectionType>,
				BACnetChoiceElement<2, BACnetUnsigned8Type>
			>
		>,
		BACnetSequenceElement<3, BACnetCharacterStringType, true>
	>
{
public:

};
