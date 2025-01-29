#pragma once

#include "BACnetBasicTypes.inl"

//Date Range
class BACnetDateRange : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetDateType, false>,
		BACnetSequenceElement<NoTag, BACnetDateType, false>
	>
{
public:

};

//Calendar Entry
class BACnetCalendarEntry : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetDateType>,
		BACnetChoiceElement<1, BACnetDateRange>,
		BACnetChoiceElement<2, BACnetWeekNDayType>
	>
{
public:

};

//Daily Schedule
class BACnetDailySchedule : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetTimeValue>, false>
	>
{
public:

};

//Special Event
class BACnetSpecialEvent : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, 
			BACnetChoice<NoDefault, 
				BACnetChoiceElement<0, BACnetCalendarEntry>,
				BACnetChoiceElement<1, BACnetObjectIDType>
			>, false
		>,
		BACnetSequenceElement<2, BACnetSequenceOf<BACnetTimeValue>, false>,
		BACnetSequenceElement<3, BACnetUnsignedType>
	>
{
public:

};

//Time Value
class BACnetTimeValue : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetTimeType, false>,
		BACnetSequenceElement<NoTag, BACnetApplicationAnyType, false>
	>
{
public:

};
