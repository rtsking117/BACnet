#pragma once

#include "BACnetNetwork.h"
#include <ObjectWrapper.h>
#include <map>
#include "NPDU.h"

class CSimpleNetwork :
	public ObjectWrapper<IBACnetSimpleNetwork>
{
	APDUHandlerFunction apduhandler;
	typedef std::pair<U16, CObjectPtr<IBACnetAddress>> routerent;
	std::map<U16, CObjectPtr<IBACnetAddress>> routertbl;
	typedef std::pair<U32, NetworkMessageHandlerFunction> NMHPair;
	std::map<U32, NetworkMessageHandlerFunction> nmhandlermap;
	CObjectPtr<IBACnetPort> port;
	CObjectPtr<IBACnetThreadpool> tpool;
	CObjectPtr<IBACnetEvent> nmfailed;
	U16 nid;
	bool config;
	bool live;

	CObjectPtr<IBACnetNetworkAddress> CreateRoutedPortAddress(U16 NetworkID, U8* Addr, U8 AddrLen) const;
	CObjectPtr<IBACnetNetworkAddress> CreateNetworkAddress(U16 NetworkID, CObjectPtr<IBACnetAddress> pAddress = nullptr) const;

	BACnetResult BuildNPDU(NPDU & n, CObjectPtr<IBACnetAddress>& dest, CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, U32 MessageFlags);

	BACnetResult OnReceive(CObjectPtr<IBACnetAddress> sender, CObjectPtr<IBACnetBuffer> msg);
	BACnetResult HandleNetworkMessage(U8 NetMessage, U16 VendorID, CObjectPtr<IBACnetNetworkAddress> sender, CObjectPtr<IBACnetBuffer> msg);
	NetworkMessageHandlerFunction GetNetworkMessageHandler(U8 NetMessage, U16 VendorID);
	void SendNetworkNumber();

public:
	CSimpleNetwork(CObjectPtr<IBACnetThreadpool> pThreadPool);
	~CSimpleNetwork();

	BACnetResult BACNETMETHODCALLTYPE AttachPort(U16 NetworkID, CObjectPtr<IBACnetPort> pPort);
	CObjectPtr<IBACnetPort> BACNETMETHODCALLTYPE GetPort(U16 NetworkID) const;
	BACnetResult BACNETMETHODCALLTYPE DetachPort(U16 NetworkID);
	U32 BACNETMETHODCALLTYPE GetMaxAPDUSize(CObjectPtr<IBACnetNetworkAddress> pDestination) const;

	BACnetResult BACNETMETHODCALLTYPE WriteMessage(CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, U32 MessageFlags, U8 MessageID, U16 VendorID = 0);
	BACnetResult BACNETMETHODCALLTYPE WriteAPDU(CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, U32 MessageFlags);
	BACnetResult BACNETMETHODCALLTYPE RegisterAPDUHandler(APDUHandlerFunction pAPDUHandler);
	BACnetResult BACNETMETHODCALLTYPE RemoveAPDUHandler();
	BACnetResult BACNETMETHODCALLTYPE RegisterNetworkMessageHandler(U8 NetworkMessageID, U16 VendorID, NetworkMessageHandlerFunction pNetworkMessageHandler);
	BACnetResult BACNETMETHODCALLTYPE RemoveNetworkMessageHandler(U8 NetworkMessageID, U16 VendorID);
	BACnetResult BACNETMETHODCALLTYPE Start();
	BACnetResult BACNETMETHODCALLTYPE Stop();
	BACnetResult BACNETMETHODCALLTYPE DiscoverNetworks();
	BACnetResult BACNETMETHODCALLTYPE GetRoutingTable(U16 NetworkNumber, std::vector<RouterEntry> RoutingTable) const;
	CObjectPtr<IBACnetNetworkAddress> BACNETMETHODCALLTYPE GetBroadcastAddress(U16 NetworkNumber) const;
};

