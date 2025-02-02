#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Read Property
class ReadPropertyRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetEnumeratedType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>
	>
{
public:

	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool IsArrayIndexPresent()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if (IsArrayIndexPresent())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 Property)
	{
		get<1>().set(Property);
	}

	void SetArrayIndex(U32 Index)
	{
		make_present<2>(true);
		get<2>().set(Index);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}
};
