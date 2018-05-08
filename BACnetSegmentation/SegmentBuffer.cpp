#include "SegmentBuffer.h"



CSegmentBuffer::CSegmentBuffer():
	segbuf(),
	TotalLength(0),
	CurrentWindowIndex(0)
{
}

CSegmentBuffer::~CSegmentBuffer()
{
}

U32 CSegmentBuffer::GetNumSegments() const
{
	return (U32)segbuf.size();
}

void CSegmentBuffer::PushSegment(CObjectPtr<IBACnetBuffer> pBuffer)
{
	segbuf.push_back(pBuffer);
	TotalLength += pBuffer->GetSize();
}

CObjectPtr<IBACnetBuffer> CSegmentBuffer::GetSegmentFromWindow(U8 WindowIndex)
{
	if(CurrentWindowIndex + WindowIndex > segbuf.size())
	{
		return nullptr;
	}
	return segbuf.at(CurrentWindowIndex + WindowIndex);
}

void CSegmentBuffer::ShiftSegmentWindow(U8 WindowShift)
{
	if(CurrentWindowIndex + WindowShift < segbuf.size())
	{
		CurrentWindowIndex += WindowShift;
	}
	CurrentWindowIndex = (U32)segbuf.size();
}

void CSegmentBuffer::EmptySegmentBuffer()
{
	segbuf.clear();
	CurrentWindowIndex = 0;
	TotalLength = 0;
}

bool CSegmentBuffer::IsWindowIndexValid(U8 WindowIndex)
{
	return (CurrentWindowIndex + WindowIndex) < segbuf.size();
}

CObjectPtr<IBACnetBuffer> CSegmentBuffer::CoalesceSegments()
{
	if(!segbuf.size())
	{
		return nullptr;
	}
	if(segbuf.size() == 1)
	{
		auto ret = segbuf.front();
		EmptySegmentBuffer();
		return ret;
	}
	else
	{
		CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(TotalLength);
		for each(auto seg in segbuf)
		{
			buf->Write(seg->GetSize(), seg);
		}
		EmptySegmentBuffer();
		return buf;
	}
}

bool CSegmentBuffer::IsSegmentedData()
{
	return (segbuf.size() == 1);
}
