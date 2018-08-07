#pragma once
#include "BACnetInterface.h"
#include "ObjectWrapper.h"

class Buffer :
	public ObjectWrapper < IBACnetBuffer >
{
	U8* data;
	//0 <= rindex <= windex <= len
	U32 len;
	U32 rindex;
	U32 windex;

public:
	Buffer(U32 sz, const U8* const data);
	~Buffer();

	U8* GetData(U32 offset = 0) const;
	U8 * GetDataForWrite(U32 offset = 0) const;

	BACnetResult BACNETMETHODCALLTYPE Clear();
	U32 BACNETMETHODCALLTYPE GetSize() const;
	void* BACNETMETHODCALLTYPE GetBuffer() const;
	U32 BACNETMETHODCALLTYPE GetRemainingSize() const;
	U32 BACNETMETHODCALLTYPE GetAllocatedSize() const;
	BACnetResult BACNETMETHODCALLTYPE MoveReadHead(I32 iOffset, U32* const pNewPosition = nullptr);
	BACnetResult BACNETMETHODCALLTYPE MoveWriteHead(I32 iOffset, U32* const pNewPosition = nullptr);
	void BACNETMETHODCALLTYPE ResetReadHead();
	BACnetResult BACNETMETHODCALLTYPE ExpandBuffer(U32 uiAmountToExpand);
	BACnetResult BACNETMETHODCALLTYPE Read(U32 uiNumBytes, U8* const pData);
	BACnetResult BACNETMETHODCALLTYPE Read(U32 uiNumBytes, CObjectPtr<IBACnetBuffer> pBuffer);
	BACnetResult BACNETMETHODCALLTYPE ReadByte(U8& uiData);
	BACnetResult BACNETMETHODCALLTYPE ReadShort(U16& usData, bool ByteFlip = false);
	BACnetResult BACNETMETHODCALLTYPE ReadInt(U32& uiData, bool ByteFlip = false);
	BACnetResult BACNETMETHODCALLTYPE ReadInt64(U64& ullData, bool ByteFlip = false);
	BACnetResult BACNETMETHODCALLTYPE Write(U32 uiNumBytes, const U8* const pData);
	BACnetResult BACNETMETHODCALLTYPE Write(U32 uiNumBytes, CObjectPtr<IBACnetBuffer> pBuffer);
	BACnetResult BACNETMETHODCALLTYPE WriteByte(U8 uiData);
	BACnetResult BACNETMETHODCALLTYPE WriteShort(U16 usData, bool ByteFlip = false);
	BACnetResult BACNETMETHODCALLTYPE WriteInt(U32 uiData, bool ByteFlip = false);
	BACnetResult BACNETMETHODCALLTYPE WriteInt64(U64 ullData, bool ByteFlip = false);
};

