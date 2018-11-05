#include "SimpleNetwork.h"
#include "NetAddress.h"

CObjectPtr<IBACnetNetworkAddress> CSimpleNetwork::CreateRoutedPortAddress(U16 NetworkID, U8 * Addr, U8 AddrLen) const
{
	CObjectPtr<IBACnetAddress> p = CObjectPtr<IBACnetAddress>(new RoutedPortAddress(Addr, AddrLen), true);
	return CObjectPtr<IBACnetNetworkAddress>(new NetAddress(NetworkID, p), true);
}

CObjectPtr<IBACnetNetworkAddress> CSimpleNetwork::CreateNetworkAddress(U16 NetworkID, CObjectPtr<IBACnetAddress> pAddress) const
{
	return CObjectPtr<IBACnetNetworkAddress>(new NetAddress(NetworkID, pAddress), true);
}

BACnetResult CSimpleNetwork::OnReceive(CObjectPtr<IBACnetAddress> sender, CObjectPtr<IBACnetBuffer> msg)
{
	NPDU npdu;
	npdu.Read(msg);
	if(npdu.HasDADR())
	{
		//is the DNET a broadcast on our network number or the global broadcast?
		if(npdu.GetDADR().NetID != nid && npdu.GetDADR().NetID != 0xFFFF)
		{
			//No. Drop it. We do not route packets.
			return BCE_ROUTING_DISABLED;
		}
	}
	CObjectPtr<IBACnetNetworkAddress> netadr;
	if(npdu.HasSADR())
	{
		if(npdu.GetSADR().AddrLen == 0)
		{
			netadr = CreateNetworkAddress(npdu.GetSADR().NetID);
		}
		else
		{
			netadr = CreateRoutedPortAddress(npdu.GetSADR().NetID, npdu.GetSADR().Addr, npdu.GetSADR().AddrLen);
		}
	}
	else
	{
		netadr = CreateNetworkAddress(nid, sender);
	}
	if(npdu.HasNetworkMessage())
	{
		return HandleNetworkMessage(npdu.GetNetworkMessage(), npdu.GetVendorID(), netadr, msg);
	}
	else
	{
		//What priority is the message?
		if(npdu.GetPriority() & Message_PriorityCritical)
		{
			//critical and higher are called on this thread - do no dispatching.
			return apduhandler(netadr, msg);
		}
		else
		{
			//Urgent and lower are queued. they are scheduled and dispatched as needed.
			return tpool->QueueAsyncCallback([this, netadr, msg](CObjectPtr<IBACnetThreadpool> pPool, CallbackHandle hInst)->BACnetResult
			{
				pPool->CallbackRunsLong(hInst);
				return apduhandler(netadr, msg);
			});
		}
	}
}

BACnetResult CSimpleNetwork::HandleNetworkMessage(U8 NetMessage, U16 VendorID, CObjectPtr<IBACnetNetworkAddress> sender, CObjectPtr<IBACnetBuffer> msg)
{
	if(VendorID == 0)
	{
		switch(NetMessage)
		{
		case NetworkMessage_WhoIsRouterToNetwork:
			//We're not a router - don't respond.
			break;
		case NetworkMessage_IAmRouterToNetwork:
			{
				//Add router to table.
				U16 netid = 0;
				while(BCE_SUCCEEDED(msg->ReadShort(netid, true)))
				{
					auto it = routertbl.insert(std::pair<U16, CObjectPtr<IBACnetAddress>>(netid, sender->GetPortAddress()));
					if(!it.second)
					{
						it.first->second = sender->GetPortAddress();
					}
				}
				break;
			}
		case NetworkMessage_ICouldBeRouterToNetwork:
			{
				//Tell router to initiate connection and add it
				CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
				CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(3);
				U16 netid = 0;
				msg->ReadShort(netid);
				buf->WriteShort(netid);
				buf->WriteByte(0);
				tx->Push(buf);
				return WriteMessage(sender, tx, Message_WaitForTransmit, NetworkMessage_EstablishConnectionToNetwork);
			}
		case NetworkMessage_RejectMessageToNetwork:
			{
				U8 error;
				msg->ReadByte(error);
				if(error == 0x01)
				{
					//this is the one we actually care about. 
					//remove the key and set the event.
					U16 netid = 0;
					msg->ReadShort(netid, true);
					routertbl.erase(netid);
					nmfailed->Set();
					//now back up the msg pointer and forward it to the handler.
					msg->MoveReadHead(-2);
				}
				msg->MoveReadHead(-1);
				break;
			}
		case NetworkMessage_WhatIsNetworkNumber:
			{
				//send back the network number, if we know one.
				if(nid != 0)
				{
					CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();		
					CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(3);
					buf->WriteShort(nid, true);
					buf->WriteByte(config ? 1 : 0);
					tx->Push(buf);
					return WriteMessage(CObjectPtr<IBACnetNetworkAddress>(new NetAddress(nid), true), tx, Message_WaitForTransmit, NetworkMessage_NetworkNumberIs);
				}
				return BC_OK;
			}
		case NetworkMessage_NetworkNumberIs:
			{
				U16 netid;
				U8 configed;
				msg->ReadShort(netid, true);
				msg->ReadByte(configed);
				if(configed == 1)
				{
					if(!config)
					{
						config = true;
						nid = netid;
					}
				}
				else
				{
					if(!config)
					{
						config = false;
						nid = netid;
					}
				}
				return BC_OK;
			}
		default:
			break;
		}
	}
	auto nmh = GetNetworkMessageHandler(NetMessage, VendorID);
	if(nmh)
	{
		return nmh(sender, msg);
	}
	return BC_OK;
}

