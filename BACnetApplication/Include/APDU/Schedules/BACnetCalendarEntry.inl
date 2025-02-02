#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Schedules/BACnetDateRange.inl>
#include <APDU/Common/BACnetNamedTypes.inl>

//Calendar Entry
class BACnetCalendarEntry : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetDateType>,
		BACnetChoiceElement<1, BACnetDateRange>,
		BACnetChoiceElement<2, BACnetWeekAndDayType>
	>
{
public:

};
