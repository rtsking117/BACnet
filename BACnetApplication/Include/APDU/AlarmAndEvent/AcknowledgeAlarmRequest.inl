#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetTimeStamp.inl>

//Acknowledge Alarm
class AcknowledgeAlarmRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetCharacterStringType>
	>
{
public:

};
