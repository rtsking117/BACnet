#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Propery Value
class BACnetPropertyValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>,
		BACnetSequenceElement<2, BACnetAnyType>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>
	>
{
public:
	BACnetPropertyValue() = default;
	BACnetPropertyValue(U32 Property, const BACnetValue& Value, U32 ArrayIndex = -1, U32 Priority = -1)
	{
		SetProperty(Property);
		if (ArrayIndex != -1)
		{
			SetArrayIndex(ArrayIndex);
		}
		else
		{
			ClearArrayIndex();
		}
		SetValue(Value);
		if (Priority != -1)
		{
			SetPriority(Priority);
		}
		else
		{
			ClearPriority();
		}
	}

	U32 GetProperty()
	{
		return get<0>().get();
	}

	bool HasIndex()
	{
		return is_present<1>();
	}

	U32 GetIndex()
	{
		return get<1>().get();
	}

	BACnetValue GetPropertyValue()
	{
		return get<2>().get();
	}

	bool HasPriority()
	{
		return is_present<3>();
	}

	U32 GetPriority()
	{
		return get<3>().get();
	}

	void SetProperty(U32 Property)
	{
		get<0>().set(Property);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<1>(true);
		get<1>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<1>(false);
	}

	void SetValue(const BACnetValue& Value)
	{
		get<2>().set(Value);
	}

	void SetPriority(U32 Priority)
	{
		make_present<3>(true);
		get<3>().set(Priority);
	}

	void ClearPriority()
	{
		make_present<3>(false);
	}
};
