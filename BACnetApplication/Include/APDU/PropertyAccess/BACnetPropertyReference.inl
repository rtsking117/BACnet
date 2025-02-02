#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Property Reference
class BACnetPropertyReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>
	>
{
public:
	BACnetPropertyReference() = default;
	BACnetPropertyReference(U32 Property, U32 ArrayIndex = -1)
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
	}

	U32 GetProperty()
	{
		return get<0>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<1>();
	}

	U32 GetArrayIndex()
	{
		if (!HasArrayIndex())
		{
			return (U32)-1;
		}
		return get<1>().get();
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

};
