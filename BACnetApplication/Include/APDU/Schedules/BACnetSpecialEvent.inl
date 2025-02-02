#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Schedules/BACnetCalendarEntry.inl>
#include <APDU/Schedules/BACnetTimeValue.inl>

//Special Event
class BACnetSpecialEvent : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, 
			BACnetChoice<NoDefault, 
				BACnetChoiceElement<0, BACnetCalendarEntry>,
				BACnetChoiceElement<1, BACnetObjectIDType>
			>
		>,
		BACnetSequenceElement<2, BACnetSequenceOf<BACnetTimeValue>>,
		BACnetSequenceElement<3, BACnetUnsignedType>
	>
{
public:

};
