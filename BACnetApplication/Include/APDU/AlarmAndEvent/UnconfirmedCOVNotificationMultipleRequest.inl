#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/AlarmAndEvent/BACnetCOVNotification.inl>

class UnconfirmedCOVNotificationMultipleRequest : public
	BACnetSequence <
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetDateTimeType, true>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetNotifyingDevice>>
	>
{
public:

};
