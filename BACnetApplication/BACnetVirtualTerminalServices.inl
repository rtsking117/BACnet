#pragma once

#include "BACnetComplexTypes.inl"

//=============================================================================================
//							CONFIRMED VIRTUAL TERMINAL SERVICES
//=============================================================================================

//VT Open
class VTOpenRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetVTClassType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>
	>
{
public:

	U32 GetVTClass()
	{
		return get<0>().get();
	}

	U8 GetLocalSessionID()
	{
		return get<1>().get();
	}

	void SetVTClass(U32 VTClass)
	{
		get<0>().set(VTClass);
	}

	void SetLocalSessionID(U8 LocalSessionID)
	{
		get<1>().set(LocalSessionID);
	}
};

//VT Open Ack
class VTOpenResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>
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

//VT Close
class VTCloseRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<BACnetUnsigned8Type>, false>
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

//VT Data
class VTDataRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<NoTag, BACnetOctetStringType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType, false>
	>
{
public:
	U8 GetSessionID()
	{
		return get<0>().get();
	}

	BACnetByteString GetVTData()
	{
		return get<1>().get();
	}

	U32 GetDataFlag()
	{
		return get<2>().get();
	}

	void SetSessionID(U8 SessionID)
	{
		get<0>().set(SessionID);
	}

	void SetVTData(BACnetByteString VTData)
	{
		get<1>().set(VTData);
	}

	void SetDataFlag(bool DataFlag)
	{
		get<2>().set(DataFlag ? 1 : 0);
	}
};

//VT Data Ack
class VTDataResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetBooleanType, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>
	>
{
public:
	bool IsValid()
	{
		if(WasAllDataAccepted())
		{
			return !HasAcceptedOctetCount();
		}
		return HasAcceptedOctetCount();
	}

	bool WasAllDataAccepted()
	{
		return get<0>().get();
	}

	bool HasAcceptedOctetCount()
	{
		return is_present<1>();
	}

	U32 GetAcceptedOctetCount()
	{
		if(!HasAcceptedOctetCount())
		{
			return (U32)-1;
		}
		return get<1>().get();
	}

	void SetAllDataAcceptedFlag(bool WasAllDataAccepted)
	{
		get<0>().set(WasAllDataAccepted);
		if(WasAllDataAccepted)
		{
			make_present<1>(false);
		}
	}

	void SetAcceptedOctetCount(U32 AcceptedOctetCount)
	{
		get<0>().set(false);
		make_present<1>(true);
		get<1>().set(AcceptedOctetCount);
	}
};