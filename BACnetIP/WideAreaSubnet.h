#pragma once

#include "BACnetIP.h"
#include <ObjectWrapper.h>
#include "WinSockManager.h"
#include "IPAddress.h"
#include <atomic>
#include <list>
#include <set>

template<typename T>
struct CompareXDTEntry
{
	constexpr bool operator()(const T& lhs, const T& rhs) const
	{
		int v = memcmp(lhs.IpAddress, rhs.IpAddress, 4);
		if(!v)
		{
			return lhs.Port < rhs.Port;
		}
		return v < 0;
	}
};

class WideAreaSubnet : public ObjectWrapper<IBACnetWideAreaSubnet>
{
	ReceiverCallbackFunction RXCallback;
	sockaddr_in Addr;
	std::set<BDTEntry, CompareXDTEntry<BDTEntry>> bdt;
	CObjectPtr<IBACnetSpinLock> bdtlock;
	std::set<FDTEntry, CompareXDTEntry<FDTEntry>> fdt;
	CObjectPtr<IBACnetSpinLock> fdtlock;
	CObjectPtr<WinSockManager> WinSock;
	CObjectPtr<IBACnetThreadPool> pool;
	CObjectPtr<IBACnetThread> Listener;
	CObjectPtr<IBACnetEvent> HasRXData;
	CObjectPtr<IBACnetEvent> HasResponse;
	CObjectPtr<IPAddress> BroadcastAddress;
	SOCKET sock;
	U16 AsyncResultCode;
	std::atomic<bool> HasPendingCommand;

	BACnetResult WriteBVLL(sockaddr_in to, U8 messageid, U8 * pBuffer, U16 BufferLength);
	BACnetResult WriteBVLL(sockaddr_in to, U8 messageid, CObjectPtr<IBACnetTransmitBuffer> pBuffer);

	BACnetResult StartListenerThread();
	BACnetResult StopListenerThread();

	BACnetResult SendCommandAndWait(sockaddr_in to, U8 messageid, U8 * pBuffer, U16 BufferLength, U16& ResponseCode);
	BACnetResult SignalCommandResponse(U16 ResponseCode);

	BACnetResult ListenerThread(CObjectPtr<IBACnetThread>);

public:
	WideAreaSubnet(CObjectPtr<IBACnetThreadPool> pThreadPool, U16 PortNumber);
	~WideAreaSubnet();

	//IBACnetPort
	BACnetResult BACNETMETHODCALLTYPE WriteMessage(CObjectPtr<IBACnetAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, bool WaitForTransmit = false);
	CObjectPtr<IBACnetAddress> BACNETMETHODCALLTYPE CreateAddress(U32 AddressSize, const U8 * const AddressDataBuffer) const;
	CObjectPtr<IBACnetAddress> BACNETMETHODCALLTYPE GetBroadcastAddress() const;
	BACnetResult BACNETMETHODCALLTYPE RegisterReceiverCallback(ReceiverCallbackFunction pCallback);
	BACnetResult BACNETMETHODCALLTYPE RemoveReceiverCallback();
	BACnetAddressType BACNETMETHODCALLTYPE GetAddressType() const { return BACnetAddressType::Address_BACnetIP; }
	U32 BACNETMETHODCALLTYPE GetMaxAPDULength() const { return 1476; }
	U32 BACNETMETHODCALLTYPE GetMaxTransmitLength() const { return 1536; }
	U32 BACNETMETHODCALLTYPE GetMaxHeaderLength() const { return 4; }
	BACnetResult BACNETMETHODCALLTYPE Start();
	BACnetResult BACNETMETHODCALLTYPE Stop();

	//IBACnetIPPort
	CObjectPtr<IBACnetIPAddress> BACNETMETHODCALLTYPE CreateIPAddress(const U8 * const pIpAddress, U16 usPort, const U8 * const pSubnetMask) const;
	BACnetResult BACNETMETHODCALLTYPE ReadForeignDeviceTable(const FDTEntry* pFDTEntries, size_t &pFDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE WriteForeignDeviceTable(const FDTEntry* pFDTEntries, size_t FDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE ReadBroadcastTable(const BDTEntry* pBDTEntries, size_t &pBDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE WriteBroadcastTable(const BDTEntry* pBDTEntries, size_t BDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE SetIPPort(U16 usPortNumber);

	//IBACnetWideAreaNetwork
	BACnetResult BACNETMETHODCALLTYPE AddRemotePeer(const CObjectPtr<IBACnetIPAddress> pRemoteAddress);
};

