#include "MSTPAddress.h"

MSTPAddress::MSTPAddress(U8 Address):NodeAddr(Address)
{
}

MSTPAddress::~MSTPAddress()
{
}

U8 MSTPAddress::GetAddressValue()
{
	return NodeAddr;
}

BACnetString MSTPAddress::ToString()
{
	return BACnetString::ToString(NodeAddr);
}

BACnetResult MSTPAddress::Parse(BACnetString pString)
{
	I32 i = pString.ParseInt();
	if(i & ~0xFF)
	{
		return BCE_INVALID_ADDRESS_FORMAT;
	}
	NodeAddr = i & 0xFF;
	return 0;
}

bool MSTPAddress::IsEqual(CObjectPtr<IBACnetAddress> pAddress)
{
	if(pAddress == nullptr) return false;
	if(pAddress->GetTypeCode() != GetTypeCode()) return false;
	MSTPAddress* rhs = (MSTPAddress*)pAddress.GetInterface();
	return (NodeAddr == rhs->NodeAddr);
}

int MSTPAddress::Compare(CObjectPtr<IBACnetAddress> pAddress)
{
	if(pAddress == nullptr) return 1;
	U32 tc = pAddress->GetTypeCode();
	if(GetTypeCode() < tc) return -1;
	if(GetTypeCode() > tc) return 1;
	MSTPAddress* rhs = (MSTPAddress*)pAddress.GetInterface();
	if(NodeAddr < rhs->NodeAddr) return -1;
	if(NodeAddr > rhs->NodeAddr) return 1;
	return 0;
}

U32 MSTPAddress::GetTypeCode()
{
	return Address_MSTP;
}

U32 MSTPAddress::GetAddressLength()
{
	return 1;
}

BACnetResult MSTPAddress::WriteAddress(U8 * pData, U32 Length)
{
	if(!Length) return BCE_NOT_ENOUGH_BUFFER_SPACE;
	*pData = NodeAddr;
	return BC_OK;
}
