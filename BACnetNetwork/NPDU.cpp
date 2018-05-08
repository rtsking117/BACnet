#include "NPDU.h"
#include <memory.h>

enum ControlBits
{
	HasMessageType = 0x80,
	HasDNET = 0x20,
	HasSNET = 0x08,
	NeedsReply = 0x40,
};

NPDU::NPDU():
	Version(0x01),
	Control(0x00),
	HopCount(0),
	MsgType(0),
	VendorID(0),
	length(2)
{
	memset(&DADR, 0, sizeof(DADR));
	memset(&SADR, 0, sizeof(SADR));
}


NPDU::~NPDU()
{

}

BACnetResult NPDU::AddDNET(Address NewDNET)
{
	if(Control & HasDNET)
	{
		RemoveDNET();
	}
	Control ^= HasDNET; //toggle the bit on.
	DADR = NewDNET;
	HopCount = 0xFF;
	length += 5; //DNET + DLEN + HopCount
	length += DADR.AddrLen; 
	return BC_OK;
}

BACnetResult NPDU::RemoveDNET()
{
	if((Control & HasDNET))
	{
		Control ^= HasDNET;
		HopCount = 0;
		length -= DADR.AddrLen;
		length -= 5;
	}
	return BC_OK;
}

BACnetResult NPDU::AddSNET(Address NewSNET)
{
	if(Control & HasSNET)
	{
		RemoveSNET();
	}
	Control ^= HasSNET; //toggle the bit on.
	SADR = NewSNET;
	length += 3; //SNET + SLEN
	length += SADR.AddrLen;
	return BC_OK;
}

BACnetResult NPDU::RemoveSNET()
{
	if((Control & HasSNET))
	{
		Control ^= HasSNET;
		length -= SADR.AddrLen;
		length -= 3;
	}
	return BC_OK;
}

BACnetResult NPDU::AddMessageType(U8 MessageType, U16 VendorId)
{
	if((MessageType & 0x80) && !VendorId)
	{
		return BCE_VENDOR_ID_UNSPECIFIED;
	}
	if(Control & HasMessageType)
	{
		RemoveMessageType();
	}
	Control ^= HasMessageType;
	MsgType = MessageType;
	VendorID = VendorId;
	++length;
	if(MsgType & 0x80)
	{
		length += 2;
	}
	return BC_OK;
}

BACnetResult NPDU::RemoveMessageType()
{
	if(Control & HasMessageType)
	{
		return BC_OK;
	}
	--length;
	if(MsgType & 0x80)
	{
		length -= 2;
	}
	MsgType = 0;
	VendorID = 0;
	Control ^= HasMessageType;
	return BC_OK;
}

void NPDU::SetPriority(U8 Priority)
{
	Control = ((Control & ~0x03) | (Priority & 0x03));
}

void NPDU::SetResponseRequired(bool NeedResponse)
{
	if(NeedResponse)
	{
		Control |= NeedsReply;
	}
	else
	{
		Control &= ~NeedsReply;
	}
}

bool NPDU::IsResponseRequired() const
{
	return (Control & NeedsReply) == NeedsReply;
}

bool NPDU::HasDADR() const
{
	return (Control & HasDNET) == HasDNET;
}

bool NPDU::HasSADR() const
{
	return (Control & HasSNET) == HasSNET;
}

bool NPDU::HasNetworkMessage() const
{
	return (Control & HasMessageType) == HasMessageType;
}

U8 NPDU::GetPriority() const
{
	return (Control & 0x03);
}

Address NPDU::GetSADR() const
{
	return SADR;
}

Address NPDU::GetDADR() const
{
	return DADR;
}

U8 NPDU::GetNetworkMessage() const
{
	return MsgType;
}

U16 NPDU::GetVendorID() const
{
	return VendorID;
}

U8 NPDU::GetHopCount() const
{
	return HopCount;
}

U32 NPDU::GetNPDULength() const
{
	return length;
}

BACnetResult NPDU::Write(CObjectPtr<IBACnetBuffer> txbuf)
{
	//first write version/control.
	txbuf->WriteByte(Version);
	txbuf->WriteByte(Control);
	if(Control&HasDNET)
	{
		txbuf->WriteShort(DADR.NetID, true);
		txbuf->WriteByte(DADR.AddrLen);
		txbuf->Write(DADR.AddrLen, DADR.Addr);
	}
	if(Control&HasSNET)
	{
		txbuf->WriteShort(SADR.NetID, true);
		txbuf->WriteByte(SADR.AddrLen);
		txbuf->Write(SADR.AddrLen, SADR.Addr);
	}
	if(Control&HasDNET)
	{
		txbuf->WriteByte(HopCount);
	}
	if(Control & HasMessageType)
	{
		txbuf->WriteByte(MsgType);
		if(MsgType & 0x80)
		{
			txbuf->WriteShort(VendorID, true);
		}
	}
	return BC_OK;
}

BACnetResult NPDU::Read(CObjectPtr<IBACnetBuffer> rxbuf)
{
	rxbuf->ReadByte(Version);
	rxbuf->ReadByte(Control);
	length = 2;
	if(Control & HasDNET)
	{
		//Read the net.
		rxbuf->ReadShort(DADR.NetID, true);
		rxbuf->ReadByte(DADR.AddrLen);
		length += 3;
		rxbuf->Read(DADR.AddrLen, DADR.Addr);
		length += DADR.AddrLen;
	}
	if(Control & HasSNET)
	{
		rxbuf->ReadShort(SADR.NetID, true);
		rxbuf->ReadByte(SADR.AddrLen);
		length += 3;
		rxbuf->Read(SADR.AddrLen, SADR.Addr);
		length += SADR.AddrLen;
	}
	if(Control & HasDNET)
	{
		rxbuf->ReadByte(HopCount);
		++length;
	}
	if(Control & HasMessageType)
	{
		rxbuf->ReadByte(MsgType);
		++length;
		if(MsgType & 0x80)
		{
			rxbuf->ReadShort(VendorID, true);
			length += 2;
		}
	}
	return BC_OK;
}
