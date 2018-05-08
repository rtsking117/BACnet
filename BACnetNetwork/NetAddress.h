#pragma once

#include <BACnetInterface.h>
#include <ComWrapper.h>

class RoutedPortAddress :
	public ComWrapper<IBACnetAddress>
{
	U8 Addr[8];
	U8 AddrLen;
public:
	RoutedPortAddress(U8* addr, U8 len) : AddrLen(len)
	{
		if(AddrLen)
		{
			memcpy(Addr, addr, AddrLen);
		}
	}
	~RoutedPortAddress() {}

	BACnetString BACNETMETHODCALLTYPE ToString() const { return BACnetString("Routed source address"); }
	BACnetResult BACNETMETHODCALLTYPE Parse(BACnetString pString) { return BC_OK; }
	bool BACNETMETHODCALLTYPE IsEqual(CObjectPtr<IBACnetAddress> pAddress) const
	{
		return pAddress->GetTypeCode() == GetTypeCode();
	}
	int BACNETMETHODCALLTYPE Compare(CObjectPtr<IBACnetAddress> pAddress) const
	{
		if(pAddress == nullptr) return 1;
		U32 tc = pAddress->GetTypeCode();
		if(GetTypeCode() < tc) return -1;
		if(GetTypeCode() > tc) return 1;
		return 0;
	}
	U32 BACNETMETHODCALLTYPE GetTypeCode() const { return Address_Unknown; }
	U32 BACNETMETHODCALLTYPE GetAddressLength() const { return AddrLen; }
	bool BACNETMETHODCALLTYPE IsBroadcast() const { return AddrLen == 0; }
	BACnetResult BACNETMETHODCALLTYPE WriteAddress(U8* const pData, U32 Length) const
	{
		if(AddrLen)
		{
			if(Length < AddrLen)
			{
				memcpy(pData, Addr, AddrLen);
			}
			else
			{
				return BCE_BUFFER_OVERFLOW;
			}
		}
		return BC_OK;
	}
};

class NetAddress :
	public ComWrapper<IBACnetNetworkAddress>
{
	CObjectPtr<IBACnetAddress> portaddr;
	U16 netid;

public:
	NetAddress( U16 NetAddress, CObjectPtr<IBACnetAddress> PortAddress = nullptr);
	~NetAddress();

	BACnetString BACNETMETHODCALLTYPE ToString() const;
	CObjectPtr<IBACnetAddress> BACNETMETHODCALLTYPE GetPortAddress() const;
	U16 BACNETMETHODCALLTYPE GetNetworkID() const;
	bool BACNETMETHODCALLTYPE IsEqual(CObjectPtr<IBACnetNetworkAddress> pAddress) const;
	int BACNETMETHODCALLTYPE Compare(CObjectPtr<IBACnetNetworkAddress> pAddress) const;
};

