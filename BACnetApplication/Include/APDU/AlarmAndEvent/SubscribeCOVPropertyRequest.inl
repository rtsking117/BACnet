#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPropertyReference.inl>

//Subscribe COV Property
class SubscribeCOVPropertyRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetBooleanType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetPropertyReference>,
		BACnetSequenceElement<5, BACnetRealValueType, true>
	>
{
public:

};
