#pragma once
#include "ComWrapper.h"
#include <Windows.h>

class CTimer :
	public ComWrapper<IBACnetTimer>
{
	HANDLE timer;
public:
	CTimer(bool ManualReset);
	~CTimer();

	void* BACNETMETHODCALLTYPE GetWaitHandle() const { return timer; }
	BACnetResult BACNETMETHODCALLTYPE WaitUntil(I64 AbsoluteTime, U32 RepeatAfter = 0);
	BACnetResult BACNETMETHODCALLTYPE WaitFor(I64 RelativeTime, U32 RepeatAfter = 0);
	BACnetResult BACNETMETHODCALLTYPE Cancel();
};

