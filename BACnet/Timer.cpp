#include "Timer.h"



CTimer::CTimer(bool ManualReset):
	timer(CreateWaitableTimer(nullptr, ManualReset, nullptr))
{
}


CTimer::~CTimer()
{
	CloseHandle(timer);
	timer = INVALID_HANDLE_VALUE;
}

BACnetResult BACNETMETHODCALLTYPE CTimer::WaitUntil(I64 AbsoluteTime, U32 RepeatAfter)
{
	LARGE_INTEGER duetime;
	if(AbsoluteTime < 0)
	{
		duetime.QuadPart = -AbsoluteTime;
	}
	else
	{
		duetime.QuadPart = AbsoluteTime;
	}
	SetWaitableTimer(timer, &duetime, RepeatAfter, nullptr, nullptr, FALSE);
	return BC_OK;
}

BACnetResult BACNETMETHODCALLTYPE CTimer::WaitFor(I64 RelativeTime, U32 RepeatAfter)
{
	LARGE_INTEGER duetime;
	if(RelativeTime < 0)
	{
		duetime.QuadPart = RelativeTime;
	}
	else
	{
		duetime.QuadPart = -RelativeTime;
	}
	SetWaitableTimer(timer, &duetime, RepeatAfter, nullptr, nullptr, FALSE);
	return BC_OK;
}

BACnetResult BACNETMETHODCALLTYPE CTimer::Cancel()
{
	CancelWaitableTimer(timer);
	return BC_OK;
}

CObjectPtr<IBACnetTimer> CreateBACnetTimer(bool ManualReset)
{
	return CObjectPtr<IBACnetTimer>(new CTimer(ManualReset), true);
}
