#pragma once

enum PDUTypes
{
	PDUType_ConfirmedRequest,
	PDUType_UnconfirmedRequest,
	PDUType_SimpleAck,
	PDUType_ComplexAck,
	PDUType_SegmentAck,
	PDUType_Error,
	PDUType_Reject,
	PDUType_Abort,
};

enum PDUFlags
{
	PDUFlag_IsSegmented = 0x08,
	PDUFlag_MoreFollows = 0x04,
	PDUFlag_SegmentResponse = 0x02,
	PDUFlag_SegmentNAK = 0x02,
	PDUFlag_IsServer = 0x01,
};

enum MaxSegments
{
	MaxSeg_Unspecified = 0,
	MaxSeg_2 = 1,
	MaxSeg_4 = 2,
	MaxSeg_8 = 3,
	MaxSeg_16 = 4,
	MaxSeg_32 = 5,
	MaxSeg_64 = 6,
	MaxSeg_Infinite = 7,
};

enum MaxAPDU
{
	MaxAPDU_MinSize = 0,
	MaxAPDU_128 = 1,
	MaxAPDU_206 = 2,
	MaxAPDU_480 = 3,
	MaxAPDU_1024 = 4,
	MaxAPDU_1476 = 5,
};


const U16 MaxAPDUTable[] = {
	50,
	128,
	206,
	480,
	1024,
	1476,
};