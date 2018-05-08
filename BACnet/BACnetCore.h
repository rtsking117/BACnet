#pragma once

#include "BACnetInterface.h"

#ifndef __IBACnetStackComponent__FWD_DEFINED__
#define __IBACnetStackComponent__FWD_DEFINED__
typedef struct IBACnetStackComponent IBACnetStackComponent;
#endif

#ifndef __IBACnetAddress__FWD_DEFINED__
#define __IBACnetAddress__FWD_DEFINED__
typedef struct IBACnetAddress IBACnetAddress;
#endif

#ifndef __IBACnetPort__FWD_DEFINED__
#define __IBACnetPort__FWD_DEFINED__
typedef struct IBACnetPort IBACnetPort;
#endif

#ifndef __IBACnetNetworkAddress__FWD_DEFINED__
#define __IBACnetNetworkAddress__FWD_DEFINED__
typedef struct IBACnetNetworkAddress IBACnetNetworkAddress;
#endif

#ifndef __IBACnetSecurityContext__FWD_DEFINED__
#define __IBACnetSecurityContext__FWD_DEFINED__
typedef struct IBACnetSecurityContext IBACnetSecurityContext;
#endif

#ifndef __IBACnetNetwork__FWD_DEFINED__
#define __IBACnetNetwork__FWD_DEFINED__
typedef struct IBACnetNetwork IBACnetNetwork;
#endif

#ifndef __IBACnetTransactionManager__FWD_DEFINED__
#define __IBACnetTransactionManager__FWD_DEFINED__
typedef struct IBACnetTransactionManager IBACnetTransactionManager;
#endif

#include "BACnetBuffer.h"

BACNET_INTERFACE("{501F3385-9CA7-4381-9E9B-2E9194FCCF2D}")
IBACnetStackComponent : public IBACnetUnknown
{
	BCNMETHOD(Start()) BCPURE;
	BCNMETHOD(Stop()) BCPURE;
};

enum BACnetAddressType
{
	Address_Unknown,
	Address_None,
	Address_Ethernet,
	Address_ARCNET,
	Address_MSTP,
	Address_LON,
	Address_BACnetIP,
	Address_ZigBee,
	Address_Custom = 0x80000000,
};

//To add a custom address type, use the following macro
#define MAKE_CUSTOM_ADDRESS(AddressTypeValue,VendorID) ((U32)(((((U32)(AddressTypeValue))&0x7FFF)<<16) | (((U32)(VendorID))&0xFFFF) | Address_Custom)

BACNET_INTERFACE("{2C64C484-845B-413D-97A1-64E20DD3F47A}")
IBACnetAddress: public IBACnetUnknown
{
	BCNMETHODTYPE(BACnetString,ToString() const) BCPURE;
	BCNMETHOD(Parse(BACnetString pString)) BCPURE;
	BCNMETHODTYPE(bool, IsEqual(CObjectPtr<IBACnetAddress> pAddress) const) BCPURE;
	BCNMETHODTYPE(int, Compare(CObjectPtr<IBACnetAddress> pAddress) const) BCPURE;
	BCNMETHODTYPE(U32, GetTypeCode() const) BCPURE;
	BCNMETHODTYPE(U32, GetAddressLength() const) BCPURE;
	BCNMETHODTYPE(bool, IsBroadcast() const) BCPURE;
	BCNMETHOD(WriteAddress(U8* const pData, U32 Length) const) BCPURE;
};

typedef std::function<BACnetResult(CObjectPtr<IBACnetAddress>, CObjectPtr<IBACnetBuffer>)> ReceiverCallbackFunction;

