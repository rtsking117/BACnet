#include "WideAreaSubnet.h"



WideAreaSubnet::WideAreaSubnet(CObjectPtr<IBACnetThreadPool> pThreadPool, U16 PortNumber):
	sock(INVALID_SOCKET),
	HasRXData(CreateBACnetEvent(true, false)),
	HasResponse(CreateBACnetEvent(true, false)),
	Listener(CreateBACnetThread([this](auto thread) -> auto { return ListenerThread(thread); })),
	pool(pThreadPool),
	BroadcastAddress(nullptr)
{
	BACnetResult r = CreateWSADevice(WinSock);
	if(BCE_FAILED(r))
	{
		throw BACnetException("Failed to initialize the Windows Sockets device.", r);
	}
	//Allow async I/O
	sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if(sock == INVALID_SOCKET)
	{
		throw BACnetException("Failed to create the socket.", BCNRESULT_FROM_SYSTEM(WSAGetLastError()));
	}
	//now set up permissions:
	//allow broadcast
	BOOL bcast = TRUE;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&bcast, sizeof(bcast));
	sockaddr_in tmpaddr = { 0 };
	tmpaddr.sin_family = AF_INET;
	tmpaddr.sin_port = htons(PortNumber);
	tmpaddr.sin_addr.s_addr = INADDR_ANY;
	if(::bind(sock, (sockaddr*)&tmpaddr, sizeof(tmpaddr)))
	{
		throw BACnetException("Failed to bind port 47808.", BCNRESULT_FROM_SYSTEM(WSAGetLastError()));
	}
	tmpaddr.sin_addr.s_addr = INADDR_BROADCAST;
	BroadcastAddress = IPAddress::CreateIPAddress(tmpaddr);
	//socket is now bound.
	//get the real address we're bound to.
	int addrsz = sizeof(Addr);
	if(getsockname(sock, (sockaddr*)&Addr, &addrsz))
	{
		//problem!
		throw BACnetException("Failed to retrieve bound address.", BCNRESULT_FROM_SYSTEM(WSAGetLastError()));
	}
}


WideAreaSubnet::~WideAreaSubnet()
{
	Stop();
	closesocket(sock);
	CloseHandle(HasRXData);
}

BACnetResult WideAreaSubnet::WriteMessage(CObjectPtr<IBACnetAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, bool WaitForTransmit)
{
	return BACnetResult();
}

CObjectPtr<IBACnetAddress> WideAreaSubnet::CreateAddress(U32 AddressSize, const U8 * const AddressDataBuffer) const
{
	return CObjectPtr<IBACnetAddress>();
}

CObjectPtr<IBACnetAddress> WideAreaSubnet::GetBroadcastAddress() const
{
	return CObjectPtr<IBACnetAddress>();
}

BACnetResult WideAreaSubnet::RegisterReceiverCallback(ReceiverCallbackFunction pCallback)
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::RemoveReceiverCallback()
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::Start()
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::Stop()
{
	return BACnetResult();
}

CObjectPtr<IBACnetIPAddress> WideAreaSubnet::CreateIPAddress(const U8 * const pIpAddress, U16 usPort, const U8 * const pSubnetMask) const
{
	return CObjectPtr<IBACnetIPAddress>();
}

BACnetResult WideAreaSubnet::ReadForeignDeviceTable(const FDTEntry *& ppFDTEntries, size_t & pFDTEntryCount)
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::WriteForeignDeviceTable(const FDTEntry * pFDTEntries, size_t FDTEntryCount)
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::ReadBroadcastTable(const BDTEntry *& ppBDTEntries, size_t & pBDTEntryCount)
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::WriteBroadcastTable(const BDTEntry * pBDTEntries, size_t BDTEntryCount)
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::SetIPPort(U16 usPortNumber)
{
	return BACnetResult();
}

BACnetResult WideAreaSubnet::AddRemotePeer(const CObjectPtr<IBACnetIPAddress> pRemoteAddress)
{
	return BACnetResult();
}
