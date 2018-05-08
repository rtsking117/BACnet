#include "IPAddress.h"

IPAddress::IPAddress(sockaddr_in Address, const U8* const Mask):addr(Address)
{
	if(Mask)
	{
		memcpy(mask, Mask, sizeof(mask));
	}
	else
	{
		memset(mask, 0xFF, sizeof(mask));
	}
}

IPAddress::~IPAddress()
{
}

sockaddr_in IPAddress::GetSocketAddress()
{
	return addr;
}

BACnetString IPAddress::ToString() const
{
	return BACnetString::ToString(addr.sin_addr.s_net) + "." +
		BACnetString::ToString(addr.sin_addr.s_host) + "." +
		BACnetString::ToString(addr.sin_addr.s_lh) + "." +
		BACnetString::ToString(addr.sin_addr.s_impno) + ":" +
		BACnetString::ToString(ntohs(addr.sin_port));
}

BACnetResult IPAddress::Parse(BACnetString pString)
{
	//We expect XXX.XXX.XXX.XXX:XXXXX as the string. 
	// reject anything else. If no port is given, 
	// assume 47808 (0xBAC0).
	BACnetString::iterator end;
	int b1 = pString.ParseInt(pString.begin(), &end);
	if(*end != '.')
	{
		return BCE_INVALID_ADDRESS_FORMAT;
	}
	int b2 = pString.ParseInt(end, &end);
	if(*end != '.')
	{
		return BCE_INVALID_ADDRESS_FORMAT;
	}
	int b3 = pString.ParseInt(end, &end);
	if(*end != '.')
	{
		return BCE_INVALID_ADDRESS_FORMAT;
	}
	int b4 = pString.ParseInt(end, &end);
	if(*end != ':')
	{
		//assign and return.
		addr.sin_port = htons(47808);
	}
	else
	{
		addr.sin_port = htons(pString.ParseInt(end) & 0xFFFF);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_net = b1;
	addr.sin_addr.s_host = b2;
	addr.sin_addr.s_lh = b3;
	addr.sin_addr.s_impno = b4;
	return BC_OK;
}

bool IPAddress::IsEqual(CObjectPtr<IBACnetAddress> pAddress) const
{
	if(pAddress == nullptr) return false;
	if(pAddress->GetTypeCode() != GetTypeCode()) return false;
	IPAddress* rhs = (IPAddress*)pAddress.GetInterface();
	return (addr.sin_addr.s_addr == rhs->addr.sin_addr.s_addr) &&
		(addr.sin_port == rhs->addr.sin_port);
}

int IPAddress::Compare(CObjectPtr<IBACnetAddress> pAddress) const
{
	if(pAddress == nullptr) return -1;
	U32 tc = pAddress->GetTypeCode();
	if(GetTypeCode() < tc) return -1;
	if(GetTypeCode() > tc) return 1;
	IPAddress* rhs = (IPAddress*)pAddress.GetInterface();
	if(addr.sin_addr.s_addr < rhs->addr.sin_addr.s_addr) return -1;
	if(addr.sin_addr.s_addr > rhs->addr.sin_addr.s_addr) return 1;
	if(addr.sin_port < rhs->addr.sin_port) return -1;
	if(addr.sin_port > rhs->addr.sin_port) return 1;
	return 0;
}

U32 IPAddress::GetTypeCode() const
{
	return Address_BACnetIP;
}

U32 IPAddress::GetAddressLength() const
{
	return 6;
}

bool IPAddress::IsBroadcast() const
{
	return addr.sin_addr.s_addr == INADDR_BROADCAST;
}

BACnetResult IPAddress::WriteAddress(U8 * const pData, U32 Length) const
{
	if(Length < 6)
	{
		return BCE_NOT_ENOUGH_DATA;
	}
	pData[0] = addr.sin_addr.S_un.S_un_b.s_b1;
	pData[1] = addr.sin_addr.S_un.S_un_b.s_b2;
	pData[2] = addr.sin_addr.S_un.S_un_b.s_b3;
	pData[3] = addr.sin_addr.S_un.S_un_b.s_b4;
	pData[4] = (addr.sin_port & 0x00FF);
	pData[5] = (addr.sin_port & 0xFF00) >> 8;
	return BC_OK;
}

U16 IPAddress::GetPort() const
{
	return addr.sin_port;
}

BACnetResult IPAddress::GetSubnetMask(U8 * const pSubnetMask, U8 uiMaskSize) const
{
	if(!pSubnetMask)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(uiMaskSize < 4)
	{
		return BCE_NOT_ENOUGH_BUFFER_SPACE;
	}
	memcpy(pSubnetMask, mask, 4);
	return BC_OK;
}

BACnetResult BACNETMETHODCALLTYPE IPAddress::GetIpAddress(U8 * const pIpAddress, U8 uiAddressSize) const
{
	if(!pIpAddress)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(uiAddressSize < 4)
	{
		return BCE_NOT_ENOUGH_BUFFER_SPACE;
	}
	pIpAddress[0] = addr.sin_addr.s_net;
	pIpAddress[1] = addr.sin_addr.s_host;
	pIpAddress[2] = addr.sin_addr.s_lh;
	pIpAddress[3] = addr.sin_addr.s_impno;
	return BC_OK;
}

CObjectPtr<IPAddress> IPAddress::CreateIPAddress(sockaddr_in addr, const U8* const mask)
{
	return CObjectPtr<IPAddress>(new IPAddress(addr, mask), true);
}