BACNET_INTERFACE("{5A6124CA-D9AD-420F-9143-D0A49FAA7408}")
IBACnetPort : public IBACnetStackComponent
{
	BCNMETHOD(WriteMessage(CObjectPtr<IBACnetAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, bool WaitForTransmit = false)) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetAddress>, CreateAddress(U32 AddressSize, const U8* const AddressDataBuffer = nullptr) const) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetAddress>, GetBroadcastAddress() const) BCPURE;
	BCNMETHODTYPE(BACnetAddressType, GetAddressType() const) BCPURE;
	BCNMETHODTYPE(U32, GetMaxAPDULength() const) BCPURE;
	BCNMETHODTYPE(U32, GetMaxTransmitLength() const) BCPURE;
	BCNMETHODTYPE(U32, GetMaxHeaderLength() const) BCPURE;
	BCNMETHOD(RegisterReceiverCallback(ReceiverCallbackFunction pCallback)) BCPURE;
	BCNMETHOD(RemoveReceiverCallback()) BCPURE;
};

BACNET_INTERFACE("{7053E207-B9FE-47C5-A422-351D9269577F}")
IBACnetSecurityContext: public IBACnetUnknown
{

};

BACNET_INTERFACE("{F8F39A69-E66F-480A-B871-9CA9837F6953}")
IBACnetNetworkAddress : public IBACnetUnknown
{
	BCNMETHODTYPE(BACnetString, ToString() const) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetAddress>, GetPortAddress() const) BCPURE;
	BCNMETHODTYPE(U16, GetNetworkID() const) BCPURE;
	BCNMETHODTYPE(bool, IsEqual(CObjectPtr<IBACnetNetworkAddress> pAddress) const) BCPURE;
	BCNMETHODTYPE(int, Compare(CObjectPtr<IBACnetNetworkAddress> pAddress) const) BCPURE;
};

enum TransmitFlags
{
	Message_PriorityNormal = 0x00,
	Message_PriorityUrgent = 0x01,
	Message_PriorityCritical = 0x02,
	Message_PriorityLifeSafety = 0x03,
	Message_PriorityMask = 0x03,
	Message_ExpectingReply = 0x04,
	Message_WaitForTransmit = 0x1000,
};

typedef std::function<BACnetResult(CObjectPtr<IBACnetNetworkAddress> pSender, CObjectPtr<IBACnetBuffer> pBuffer)> APDUHandlerFunction;
typedef std::function<BACnetResult(CObjectPtr<IBACnetNetworkAddress> pSender, CObjectPtr<IBACnetBuffer> pBuffer)> NetworkMessageHandlerFunction;

enum NetworkMessages
{
	NetworkMessage_WhoIsRouterToNetwork = 0x0,
	NetworkMessage_IAmRouterToNetwork = 0x1,
	NetworkMessage_ICouldBeRouterToNetwork = 0x2,
	NetworkMessage_RejectMessageToNetwork = 0x3,
	NetworkMessage_RouterBusyToNetwork = 0x4,
	NetworkMessage_RouterAvailableToNetwork = 0x5,
	NetworkMessage_InitRtTable = 0x6,
	NetworkMessage_InitRtTableAck = 0x7,
	NetworkMessage_EstablishConnectionToNetwork = 0x8,
	NetworkMessage_DisconnectConnectionToNetwork = 0x9,
	NetworkMessage_ChallengeRequest = 0xa,
	NetworkMessage_SecurityPayload = 0xb,
	NetworkMessage_SecurityResponse = 0xc,
	NetworkMessage_RequestKeyUpdate = 0xd,
	NetworkMessage_UpdateKeySet = 0xe,
	NetworkMessage_UpdateDistributionKey = 0xf,
	NetworkMessage_RequestMasterKey = 0x10,
	NetworkMessage_SetMasterKey = 0x11,
	NetworkMessage_WhatIsNetworkNumber = 0x12,
	NetworkMessage_NetworkNumberIs = 0x13,
};

struct RouterEntry
{
	CObjectPtr<IBACnetAddress> pRouterAddress;
	U16 ConnectedNetwork;
};

