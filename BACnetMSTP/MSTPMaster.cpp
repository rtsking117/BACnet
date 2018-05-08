#include "MSTPMaster.h"
#include <process.h>
#include <functional>

MSTPMaster::MSTPMaster():
	sendbuf(nullptr),
	recvbuf(nullptr),
	RequestToSend(CreateBACnetEvent(true, false)),
	FrameSent(CreateBACnetEvent(true, false)),
	DataAvailable(CreateBACnetEvent(true, false)),
	MasterThread(CreateBACnetThread(std::bind(&MSTPMaster::MasterStateMachine, this, std::placeholders::_1))),
	LineDriverThread(CreateBACnetThread(std::bind(&MSTPMaster::LineDriver, this, std::placeholders::_1))),
	tmpbuf(nullptr),
	InputBuffer(nullptr),
	InputBufferSize(0),
	tmpbufsize(0),
	DataLength(0),
	EventCount(0),
	FrameCount(0),
	Index(0),
	SilenceTimer(0),
	TokenCount(0),
	DataCRC(0),
	SourceAddress(0),
	TS(0),	//User Init
	NS(0),
	PS(0),
	DestinationAddress(0),
	HeaderCRC(0),
	RetryCount(0), //Standard sets this
	RecievedInvalidFrame(false),
	RecievedValidFrame(false),
	SoleMaster(false)
{
	if(InputBufferSize == 0)
	{
		InputBufferSize = 512; //512 byte buffer for receiving frames.
	}
	InputBuffer = (U8*)calloc(InputBufferSize, sizeof(U8));
	tmpbuf = (U8*)calloc(tmpbufsize = 1024, sizeof(U8)); //1K buffer for send buffer construction.
}


MSTPMaster::~MSTPMaster()
{
	free(InputBuffer);
	InputBuffer = nullptr;
	free(tmpbuf);
	tmpbuf = nullptr;
}

U8 CalcHeaderCRC(U8* data, U32 size, U8 crc = 0)
{
	for(U32 i = 0; i < size; ++i)
	{
		//Based on CRC algorithm from BACnet Standard.
		U32 t;
		t = crc ^ data[i];
		t = t ^ (t << 1) ^ (t << 2) ^ (t << 3)
			^ (t << 4) ^ (t << 5) ^ (t << 6)
			^ (t << 7);
		crc = (t & 0xfe) ^ ((t >> 8) & 1);
	}
	return crc;
}

U16 CalcDataCRC(U8* data, U32 size, U16 crc = 0)
{
	for(U32 i = 0; i < size; ++i)
	{
		//Based on CRC algorithm from BACnet Standard.
		U32 crcLow;
		crcLow = (crc & 0xff) ^ data[i];
		crc = (crc >> 8) ^ (crcLow << 8) ^ (crcLow << 3)
			^ (crcLow << 12) ^ (crcLow >> 4)
			^ (crcLow & 0x0f) ^ ((crcLow & 0x0f) << 7);
	}
	return crc;
}