NetworkMessageHandlerFunction CSimpleNetwork::GetNetworkMessageHandler(U8 NetMessage, U16 VendorID)
{
	U32 Key = ((VendorID << 16) | (NetMessage));
	auto it = nmhandlermap.find(Key);
	if(it == nmhandlermap.end())
	{
		return nullptr;
	}
	return it->second;
}

void CSimpleNetwork::SendNetworkNumber()
{
	if(config)
	{
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(3);
		buf->WriteShort(nid, true);
		buf->WriteByte(1);
		tx->Push(buf);
		WriteMessage(CObjectPtr<IBACnetNetworkAddress>(new NetAddress(nid), true), tx, Message_WaitForTransmit, NetworkMessage_NetworkNumberIs);
	}
}

CSimpleNetwork::CSimpleNetwork(CObjectPtr<IBACnetThreadpool> pThreadPool) :
	tpool(pThreadPool),
	nmfailed(CreateBACnetEvent(true,false)),
	nid(0),
	config(false),
	live(false)
{
}


CSimpleNetwork::~CSimpleNetwork()
{
	Stop();
}

BACnetResult CSimpleNetwork::AttachPort(U16 NetworkID, CObjectPtr<IBACnetPort> pPort)
{
	if(port)
	{
		DetachPort(NetworkID);
	}
	nid = NetworkID;
	if(nid != 0)
	{
		config = true;
	}
	port = pPort;
	port->RegisterReceiverCallback([this](CObjectPtr<IBACnetAddress> sender, CObjectPtr<IBACnetBuffer> msg) -> BACnetResult
	{
		return OnReceive(sender, msg);
	});
	if(live)
	{
		live = false;
		Start();
	}
	return BC_OK;
}

CObjectPtr<IBACnetPort> CSimpleNetwork::GetPort(U16 NetworkID) const
{
	return port;
}

BACnetResult CSimpleNetwork::DetachPort(U16 NetworkID)
{
	if(port)
	{
		port->Stop();
		port->RemoveReceiverCallback();
	}
	port = nullptr;
	nid = 0;
	config = false;
	return BC_OK;
}

U32 CSimpleNetwork::GetMaxAPDUSize(CObjectPtr<IBACnetNetworkAddress> pDestination) const
{
	return port->GetMaxAPDULength();
}

BACnetResult CSimpleNetwork::BuildNPDU(NPDU &n, CObjectPtr<IBACnetAddress>& dest, CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, U32 MessageFlags)
{
	n.SetResponseRequired(((MessageFlags & Message_ExpectingReply) ? true : false));
	n.SetPriority((MessageFlags & Message_PriorityMask));
	//do we need to route to another network?
	U16 destnet = pDestinationAddress->GetNetworkID();
	if(destnet != 0 && destnet != nid)
	{
		//route to remote network.
		//write port address to DNET
		Address dnet;
		dnet.NetID = destnet;
		CObjectPtr<IBACnetAddress> pa = pDestinationAddress->GetPortAddress();
		if(pa == nullptr || pa->IsBroadcast())
		{
			//broadcast to network.
			dnet.AddrLen = 0;
		}
		else
		{
			//unicast.
			dnet.AddrLen = pa->GetAddressLength();
			pa->WriteAddress(dnet.Addr, dnet.AddrLen);
		}
		n.AddDNET(dnet);
		if(destnet != 0xFFFF)
		{
			//unicast to router
			auto it = routertbl.find(destnet);
			if(it == routertbl.end())
			{
				//return error.
				return BCE_ROUTER_NOT_FOUND;
			}
			dest = it->second;
		}
		else
		{
			dest = port->GetBroadcastAddress();
		}
	}
	else
	{
		dest = pDestinationAddress->GetPortAddress();
		if(dest == nullptr)
		{
			dest = port->GetBroadcastAddress();
		}
	}
	return BC_OK;
}

