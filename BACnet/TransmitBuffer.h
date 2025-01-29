#pragma once

#include "BACnetInterface.h"
#include "ObjectWrapper.h"
#include <list>


class TransmitBuffer :
	public ObjectWrapper<IBACnetTransmitBuffer>
{
	std::list<CObjectPtr<IBACnetBuffer>> buflist;
	U32 totlen;

public:
	TransmitBuffer();
	~TransmitBuffer();

	BACnetResult BACNETMETHODCALLTYPE Clear();
	BACnetResult BACNETMETHODCALLTYPE Push(CObjectPtr<IBACnetBuffer> pNewBuffer);
	BACnetResult BACNETMETHODCALLTYPE Pop();
	U32 BACNETMETHODCALLTYPE GetNumBuffers() const;
	U32 BACNETMETHODCALLTYPE GetTotalBufferLength() const;
	CObjectPtr<IBACnetBuffer> BACNETMETHODCALLTYPE GetBuffer(U32 BufferIndex) const;
	BACnetResult BACNETMETHODCALLTYPE ReadBufferList(CObjectPtr<IBACnetBuffer>* const pBufferList, U32 NumElements) const;
	CObjectPtr<IBACnetBuffer> BACNETMETHODCALLTYPE CoalesceBuffers() const;
};

