#include "NetAddress.h"

NetAddress::NetAddress(U16 NetAddress,CObjectPtr<IBACnetAddress> PortAddress):
	netid(NetAddress),
	portaddr(PortAddress)
{
}

NetAddress::~NetAddress()
{
}

BACnetString NetAddress::ToString() const
{
	return (portaddr != nullptr ? portaddr->ToString() : BACnetString("Broadcast")) + " from net " + BACnetString::ToString(netid);
}

CObjectPtr<IBACnetAddress> NetAddress::GetPortAddress() const
{
	return portaddr;
}

U16 NetAddress::GetNetworkID() const
{
	return netid;
}

bool NetAddress::IsEqual(CObjectPtr<IBACnetNetworkAddress> pAddress) const
{
	NetAddress* rhs = (NetAddress*)pAddress.GetInterface();
	bool ret = (netid == rhs->netid);
	if(portaddr)
	{
		return ret && (portaddr->IsEqual(rhs->portaddr));
	}
	else
	{
		return ret && rhs->portaddr == nullptr;
	}
}

int NetAddress::Compare(CObjectPtr<IBACnetNetworkAddress> pAddress) const
{
	NetAddress* rhs = (NetAddress*)pAddress.GetInterface();
	if(rhs == nullptr) return 1;
	if(netid < rhs->netid) return -1;
	if(netid > rhs->netid) return 1;
	if(portaddr)
	{
		return portaddr->Compare(rhs->portaddr);
	}
	else
	{
		return rhs->portaddr ? -1 : 0;
	}
}
