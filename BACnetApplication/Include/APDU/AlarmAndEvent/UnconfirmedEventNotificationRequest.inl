#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Common/BACnetTimeStamp.inl>
#include <APDU/AlarmAndEvent/BACnetNotificationParameters.inl>

class UnconfirmedEventNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetUnsignedType>,
		BACnetSequenceElement<5, BACnetUnsigned8Type>,
		BACnetSequenceElement<6, BACnetEventTypeType>,
		BACnetSequenceElement<7, BACnetCharacterStringType, true>,
		BACnetSequenceElement<8, BACnetNotifyTypeType>,
		BACnetSequenceElement<9, BACnetBooleanType, true>,
		BACnetSequenceElement<10, BACnetEventStateType, true>,
		BACnetSequenceElement<11, BACnetEventStateType>,
		BACnetSequenceElement<12, BACnetNotificationParameters, true>
	>
{
public:

};
