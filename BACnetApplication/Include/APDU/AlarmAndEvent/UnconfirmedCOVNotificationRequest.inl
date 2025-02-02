#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPropertyValue.inl>

class UnconfirmedCOVNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetPropertyValue>>
	>
{
public:

};
