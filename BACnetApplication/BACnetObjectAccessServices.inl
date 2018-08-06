#pragma once

#include "BACnetComplexTypes.inl"


//=============================================================================================
//							CONFIRMED OBJECT ACCESS SERVICES
//=============================================================================================

//Add List Element
class AddListElementRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<3, BACnetAnyType, false>
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
		if(!HasArrayIndex())
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

	void SetElementValue(const BACnetValue & Value)
	{
		get<3>().set(Value);
	}
};

//Create Object
class CreateObjectRequest : public
	BACnetSequence<
	BACnetSequenceElement<0,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0, BACnetEnumeratedType>,
	BACnetChoiceElement<1, BACnetObjectIDType>
	>, false
	>,
	BACnetSequenceElement<1,
	BACnetSequenceOf<BACnetPropertyValue>
	, true>
	>
{
public:
	bool IsObjectType()
	{
		return get<0>().is_selected(0);
	}

	U32 GetObjectType()
	{
		if(!IsObjectType())
		{
			return 0;
		}
		return get<0>().get<0>().get();
	}

	bool IsObjectID()
	{
		return get<0>().is_selected(1);
	}

	BACnetObjectID GetObjectID()
	{
		if(!IsObjectID())
		{
			return 0;
		}
		return get<0>().get<1>().get();
	}

	bool HasInitialValues()
	{
		return is_present<1>();
	}

	std::vector<BACnetPropertyValue> GetInitialValueList()
	{
		if(!HasInitialValues())
		{
			return {};
		}
		return get<1>().get_list();
	}

	void SetObjectType(U32 ObjectType)
	{
		get<0>().make_selected(0);
		get<0>().get<0>().set(ObjectType);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().make_selected(1);
		get<0>().get<1>().set(ObjectID);
	}

	void SetInitialValueList(std::vector<BACnetPropertyValue> InitialValueList)
	{
		make_present<1>(true);
		get<1>().set_list(InitialValueList);
	}

	void ClearInitialValueList()
	{
		make_present<1>(false);
	}
};

//Create Object Ack
class CreateObjectResponse : public
	BACnetObjectIDType
{
public:

	BACnetObjectID GetObjectID()
	{
		return get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		set(ObjectID);
	}
};

//Delete Object
class DeleteObjectRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetObjectIDType, false>
	>
{
public:
	BACnetObjectID GetObject()
	{
		return get<0>().get();
	}

	void SetObject(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}
};

//Read Property
class ReadPropertyRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
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
		if(IsArrayIndexPresent())
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

//Read Property Ack
class ReadPropertyResponse : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<3, BACnetAnyType, false>
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
		if(IsArrayIndexPresent())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	BACnetValue GetPropertyValue()
	{
		return get<3>().get();
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
};

//Read Property Multiple
class ReadPropertyMultipleRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetSequenceOf<ReadAccessSpecification>, false>
	>
{
public:

	ReadAccessSpecification GetReadForObject(U32 Index)
	{
		return get<0>().get(Index);
	}

	std::vector<ReadAccessSpecification> GetReads()
	{
		return get<0>().get_list();
	}

	void ClearAllReads()
	{
		get<0>().clear_list();
	}

	void AddReadForObject(ReadAccessSpecification PropertyRead)
	{
		get<0>().add(PropertyRead);
	}

	void AddReads(std::vector<ReadAccessSpecification> PropertyReads)
	{
		get<0>().add_list(PropertyReads);
	}

	void SetReads(std::vector<ReadAccessSpecification> PropertyReads)
	{
		get<0>().set_list(PropertyReads);
	}
};

//Read Property Multiple Ack
class ReadPropertyMultipleResponse : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetSequenceOf<ReadAccessResult>, false>
	>
{
public:
	ReadAccessResult GetReadForObject(U32 Index)
	{
		return get<0>().get(Index);
	}

	std::vector<ReadAccessResult> GetReads()
	{
		return get<0>().get_list();
	}

	void ClearAllReads()
	{
		get<0>().clear_list();
	}

	void AddReadForObject(ReadAccessResult PropertyRead)
	{
		get<0>().add(PropertyRead);
	}

	void AddReads(std::vector<ReadAccessResult> PropertyReads)
	{
		get<0>().add_list(PropertyReads);
	}

	void SetReads(std::vector<ReadAccessResult> PropertyReads)
	{
		get<0>().set_list(PropertyReads);
	}
};

