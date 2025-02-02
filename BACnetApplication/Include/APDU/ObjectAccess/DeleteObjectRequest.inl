#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Delete Object
class DeleteObjectRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType>
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