#pragma once
#include "WinSockManager.h"
#include <ObjectWrapper.h>
#include "BACnetIP.h"

class IPAddress :
	public ObjectWrapper<IBACnetIPAddress>
{
	sockaddr_in addr;
	U8 mask[4];
	
public:
	IPAddress(sockaddr_in Address, const U8* const mask);
	~IPAddress();

	sockaddr_in GetSocketAddress();

	BACnetString BACNETMETHODCALLTYPE ToString() const;
	BACnetResult BACNETMETHODCALLTYPE Parse(BACnetString pString);
	bool BACNETMETHODCALLTYPE IsEqual(CObjectPtr<IBACnetAddress> pAddress) const;
	int BACNETMETHODCALLTYPE Compare(CObjectPtr<IBACnetAddress> pAddress) const;
	U32 BACNETMETHODCALLTYPE GetTypeCode() const;
	U32 BACNETMETHODCALLTYPE GetAddressLength() const;
	bool BACNETMETHODCALLTYPE IsBroadcast() const;
	BACnetResult BACNETMETHODCALLTYPE WriteAddress(U8* const pData, U32 Length) const;
	U16 BACNETMETHODCALLTYPE GetPort() const;
	BACnetResult BACNETMETHODCALLTYPE GetSubnetMask(U8* const pSubnetMask, U8 uiMaskSize) const;
	BACnetResult BACNETMETHODCALLTYPE GetIpAddress(U8* const pIpAddress, U8 uiAddressSize) const;

	static CObjectPtr<IPAddress> CreateIPAddress(sockaddr_in addr, const U8* const mask = nullptr);
};

