#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Write File Ack
class WriteFileResponse : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetSignedType>,
		BACnetChoiceElement<1, BACnetSignedType>
	>
{
public:

	bool IsStreamBased()
	{
		return is_selected(0);
	}

	bool IsRecordBased()
	{
		return is_selected(1);
	}

	I32 GetNewStreamPosition()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<0>().get();
	}

	I32 GetNewRecordNumber()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get();
	}

	void SetNewStreamPosition(I32 NewPosition)
	{
		make_selected(0);
		get<0>().set(NewPosition);
	}

	void SetNewRecordNumber(I32 NewRecordNumber)
	{
		make_selected(1);
		get<1>().set(NewRecordNumber);
	}
};
