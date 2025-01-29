#pragma once
#include "ObjectWrapper.h"
#include <vector>

class CSegmentBuffer
{
	std::vector<CObjectPtr<IBACnetBuffer>> segbuf;
	U32 CurrentWindowIndex;
	U32 TotalLength;
public:
	CSegmentBuffer();
	~CSegmentBuffer();

	U32 GetNumSegments() const;
	void PushSegment(CObjectPtr<IBACnetBuffer> pBuffer);
	CObjectPtr<IBACnetBuffer> GetSegmentFromWindow(U8 WindowIndex);
	void ShiftSegmentWindow(U8 WindowShift);
	void EmptySegmentBuffer();
	bool IsWindowIndexValid(U8 WindowIndex);
	CObjectPtr<IBACnetBuffer> CoalesceSegments();

	bool IsSegmentedData();
};

