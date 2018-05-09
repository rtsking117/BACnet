#pragma once
#include <ComWrapper.h>
#include "BACnetIP.h"
#include "WinSockManager.h"
#include "IPAddress.h"
#include <atomic>
using namespace std;

class LocalSocket :
	public ComWrapper<IBACnetLocalSubnet>
{
	ReceiverCallbackFunction RXCallback;
	sockaddr_in Addr;
	CObjectPtr<WinSockManager> WinSock;
	CObjectPtr<IBACnetThreadPool> pool;
	CObjectPtr<IBACnetThread> Listener;
	CObjectPtr<IBACnetEvent> HasRXData;
	CObjectPtr<IBACnetEvent> HasResponse;
	CObjectPtr<IPAddress> BroadcastAddress;
	CObjectPtr<IPAddress> BBMDAddress;
	CObjectPtr<IBACnetThreadpoolTimer> FDRegTimer;
	SOCKET sock;
	U16 AsyncResultCode;
	U16 FDLifetime;
	atomic<bool> HasPendingCommand;
	bool AutoRenew;

	BACnetResult WriteBVLL(sockaddr_in to, U8 messageid, U8 * pBuffer, U16 BufferLength);
	BACnetResult WriteBVLL(sockaddr_in to, U8 messageid, CObjectPtr<IBACnetTransmitBuffer> pBuffer);
	
	BACnetResult StartListenerThread();
	BACnetResult StopListenerThread();

	BACnetResult StartRegistrationTimer();
	BACnetResult StopRegistrationTimer();

	BACnetResult SendCommandAndWait(sockaddr_in to, U8 messageid, U8 * pBuffer, U16 BufferLength, U16& ResponseCode);
	BACnetResult SignalCommandResponse(U16 ResponseCode);

	BACnetResult ListenerThread(CObjectPtr<IBACnetThread>);
	
public:
	LocalSocket(CObjectPtr<IBACnetThreadPool> pThreadPool, U16 PortNumber);
	~LocalSocket();

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
	BACnetResult BACNETMETHODCALLTYPE ReadForeignDeviceTable(const FDTEntry* &ppFDTEntries, size_t &pFDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE WriteForeignDeviceTable(const FDTEntry* pFDTEntries, size_t FDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE ReadBroadcastTable(const BDTEntry* &ppBDTEntries, size_t &pBDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE WriteBroadcastTable(const BDTEntry* pBDTEntries, size_t BDTEntryCount);
	BACnetResult BACNETMETHODCALLTYPE SetIPPort(U16 usPortNumber);

	//IBACnetLocalSubnet
	BACnetResult BACNETMETHODCALLTYPE RegisterAsForeignDevice(const CObjectPtr<IBACnetIPAddress> pRemoteAddress, U16 TimeToLive, bool AutoRefresh = true);
	BACnetResult BACNETMETHODCALLTYPE RenewForeignDeviceRegistration();
	BACnetResult BACNETMETHODCALLTYPE UnregisterAsForeignDevice();
};

