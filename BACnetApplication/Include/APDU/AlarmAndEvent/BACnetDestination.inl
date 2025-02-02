#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetNamedTypes.inl>
#include <APDU/AlarmAndEvent/BACnetRecipient.inl>

//Destination
class BACnetDestination : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetDaysOfWeekType>,
		BACnetSequenceElement<NoTag, BACnetTimeType>,
		BACnetSequenceElement<NoTag, BACnetTimeType>,
		BACnetSequenceElement<NoTag, BACnetRecipient>,
		BACnetSequenceElement<NoTag, BACnetUnsigned32Type>,
		BACnetSequenceElement<NoTag, BACnetBooleanType>,
		BACnetSequenceElement<NoTag, BACnetEventTransitionBits>
	>
{

};
