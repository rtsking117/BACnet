#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>

//UTC Time Synchronization
class UTCTimeSynchronizationRequest : public
	BACnetSequence<BACnetSequenceElement<NoTag, BACnetDateTimeType>>
{
	U32 GetDate()
	{
		return get<0>().GetDate();
	}

	U32 GetTime()
	{
		return get<0>().GetTime();
	}

	void SetDate(U32 Date)
	{
		get<0>().SetDate(Date);
	}

	void SetTime(U32 Time)
	{
		get<0>().SetTime(Time);
	}
};
