#pragma once

#include <Windows.h>

#include "BACnetMSTP.h"
#include <ComWrapper.h>

//ASHRAE 135-2012, 9.5.4

class MSTPMaster :
	public ComWrapper<IBACnetMSTPPort>
{
	//these are organized to maximize structure packing
	// and alignment.
	CObjectPtr<IBACnetBuffer> sendbuf;
	CObjectPtr<IBACnetBuffer> recvbuf;
	CObjectPtr<IBACnetEvent> RequestToSend;
	CObjectPtr<IBACnetEvent> FrameSent;
	CObjectPtr<IBACnetEvent> DataAvailable;
	CObjectPtr<IBACnetThread> MasterThread;
	CObjectPtr<IBACnetThread> LineDriverThread;
	U8* InputBuffer;
	U8* tmpbuf;
	U32 InputBufferSize;
	U32 tmpbufsize;
	U32 DataLength;
	U32 EventCount;
	U32 FrameCount;
	U32 Index;
	U32 SilenceTimer;
	U32 TokenCount;
	BACnetResult SendError;
	BACnetResult ReceiveError;
	U16 DataCRC;
	U8 SourceAddress;
	U8 TS;
	U8 NS;
	U8 PS;
	U8 DestinationAddress;
	U8 HeaderCRC;
	U8 RetryCount;
	bool RecievedInvalidFrame;
	bool RecievedValidFrame;
	bool SoleMaster;
	//Constants
	static const U32 NPoll = 50; //number of tokens prior to poll
	static const U32 NRetries = 1; //number of token retries
	static const U32 NMinOctets = 4; //number of events to activate
	static const U32 TFrameAbort = 60; //bit times, 6 bytes.
	static const U32 TFrameGap = 20; //bit times, 2 bytes.
	static const U32 TNoToken = 500; //ms.
	static const U32 TPostdrive = 15; //bit times, 1.5 bytes.
	static const U32 TReplyDelay = 250; //ms.
	static const U32 TReplyTimeout = 300; //ms.
	static const U32 TRoff = 39; //bit times, 3.9 bytes (~4 bytes).
	static const U32 TSlot = 10; //ms.
	static const U32 TTurnaround = 40; //bit times, 4 bytes.
	static const U32 TUsageDelay = 15; //ms.
	static const U32 TUsageTimeout = 50; //ms.

	BACnetResult LineDriver(CObjectPtr<IBACnetThread> thread);
	BACnetResult MasterStateMachine(CObjectPtr<IBACnetThread> thread);

public:
	MSTPMaster();
	~MSTPMaster();

	//IBACnetStackComponent
	BACnetResult BACNETMETHODCALLTYPE Start();
	BACnetResult BACNETMETHODCALLTYPE Stop();
	//IBACnetPort
	BACnetResult BACNETMETHODCALLTYPE WriteMessage(CObjectPtr<IBACnetAddress> pDestinationAddress, CObjectPtr<IBACnetBuffer> pMessage, bool WaitForTransmit = false);
	CObjectPtr<IBACnetAddress> BACNETMETHODCALLTYPE CreateAddress(U32 AddressSize, const U8* const AddressDataBuffer = nullptr) const;
	CObjectPtr<IBACnetAddress> BACNETMETHODCALLTYPE GetBroadcastAddress() const;
	BACnetAddressType BACNETMETHODCALLTYPE GetAddressType() const { return Address_MSTP; }
	U32 BACNETMETHODCALLTYPE GetMaxAPDULength() const { return 501; }
	U32 BACNETMETHODCALLTYPE GetMaxTransmitLength() const { return 501; }
	U32 BACNETMETHODCALLTYPE GetMaxHeaderLength() const;
	BACnetResult BACNETMETHODCALLTYPE RegisterReceiverCallback(ReceiverCallbackFunction pCallback);
	BACnetResult BACNETMETHODCALLTYPE RemoveReceiverCallback();
	//IBACnetMSTPMaster


};

const int x = sizeof(MSTPMaster);