#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/WriteAccessSpecification.inl>

//Write Property Multiple
class WritePropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<WriteAccessSpecification>>
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
