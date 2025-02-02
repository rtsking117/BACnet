#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Life Safety Operation
class LifeSafetyOperationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetCharacterStringType>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetObjectIDType, true>
	>
{

};
