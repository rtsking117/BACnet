#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Device Communication Control
class DeviceCommunicationControlRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type, true>,
		BACnetSequenceElement<1, BACnetEnumeratedType>,
		BACnetSequenceElement<2, BACnetCharacterStringType, true>
	>
{
public:
	bool HasTimeDuration()
	{
		return is_present<0>();
	}

	U16 GetTimeDuration()
	{
		if(!HasTimeDuration())
		{
			return 0;
		}
		return get<0>().get();
	}

	U32 GetEnableState()
	{
		return get<1>().get();
	}

	bool HasPassword()
	{
		return is_present<2>();
	}

	BACnetString GetPassword()
	{
		if(!HasPassword())
		{
			return BACnetString("");
		}
		return get<2>().get();
	}

	void SetTimeDuration(U16 TimeDuration)
	{
		make_present<0>(true);
		get<0>().set(TimeDuration);
	}

	void ClearTimeDuration()
	{
		make_present<0>(false);
	}

	void SetEnableState(U32 EnableState)
	{
		get<1>().set(EnableState);
	}

	void SetPassword(BACnetString Password)
	{
		make_present<2>(true);
		get<2>().set(Password);
	}

	void ClearPassword()
	{
		make_present<2>(false);
	}
};
