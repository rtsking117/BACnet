#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Read Range Ack
class ReadRangeResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetEnumeratedType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetBitStringType>,
		BACnetSequenceElement<4, BACnetUnsignedType>,
		BACnetSequenceElement<5, BACnetSequenceOf<BACnetAnyType>>,
		BACnetSequenceElement<6, BACnetUnsigned32Type, true>
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

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if (!HasArrayIndex())
		{
			return InvalidIndex;
		}
		return get<2>().get();
	}

	BACnetBitString GetResultFlags()
	{
		return get<3>().get();
	}

	U32 GetItemCount()
	{
		return get<4>().get();
	}

	std::vector<BACnetValue> GetValues()
	{
		std::vector<BACnetValue> ret;
		for each(auto i in get<5>().get_list())
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	bool HasFirstSequenceNumber()
	{
		return is_present<6>();
	}

	U32 GetFirstSequenceNumber()
	{
		if (!HasFirstSequenceNumber())
		{
			return 0;
		}
		return get<6>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 PropertyID)
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

	void SetResultFlags(BACnetBitString ResultFlags)
	{
		get<3>().set(ResultFlags);
	}

	void SetItems(std::vector<BACnetValue> Items)
	{
		get<4>().set((U32)Items.size());
		get<5>().clear_list();
		for each(auto i in Items)
		{
			get<5>().add(BACnetAnyType(i));
		}
	}

	void AddItem(BACnetValue Item)
	{
		get<4>().set(get<4>().get() + 1);
		get<5>().add(BACnetAnyType(Item));
	}

	void AddItems(std::vector<BACnetValue> Items)
	{
		get<4>().set(get<4>().get() + (U32)Items.size());
		for each(auto i in Items)
		{
			get<5>().add(BACnetAnyType(i));
		}
	}

	void ClearItems()
	{
		get<4>().set(0);
		get<5>().clear_list();
	}

	void SetFirstSequenceNumber(U32 FirstSequenceNumber)
	{
		make_present<6>(true);
		get<6>().set(FirstSequenceNumber);
	}

	void ClearFirstSequenceNumber()
	{
		make_present<6>(false);
	}
};