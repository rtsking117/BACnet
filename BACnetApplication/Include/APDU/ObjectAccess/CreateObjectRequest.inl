#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPropertyValue.inl>

//Create Object
class CreateObjectRequest : public
	BACnetSequence<
		BACnetSequenceElement<0,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetEnumeratedType>,
				BACnetChoiceElement<1, BACnetObjectIDType>
			>
		>,
		BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyValue>, true>
	>
{
public:
	bool IsObjectType()
	{
		return get<0>().is_selected(0);
	}

	U32 GetObjectType()
	{
		if (!IsObjectType())
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
		if (!IsObjectID())
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
		if (!HasInitialValues())
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