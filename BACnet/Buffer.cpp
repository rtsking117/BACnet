#include "Buffer.h"


Buffer::Buffer(U32 sz, const U8* const idata) :
	data(nullptr),
	len(sz),
	rindex(0),
	windex(0)
{
	data = (U8*)malloc(len);
	if(idata)
	{
		memcpy(data, idata, len);
		windex = len;
	}
	else
	{
		Clear();
	}
}

Buffer::~Buffer()
{
	free(data);
	data = nullptr;
	windex = rindex = len = 0;
}

U8* Buffer::GetData(U32 offset) const
{
	if(offset > windex || !data)
	{
		return nullptr;
	}
	return data+offset;
}

U8* Buffer::GetDataForWrite(U32 offset) const
{
	if(offset > len || !data)
	{
		return nullptr;
	}
	return data + offset;
}

BACnetResult Buffer::Clear(void)
{
	if(!data)
	{
		return BCE_INVALID_POINTER;
	}
	memset(data, 0, len);
	windex = rindex = 0;
	return BC_OK;
}

U32 Buffer::GetSize(void) const
{
	return windex;
}

void* Buffer::GetBuffer() const
{
	return GetData(rindex);
}

U32 Buffer::GetRemainingSize() const
{
	return windex - rindex;
}

U32 Buffer::GetAllocatedSize() const
{
	return len;
}

BACnetResult Buffer::MoveReadHead(I32 iOffset, U32 * const pNewPosition)
{
	U32 noffset = (rindex + iOffset);
	BACnetResult ret = BC_OK;
	if(noffset > windex || noffset < 0)
	{
		if(iOffset < 0)
		{
			rindex = 0;
		}
		else
		{
			rindex = windex;
		}
		ret = BCS_OFFSET_CLAMPED;
	}
	else
	{
		rindex = noffset;
	}
	if(pNewPosition) *pNewPosition = rindex;
	return ret;
}

BACnetResult Buffer::MoveWriteHead(I32 iOffset, U32 * const pNewPosition)
{
	U32 noffset = (windex + iOffset);
	BACnetResult ret = BC_OK;
	if(noffset > len || noffset < 0)
	{
		if(iOffset < 0)
		{
			windex = 0;
		}
		else
		{
			windex = len;
		}
		ret = BCS_OFFSET_CLAMPED;
	}
	else
	{
		windex = noffset;
	}
	if(pNewPosition) *pNewPosition = windex;
	if(rindex > windex)
	{
		rindex = windex;
	}
	return ret;
}

void Buffer::ResetReadHead()
{
	rindex = 0;
}

BACnetResult Buffer::ExpandBuffer(U32 uiAmountToExpand)
{
	U8* temp = data;
	if(len + uiAmountToExpand < len)
	{
		//integer overflow.
		return BCE_BUFFER_TOO_LONG;
	}
	data = (U8*)malloc(len);
	if(!data)
	{
		data = temp;
		len -= uiAmountToExpand;
		return BCE_OUT_OF_MEMORY;
	}
	memset(data, 0, len);
	memcpy(data, temp, windex);
	free(temp);
	return BC_OK;
}

BACnetResult Buffer::Read(U32 uiNumBytes, U8 * const pData)
{
	if(!pData)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(!uiNumBytes) return BCS_NO_OPERATION;
	U32 l = windex - rindex;
	if(uiNumBytes > l)
	{
		return BCE_NOT_ENOUGH_DATA;
	}
	memcpy(pData, GetData(rindex), uiNumBytes);
	rindex += uiNumBytes;
	return BC_OK;
}

BACnetResult Buffer::Read(U32 uiNumBytes, CObjectPtr<IBACnetBuffer> pBuffer)
{
	if(!pBuffer)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(!uiNumBytes) return BCS_NO_OPERATION;
	U32 l = windex - rindex;
	if(uiNumBytes > l)
	{
		return BCE_NOT_ENOUGH_DATA;
	}
	BACnetResult r = pBuffer->Write(uiNumBytes, GetData(rindex));
	if(BCE_SUCCEEDED(r))
	{
		rindex += uiNumBytes;
	}
	return r;
}

