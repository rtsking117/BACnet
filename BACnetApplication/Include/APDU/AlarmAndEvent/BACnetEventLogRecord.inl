#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetNamedTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/AlarmAndEvent/ConfirmedEventNotificationRequest.inl>

//Event Log Record
class BACnetEventLogRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetLogStatusType>,
				BACnetChoiceElement<1, ConfirmedEventNotificationRequest>,
				BACnetChoiceElement<2, BACnetRealValueType>
			>
		>
	>
{
public:

};
