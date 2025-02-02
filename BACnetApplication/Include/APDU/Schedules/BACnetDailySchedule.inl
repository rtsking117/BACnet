#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Schedules/BACnetTimeValue.inl>

//Daily Schedule
class BACnetDailySchedule : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetTimeValue>>
	>
{
public:

};
