#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/ReadAccessSpecification.inl>

//Read Property Multiple
class ReadPropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<ReadAccessSpecification>>
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