//Read Range
class ReadRangeRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<NoTag,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<3,
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
	BACnetSequenceElement<NoTag, BACnetSigned16Type, false>
	>
	>,
	BACnetChoiceElement<6,
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
	BACnetSequenceElement<NoTag, BACnetSigned16Type, false>
	>
	>,
	BACnetChoiceElement<7,
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetDateTimeType, false>,
	BACnetSequenceElement<NoTag, BACnetSigned16Type, false>
	>
	>
	>, true
	>
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
		if(HasArrayIndex())
		{
			return InvalidIndex;
		}
		return get<2>().get();
	}

	bool HasRange()
	{
		return is_present<3>();
	}

	bool IsRangePosition()
	{
		return HasRange() && get<3>().is_selected(0);
	}

	U32 GetReferenceIndex()
	{
		if(!IsRangePosition())
		{
			return 0;
		}
		return get<3>().get<0>().get<0>().get();
	}

	bool IsRangeSequenceNumber()
	{
		return HasRange() && get<3>().is_selected(1);
	}

	U32 GetReferenceSequenceNumber()
	{
		if(!IsRangeSequenceNumber())
		{
			return 0;
		}
		return get<3>().get<1>().get<0>().get();
	}

	bool IsRangeTime()
	{
		return HasRange() && get<3>().is_selected(2);
	}

	BACnetDateTimeType GetReferenceTime()
	{
		if(!IsRangeTime())
		{
			return BACnetDateTimeType();
		}
		return get<3>().get<2>().get<0>();
	}

	I16 GetCount()
	{
		if(IsRangePosition())
		{
			return get<3>().get<0>().get<1>().get();
		}
		else if(IsRangeSequenceNumber())
		{
			return get<3>().get<1>().get<1>().get();
		}
		else if(IsRangeTime())
		{
			return get<3>().get<2>().get<1>().get();
		}
		else
		{
			return 0;
		}
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

	void SetPositionRange(U32 StartIndex, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(0);
		get<3>().get<0>().get<0>().set(StartIndex);
		get<3>().get<0>().get<1>().set(Count);
	}

	void SetSequenceNumberRange(U32 StartSequenceNumber, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(1);
		get<3>().get<1>().get<0>().set(StartSequenceNumber);
		get<3>().get<1>().get<1>().set(Count);
	}

	void SetTimeRange(BACnetDateTimeType StartTime, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(2);
		get<3>().get<2>().get<0>() = StartTime;
		get<3>().get<2>().get<1>().set(Count);
	}

	void ClearRange()
	{
		make_present<3>(false);
	}
};

//Read Range Ack
class ReadRangeResponse : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<3, BACnetBitStringType, false>,
	BACnetSequenceElement<4, BACnetUnsignedType, false>,
	BACnetSequenceElement<5,
	BACnetSequenceOf<BACnetAnyType>,
	false>,
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
		if(!HasArrayIndex())
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
		if(!HasFirstSequenceNumber())
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

//Remove List Element
class RemoveListElementRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<3, BACnetAnyType, false>
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
		if(!HasArrayIndex())
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

	void SetElementValue(const BACnetValue & Value)
	{
		get<3>().set(Value);
	}
};

//Write Property
class WritePropertyRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetEnumeratedType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<3, BACnetAnyType, false>,
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
		if(HasArrayIndex())
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
		if(HasPriority())
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

//Write Property Multiple
class WritePropertyMultipleRequest : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetSequenceOf<WriteAccessSpecification>, false>
	>
{
public:

	WriteAccessSpecification GetWriteForObject(U32 Index)
	{
		return get<0>().get(Index);
	}

	std::vector<WriteAccessSpecification> GetWrites()
	{
		return get<0>().get_list();
	}

	void ClearAllWrites()
	{
		get<0>().clear_list();
	}

	void AddWriteForObject(WriteAccessSpecification PropertyWrite)
	{
		get<0>().add(PropertyWrite);
	}

	void AddWrites(std::vector<WriteAccessSpecification> PropertyWrites)
	{
		get<0>().add_list(PropertyWrites);
	}

	void SetWrites(std::vector<WriteAccessSpecification> PropertyWrites)
	{
		get<0>().set_list(PropertyWrites);
	}
};

//=============================================================================================
//							UNCONFIRMED OBJECT ACCESS SERVICES
//=============================================================================================

//Write Group
class WriteGroupRequest : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>,
	BACnetSequenceElement<2,
	BACnetSequenceOf<BACnetGroupChannelValue>,
	false>,
	BACnetSequenceElement<3, BACnetBooleanType, true>
	>
{
public:
	U32 GetGroupNumber()
	{
		return get<0>().get();
	}

	U32 GetWritePriority()
	{
		return get<1>().get();
	}

	std::vector<BACnetGroupChannelValue> GetChangeList()
	{
		return get<2>().get_list();
	}

	bool HasInhibitDelay()
	{
		return is_present<3>();
	}

	bool IsInhibitDelaySet()
	{
		if(!HasInhibitDelay())
		{
			return false;
		}
		return get<3>().get();
	}
};
