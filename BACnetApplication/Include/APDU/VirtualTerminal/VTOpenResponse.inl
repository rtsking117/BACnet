#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//VT Open Ack
class VTOpenResponse : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetUnsigned8Type>
	>
{
public:

	U8 GetRemoteSessionID()
	{
		return get<0>().get();
	}

	void SetRemoteSessionID(U8 RemoteSessionID)
	{
		get<0>().set(RemoteSessionID);
	}
};