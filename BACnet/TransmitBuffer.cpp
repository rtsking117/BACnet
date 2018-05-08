#include "TransmitBuffer.h"



TransmitBuffer::TransmitBuffer():totlen(0)
{
}

TransmitBuffer::~TransmitBuffer()
{
}

CObjectPtr<IBACnetTransmitBuffer> CreateBACnetTransmitBuffer()
{
	return CObjectPtr<IBACnetTransmitBuffer>(new TransmitBuffer(), true);
}

BACnetResult TransmitBuffer::Clear()
{
	buflist.clear();
	totlen = 0;
	return BC_OK;
}

BACnetResult TransmitBuffer::Push(CObjectPtr<IBACnetBuffer> pNewBuffer)
{
	buflist.push_front(pNewBuffer);
	totlen += pNewBuffer->GetSize();
	return BC_OK;
}

BACnetResult TransmitBuffer::Pop()
{
	CObjectPtr<IBACnetBuffer> b = buflist.front();
	buflist.pop_front();
	totlen -= b->GetSize();
	return BC_OK;
}

U32 TransmitBuffer::GetNumBuffers() const
{
	return (U32)buflist.size();
}

U32 TransmitBuffer::GetTotalBufferLength() const
{
	return totlen;
}

CObjectPtr<IBACnetBuffer> TransmitBuffer::GetBuffer(U32 BufferIndex) const
{
	if(BufferIndex >= buflist.size()) return nullptr;
	auto it = buflist.begin();
	while(BufferIndex--) { ++it; }
	return *it;
}

BACnetResult TransmitBuffer::ReadBufferList(CObjectPtr<IBACnetBuffer>* const pBufferList, U32 NumElements) const
{
	if(NumElements < buflist.size())
	{
		return BCE_NOT_ENOUGH_BUFFERS;
	}
	auto tmplist = pBufferList;
	for(auto it = buflist.begin(); it != buflist.end(); ++it)
	{
		*tmplist++ = (*it);
	}
	return BC_OK;
}

CObjectPtr<IBACnetBuffer> TransmitBuffer::CoalesceBuffers() const
{
	if(!totlen) return nullptr;
	CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(totlen);
	for(auto it = buflist.begin(); it != buflist.end(); ++it)
	{
		buf->Write((*it)->GetSize(),*it);
	}
	return buf;
}