BACnetResult CSimpleNetwork::WriteAPDU(CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, U32 MessageFlags)
{
	//Encode the NPDU
	CObjectPtr<IBACnetBuffer> npdu = CreateBACnetBuffer(NPDU::AvgNPDULength);
	NPDU n;
	CObjectPtr<IBACnetAddress> dest;
	BACnetResult r = BuildNPDU(n, dest, pDestinationAddress, MessageFlags);
	if(BCE_FAILED(r))
	{
		return r;
	}
	//no SNET or message code needed - APDUs do not have them.
	n.Write(npdu);
	pMessage->Push(npdu);
	return port->WriteMessage(dest, pMessage, ((MessageFlags & Message_WaitForTransmit) ? true : false));
}

BACnetResult CSimpleNetwork::WriteMessage(CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, U32 MessageFlags, U8 MessageID, U16 VendorID)
{
	//Encode the NPDU
	CObjectPtr<IBACnetBuffer> npdu = CreateBACnetBuffer(NPDU::AvgNPDULength);
	NPDU n;
	CObjectPtr<IBACnetAddress> dest;
	BACnetResult r = BuildNPDU(n, dest, pDestinationAddress, MessageFlags);
	if(BCE_FAILED(r))
	{
		return r;
	}
	//no SNET needed - we do not route.
	n.AddMessageType(MessageID, VendorID);
	n.Write(npdu);
	pMessage->Push(npdu);
	return port->WriteMessage(dest, pMessage, ((MessageFlags & Message_WaitForTransmit) ? true : false));
}

BACnetResult CSimpleNetwork::RegisterAPDUHandler(APDUHandlerFunction pAPDUHandler)
{
	if(!pAPDUHandler)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(apduhandler)
	{
		return BCE_HANDLER_ALREADY_BOUND;
	}
	apduhandler = pAPDUHandler;
	return BC_OK;
}

BACnetResult CSimpleNetwork::RemoveAPDUHandler()
{
	if(apduhandler)
	{
		Stop();
		apduhandler = nullptr;
	}
	return BC_OK;
}

BACnetResult CSimpleNetwork::RegisterNetworkMessageHandler(U8 NetworkMessageID, U16 VendorID, NetworkMessageHandlerFunction pNetworkMessageHandler)
{
	if(!pNetworkMessageHandler)
	{
		return BCE_INVALID_PARAMETER;
	}
	U32 Key = ((VendorID << 16) | (NetworkMessageID));
	auto it = nmhandlermap.insert(NMHPair(Key, pNetworkMessageHandler));
	if(it.second == false)
	{
		return BCE_HANDLER_ALREADY_BOUND;
	}
	return BC_OK;
}

BACnetResult CSimpleNetwork::RemoveNetworkMessageHandler(U8 NetworkMessageID, U16 VendorID)
{
	U32 Key = ((VendorID << 16) | (NetworkMessageID));
	if(!nmhandlermap.erase(Key))
	{
		return BCE_HANDLER_DOES_NOT_EXIST;
	}
	return BC_OK;
}

BACnetResult CSimpleNetwork::Start()
{
	//check to see that some functions are bound.
	if(!port || 
	   apduhandler == nullptr)
	{
		return BCE_NOT_INITIALIZED;
	}
	if(!live)
	{	
		port->Start();
		SendNetworkNumber();
		live = true;
	}
	//Build the router table and find out all connected networks.
	return BC_OK;
}

BACnetResult CSimpleNetwork::Stop()
{
	if(live)
	{
		if(!port)
		{
			return BCE_NOT_INITIALIZED;
		}
		port->Stop();
	}
	live = false;
	return BC_OK;
}

BACnetResult CSimpleNetwork::DiscoverNetworks()
{
	return WriteMessage(GetBroadcastAddress(nid), nullptr, Message_WaitForTransmit, NetworkMessage_WhoIsRouterToNetwork);
}

CObjectPtr<IBACnetNetworkAddress> CSimpleNetwork::GetBroadcastAddress(U16 NetworkNumber) const
{
	//create a broadcast address for this network.
	return CreateNetworkAddress(NetworkNumber);
}

BACnetResult CSimpleNetwork::GetRoutingTable(U16 NetworkNumber, std::vector<RouterEntry> RoutingTable) const
{
	if(NetworkNumber != nid)
	{
		return BCE_UNKNOWN_NETWORK_NUMBER;
	}
	for(auto it = routertbl.begin(); it != routertbl.end(); ++it)
	{
		RouterEntry re;
		re.ConnectedNetwork = it->first;
		re.pRouterAddress = it->second;
		RoutingTable.push_back(re);
	}
	return BC_OK;
}