BACNET_INTERFACE("{C1CBE3E6-3096-418E-9546-D041B1A0D7C6}")
IBACnetNetwork : public IBACnetStackComponent
{
	BCNMETHOD(AttachPort(U16 NetworkID, CObjectPtr<IBACnetPort> pPort)) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetPort>, GetPort(U16 NetworkID) const) BCPURE;
	BCNMETHOD(DetachPort(U16 NetworkID)) BCPURE;
	BCNMETHODTYPE(U32, GetMaxAPDUSize(CObjectPtr<IBACnetNetworkAddress> pDestination) const) BCPURE;
	BCNMETHOD(WriteAPDU(CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, U32 MessageFlags)) BCPURE;
	BCNMETHOD(WriteMessage(CObjectPtr<IBACnetNetworkAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, U32 MessageFlags, U8 MessageID, U16 VendorID = 0)) BCPURE;
	BCNMETHOD(RegisterAPDUHandler(APDUHandlerFunction pAPDUHandler)) BCPURE;
	BCNMETHOD(RemoveAPDUHandler()) BCPURE;
	BCNMETHOD(RegisterNetworkMessageHandler(U8 NetworkMessageID, U16 VendorID, NetworkMessageHandlerFunction pNetworkMessageHandler)) BCPURE;
	BCNMETHOD(RemoveNetworkMessageHandler(U8 NetworkMessageID, U16 VendorID)) BCPURE;
	BCNMETHOD(DiscoverNetworks()) BCPURE;
	BCNMETHOD(GetRoutingTable(U16 NetworkNumber, std::vector<RouterEntry> RoutingTable) const) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetNetworkAddress>, GetBroadcastAddress(U16 NetworkID) const) BCPURE;
};

BACNET_INTERFACE("{DFF1E4AD-14BC-40AE-A096-4C14DA5E5525}")
IBACnetTransaction : public IBACnetUnknown
{
	BCNMETHODTYPE(CObjectPtr<IBACnetNetworkAddress>, GetSender() const) BCPURE;
	BCNMETHODTYPE(U8, GetServiceChoice() const) BCPURE;
	BCNMETHOD(Acknowledge(CObjectPtr<IBACnetBuffer> pResponseData = nullptr)) BCPURE;
	BCNMETHOD(Abort(AbortCode Reason)) BCPURE;
	BCNMETHOD(Reject(RejectCode Reason)) BCPURE;
	BCNMETHOD(SendError(CObjectPtr<IBACnetBuffer> pEncodedError)) BCPURE;
	BCNMETHOD(WaitForCompletion()) BCPURE;
	BCNMETHODTYPE(BACnetResult, GetTransactionResult() const) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetBuffer>, GetTransactionData()) BCPURE;
};

typedef std::function<BACnetResult(CObjectPtr<IBACnetTransaction>)> ConfirmedRequestHandler;
typedef std::function<BACnetResult(CObjectPtr<IBACnetNetworkAddress>, U8, CObjectPtr<IBACnetBuffer>)> UnconfirmedRequestHandler;

BACNET_INTERFACE("{0E492A84-1F5D-46A7-A467-C182CF6AD467}")
IBACnetTransactionManager : public IBACnetStackComponent
{
	BCNMETHOD(AttachNetwork(CObjectPtr<IBACnetNetwork> pNetwork)) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetNetwork>, GetNetwork() const) BCPURE;
	BCNMETHOD(DetachNetwork()) BCPURE;
	BCNMETHOD(RegisterConfirmedRequestHandler(ConfirmedRequestHandler pHandler)) BCPURE;
	BCNMETHOD(RemoveConfirmedRequestHandler()) BCPURE;
	BCNMETHOD(RegisterUnconfirmedRequestHandler(UnconfirmedRequestHandler pHandler)) BCPURE;
	BCNMETHOD(RemoveUnconfirmedRequestHandler()) BCPURE;
	BCNMETHOD(SendConfirmedRequest(CObjectPtr<IBACnetNetworkAddress> pDestination,
								   U8 ServiceChoice, 
								   CObjectPtr<IBACnetBuffer> pMessage,
								   CObjectPtr<IBACnetTransaction>& pTransaction)) BCPURE;
	BCNMETHOD(SendUnconfirmedRequest(CObjectPtr<IBACnetNetworkAddress> pDestination,
									 U8 ServiceChoice,
									 CObjectPtr<IBACnetBuffer> pMessage) const) BCPURE;
};

