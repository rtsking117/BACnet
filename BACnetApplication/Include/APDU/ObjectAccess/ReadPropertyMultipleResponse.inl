#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/ReadAccessResult.inl>

//Read Property Multiple Ack
class ReadPropertyMultipleResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<ReadAccessResult>>
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
