#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/AlarmAndEvent/BACnetRecipient.inl>

//Event Notification Subscription
class BACnetEventNotificationSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipient>,
		BACnetSequenceElement<1, BACnetUnsigned32Type>,
		BACnetSequenceElement<2, BACnetBooleanType>,
		BACnetSequenceElement<3, BACnetUnsignedType>
	>
{
public:

};
