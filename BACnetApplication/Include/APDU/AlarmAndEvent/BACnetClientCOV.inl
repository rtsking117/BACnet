#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Client COV
class BACnetClientCOV : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetRealValueType>,
		BACnetChoiceElement<NoTag, BACnetNullType>
	>
{
public:

	bool UsesDefaultIncrement()
	{
		return is_selected(1);
	}

	bool UsesRealValueIncrement()
	{
		return is_selected(0);
	}

	float GetRealValueIncrement()
	{
		if(!UsesRealValueIncrement())
		{
			return 0.0f;
		}
		return get<0>().get();
	}

	void SetDefaultIncrement()
	{
		make_selected(1);
		get<1>().set();
	}

	void SetRealValueIncrement(float IncrementValue)
	{
		make_selected(0);
		get<0>().set(IncrementValue);
	}
};
