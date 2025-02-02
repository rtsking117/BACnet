#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//VT Close
class VTCloseRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<BACnetUnsigned8Type>>
	>
{
public:

	std::vector<U8> GetRemoteSessionIDs()
	{
		std::vector<U8> ret;
		for each(auto i in get<0>().get_list())
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	void SetRemoteSessionIDs(std::vector<U8> RemoteSessionIDs)
	{
		get<0>().clear_list();
		for each(U8 i in RemoteSessionIDs)
		{
			get<0>().add(BACnetUnsigned8Type(i));
		}
	}

	void AddRemoteSessionID(U8 RemoteSessionID)
	{
		get<0>().add(BACnetUnsigned8Type(RemoteSessionID));
	}

	void AddRemoteSessionIDs(std::vector<U8> RemoteSessionIDs)
	{
		for each(U8 i in RemoteSessionIDs)
		{
			get<0>().add(BACnetUnsigned8Type(i));
		}
	}

	void ClearRemoteSessionIDs()
	{
		get<0>().clear_list();
	}
};
