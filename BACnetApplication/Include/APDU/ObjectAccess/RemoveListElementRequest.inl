#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Remove List Element
class RemoveListElementRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetEnumeratedType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetPropertyID()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if (!HasArrayIndex())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	BACnetValue GetElementValue()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetPropertyID(U32 PropertyID)
	{
		get<1>().set(PropertyID);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<2>(true);
		get<2>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetElementValue(const BACnetValue& Value)
	{
		get<3>().set(Value);
	}
};
