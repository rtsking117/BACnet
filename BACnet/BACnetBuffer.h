#pragma once

#include "BACnetInterface.h"

#ifndef __IBACnetBuffer__FWD_DEFINED__
#define __IBACnetBuffer__FWD_DEFINED__
typedef struct IBACnetBuffer IBACnetBuffer;
#endif

#ifndef __IBACnetTransmitBuffer__FWD_DEFINED__
#define __IBACnetTransmitBuffer__FWD_DEFINED__
typedef struct IBACnetTransmitBuffer IBACnetTransmitBuffer;
#endif

BACNET_INTERFACE("{6705ED1C-6B33-4430-8910-A3B971F3E1A8}")
IBACnetBuffer: public IBACnetUnknown
{
	BCNMETHODTYPE(U32, GetSize() const) BCPURE;
	BCNMETHODTYPE(void*, GetBuffer() const) BCPURE;
	BCNMETHODTYPE(U32, GetRemainingSize() const) BCPURE;
	BCNMETHODTYPE(U32, GetAllocatedSize() const) BCPURE;
	BCNMETHOD(MoveReadHead(I32 iOffset, U32* const pNewPosition = nullptr)) BCPURE;
	BCNMETHOD(MoveWriteHead(I32 iOffset, U32* const pNewPosition = nullptr)) BCPURE;
	BCNMETHODTYPE(void, ResetReadHead()) BCPURE;
	BCNMETHOD(Clear()) BCPURE;
	BCNMETHOD(ExpandBuffer(U32 uiAmountToExpand)) BCPURE;
	BCNMETHOD(Read(U32 uiNumBytes, U8* const pData)) BCPURE;
	BCNMETHOD(Read(U32 uiNumBytes, CObjectPtr<IBACnetBuffer> pBuffer)) BCPURE;
	BCNMETHOD(ReadByte(U8& uiData)) BCPURE;
	BCNMETHOD(ReadShort(U16& usData, bool ByteFlip = false)) BCPURE;
	BCNMETHOD(ReadInt(U32& uiData, bool ByteFlip = false)) BCPURE;
	BCNMETHOD(ReadInt64(U64& ullData, bool ByteFlip = false)) BCPURE;
	BCNMETHOD(Write(U32 uiNumBytes, const U8* const pData)) BCPURE;
	BCNMETHOD(Write(U32 uiNumBytes, CObjectPtr<IBACnetBuffer> pBuffer)) BCPURE;
	BCNMETHOD(WriteByte(U8 uiData)) BCPURE;
	BCNMETHOD(WriteShort(U16 usData, bool ByteFlip = false)) BCPURE;
	BCNMETHOD(WriteInt(U32 uiData, bool ByteFlip = false)) BCPURE;
	BCNMETHOD(WriteInt64(U64 ullData, bool ByteFlip = false)) BCPURE;
};

CObjectPtr<IBACnetBuffer>
BACNET_ENTRYPOINT
CreateBACnetBuffer(const U32 BufferLength, const U8* const pBuffer = nullptr);

//BACNET_INTERFACE("{0F2F7AD6-02F7-4190-B4B0-0F6463983CB8}")

//BACNET_INTERFACE("{0F2F7AD6-02F7-4190-B4B0-0F6463983CB8}")

BACNET_INTERFACE("{6E5863F3-CFFD-434C-A1EF-48ECB61C7DC6}")
IBACnetTransmitBuffer: public IBACnetUnknown
{
	BCNMETHOD(Clear()) BCPURE;
	BCNMETHOD(Push(CObjectPtr<IBACnetBuffer> pNewBuffer)) BCPURE;
	BCNMETHOD(Pop()) BCPURE;
	BCNMETHODTYPE(U32, GetNumBuffers() const) BCPURE;
	BCNMETHODTYPE(U32, GetTotalBufferLength() const) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetBuffer>, GetBuffer(U32 BufferIndex) const) BCPURE;
	BCNMETHOD(ReadBufferList(CObjectPtr<IBACnetBuffer>* const pBufferList, U32 NumElements) const) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetBuffer>, CoalesceBuffers() const) BCPURE;
};

//07B - B01 - 3JVCRY

CObjectPtr<IBACnetTransmitBuffer>
BACNET_ENTRYPOINT
CreateBACnetTransmitBuffer();