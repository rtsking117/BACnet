#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

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
