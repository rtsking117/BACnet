#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Date Time
class BACnetDateTimeType : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetDateType>,
		BACnetSequenceElement<NoTag, BACnetTimeType>
	>
{
public:
	U32 GetDate()
	{
		return get<0>().get();
	}

	U32 GetTime()
	{
		return get<1>().get();
	}

	void SetDate(U32 Date)
	{
		get<0>().set(Date);
	}

	void SetTime(U32 Time)
	{
		get<1>().set(Time);
	}
};
