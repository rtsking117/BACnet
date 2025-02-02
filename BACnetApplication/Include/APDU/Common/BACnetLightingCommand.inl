#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Lighting Command
class BACnetLightingCommand : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetLightingOperationType>,
		BACnetSequenceElement<1, BACnetRealValueType, true>,
		BACnetSequenceElement<2, BACnetRealValueType, true>,
		BACnetSequenceElement<3, BACnetRealValueType, true>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>,
		BACnetSequenceElement<5, BACnetUnsignedType, true>
	>
{
public:

};