#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//I Have
class IHaveRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType>,
		BACnetSequenceElement<NoTag, BACnetObjectIDType>,
		BACnetSequenceElement<NoTag, BACnetCharacterStringType>
	>
{
public:

	BACnetObjectID GetDeviceID()
	{
		return get<0>().get();
	}

	BACnetObjectID GetObjectID()
	{
		return get<1>().get();
	}

	BACnetString GetCharString()
	{
		return get<2>().get();
	}

	void SetDeviceID(BACnetObjectID DeviceID)
	{
		get<0>().set(DeviceID);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<1>().set(ObjectID);
	}

	void SetCharStringID(BACnetString CharString)
	{
		get<2>().set(CharString);
	}
};
