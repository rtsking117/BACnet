#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Get Alarm Summary Ack
class GetAlarmSummaryResponse : public
	BACnetSequenceOf<
		BACnetSequence<
			BACnetSequenceElement<NoTag, BACnetObjectIDType>,
			BACnetSequenceElement<NoTag, BACnetEnumeratedType>,
			BACnetSequenceElement<NoTag, BACnetBitStringType>
		>
	>
{
public:

};
