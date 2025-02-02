#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/AlarmAndEvent/BACnetRecipientProcess.inl>
#include <APDU/PropertyAccess/BACnetObjectPropertyReference.inl>

//COV Subscription
class BACnetCOVSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipientProcess>,
		BACnetSequenceElement<1, BACnetObjectPropertyReference>,
		BACnetSequenceElement<2, BACnetBooleanType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, BACnetRealValueType, true>
	>
{
public:

};
