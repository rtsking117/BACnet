#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Reinitialize Device
class ReinitializeDeviceRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType>,
		BACnetSequenceElement<1, BACnetCharacterStringType, true>
	>
{
public:
	U32 GetReinitializationState()
	{
		return get<0>().get();
	}

	bool HasPassword()
	{
		return is_present<1>();
	}

	BACnetString GetPassword()
	{
		if(!HasPassword())
		{
			return BACnetString("");
		}
		return get<1>().get();
	}

	void SetReinitalizationState(U32 ReinitializationState)
	{
		get<0>().set(ReinitializationState);
	}

	void SetPassword(BACnetString Password)
	{
		make_present<1>(true);
		get<1>().set(Password);
	}

	void ClearPassword()
	{
		make_present<1>(false);
	}
};