BACnetResult Buffer::ReadByte(U8 & uiData)
{
	return Read(sizeof(uiData), &uiData);
}

BACnetResult Buffer::ReadShort(U16 & usData, bool ByteFlip)
{
	BACnetResult r = Read(sizeof(usData), (U8*)&usData);
	if(ByteFlip && BCE_SUCCEEDED(r))
	{
		usData = ToHost16(usData);
	}
	return r;
}

BACnetResult Buffer::ReadInt(U32 & uiData, bool ByteFlip)
{
	BACnetResult r = Read(sizeof(uiData), (U8*)&uiData);
	if(ByteFlip && BCE_SUCCEEDED(r))
	{
		uiData = ToHost32(uiData);
	}
	return r;
}

BACnetResult Buffer::ReadInt64(U64 & ullData, bool ByteFlip)
{
	BACnetResult r = Read(sizeof(ullData), (U8*)&ullData);
	if(ByteFlip && BCE_SUCCEEDED(r))
	{
		ullData = ToHost64(ullData);
	}
	return r;
}

BACnetResult Buffer::Write(U32 uiNumBytes, const U8 * const pData)
{
	if(!pData)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(!uiNumBytes) return BCS_NO_OPERATION;
	if(uiNumBytes > (len - windex))
	{
		U32 expand = (windex + uiNumBytes) - len;
		if(expand < 32)
		{
			expand = 32;
		}
		if(len < (expand << 1) && len > expand)
		{
			expand = len;
		}
		BACnetResult r = ExpandBuffer(expand);
		if(BCE_FAILED(r))
		{
			return r;
		}
	}
	memcpy(GetDataForWrite(windex), pData, uiNumBytes);
	windex += uiNumBytes;
	return BC_OK;
}

BACnetResult Buffer::Write(U32 uiNumBytes, CObjectPtr<IBACnetBuffer> pBuffer)
{
	if(!pBuffer)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(!uiNumBytes) return BCS_NO_OPERATION;
	if(uiNumBytes > (len - windex))
	{
		U32 expand = (windex + uiNumBytes) - len;
		if(expand < 32)
		{
			expand = 32;
		}
		if(len < (expand << 1) && len > expand)
		{
			expand = len;
		}
		BACnetResult r = ExpandBuffer(expand);
		if(BCE_FAILED(r))
		{
			return r;
		}
	}
	BACnetResult r = pBuffer->Read(uiNumBytes, GetData(windex));
	if(BCE_SUCCEEDED(r))
	{
		windex += uiNumBytes;
	}
	return r;
}

BACnetResult Buffer::WriteByte(U8 uiData)
{
	return Write(sizeof(uiData), &uiData);
}

BACnetResult Buffer::WriteShort(U16 usData, bool ByteFlip)
{
	if(ByteFlip)
	{
		usData = ToNet16(usData);
	}
	return Write(sizeof(usData), (U8*)&usData);
}

BACnetResult Buffer::WriteInt(U32 uiData, bool ByteFlip)
{
	if(ByteFlip)
	{
		uiData = ToNet32(uiData);
	}
	return Write(sizeof(uiData), (U8*)&uiData);
}

BACnetResult Buffer::WriteInt64(U64 ullData, bool ByteFlip)
{
	if(ByteFlip)
	{
		ullData = ToNet64(ullData);
	}
	return Write(sizeof(ullData), (U8*)&ullData);
}

CObjectPtr<IBACnetBuffer>
CreateBACnetBuffer(
	U32 uiBufferSize,
	const U8* const pInitialData)
{
	if(!uiBufferSize)
	{
		return nullptr;
	}
	CObjectPtr<IBACnetBuffer> temp;
	try
	{
		temp = CObjectPtr<IBACnetBuffer>(new Buffer(uiBufferSize, pInitialData), true);
	}
	catch(BACnetException e)
	{
		return nullptr;
	}
	return temp;
}