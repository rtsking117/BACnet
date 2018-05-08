#pragma once
#include <BACnetInterface.h>
#include <ComWrapper.h>
#include <memory>

class MSTPAddress :
	public ComWrapper<IBACnetAddress>
{
	U8 NodeAddr;
public:
	MSTPAddress(U8 Address);
	~MSTPAddress();

	U8 GetAddressValue();

	BACnetString BACNETMETHODCALLTYPE ToString();
	BACnetResult BACNETMETHODCALLTYPE Parse(BACnetString pString);
	bool BACNETMETHODCALLTYPE IsEqual(CObjectPtr<IBACnetAddress> pAddress);
	int BACNETMETHODCALLTYPE Compare(CObjectPtr<IBACnetAddress> pAddress);
	U32 BACNETMETHODCALLTYPE GetTypeCode();
	U32 BACNETMETHODCALLTYPE GetAddressLength();
	BACnetResult BACNETMETHODCALLTYPE WriteAddress(U8* pData, U32 Length);
};

