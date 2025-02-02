#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Subscribe COV
class SubscribeCOVRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetBooleanType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>
	>
{
public:

};
