#pragma once
#include <BACnetInterface.h>
#include <BACnetTypes.h>
#include <Windows.h>

#pragma pack(push,1)
struct Address
{
	U16 NetID;
	U8 AddrLen;
	U8 Addr[8];
};
#pragma pack(pop)

class NPDU
{
	U8 Version;
	U8 Control;
	Address DADR;
	Address SADR;
	U8 HopCount;
	U8 MsgType;
	U16 VendorID;
	U32 length;

public:
	static const U32 MaxNPDULength = sizeof(U8) * 4 + sizeof(U16) + sizeof(Address) * 2;
	static const U32 AvgNPDULength = sizeof(U8) * 3 + sizeof(Address); //routed to destination, no message.

public:
	NPDU();
	~NPDU();

	BACnetResult AddDNET(Address NewDNET);
	BACnetResult RemoveDNET();
	BACnetResult AddSNET(Address NewSNET);
	BACnetResult RemoveSNET();
	BACnetResult AddMessageType(U8 MessageType, U16 VendorID=0);
	BACnetResult RemoveMessageType();
	void SetPriority(U8 Priority);
	void SetResponseRequired(bool NeedResponse);

	bool IsResponseRequired() const;
	bool HasDADR() const;
	bool HasSADR() const;
	bool HasNetworkMessage() const;

	U8 GetPriority() const;

	Address GetSADR() const;
	Address GetDADR() const;

	U8 GetNetworkMessage() const;
	U16 GetVendorID() const;
	U8 GetHopCount() const;

	U32 GetNPDULength() const;

	BACnetResult Write(CObjectPtr<IBACnetBuffer> txbuf);
	BACnetResult Read(CObjectPtr<IBACnetBuffer> rxbuf);

};

