#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetTimeStamp.inl>
#include <APDU/AlarmAndEvent/BACnetNotificationParameters.inl>

//Confirmed Event Notification
class ConfirmedEventNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetUnsignedType>,
		BACnetSequenceElement<5, BACnetUnsigned8Type>,
		BACnetSequenceElement<6, BACnetEnumeratedType>,
		BACnetSequenceElement<7, BACnetCharacterStringType, true>,
		BACnetSequenceElement<8, BACnetEnumeratedType>,
		BACnetSequenceElement<9, BACnetBooleanType, true>,
		BACnetSequenceElement<10, BACnetEnumeratedType, true>,
		BACnetSequenceElement<11, BACnetEnumeratedType>,
		BACnetSequenceElement<12, BACnetNotificationParameters, true>
	>
{
public:


	bool HasMessageText()
	{
		return is_present<7>();
	}

	bool IsACKRequired()
	{
		return is_present<9>() && get<9>().get();
	}

	bool HasFromState()
	{
		return is_present<10>();
	}

	bool HasEventValues()
	{
		return is_present<12>();
	}

	BACnetNotificationParameters GetEventValues()
	{
		if(!HasEventValues())
		{
			__debugbreak();
		}
		return get<12>();
	}
};
