#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Write Property
class WritePropertyRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetEnumeratedType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>
	>
{
public:
	BACnetObjectID GetObject()
	{
		return get<0>().get();
	}
	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if (HasArrayIndex())
		{
			return get<2>().get();
		}
		return (U32)-1;
	}

	BACnetValue GetPropertyValue()
	{
		return get<3>().get();
	}

	bool HasPriority()
	{
		return is_present<4>();
	}

	U32 GetPriority()
	{
		if (HasPriority())
		{
			return get<4>().get();
		}
		return (U32)-1;
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

	void SetPropertyValue(const BACnetValue& v)
	{
		get<3>().set(v);
	}

	void SetPriority(U32 Priority)
	{
		make_present<4>(true);
		get<4>().set(Priority);
	}

	void ClearPriority()
	{
		make_present<4>(false);
	}

};
