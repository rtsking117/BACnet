#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/AlarmAndEvent/BACnetLogData.inl>

//Log Multiple Record
class BACnetLogMultipleRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1, BACnetLogData>
	>
{
public:

};
