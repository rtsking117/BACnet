#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Router Entry
class BACnetRouterEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type>,
		BACnetSequenceElement<1, BACnetOctetStringType>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetUnsigned8Type, true>
	>
{
public:

};
