#pragma once
#include "ComWrapper.h"
#include <Windows.h>

class CThreadpoolTimer :
	public ComWrapper<IBACnetThreadpoolTimer>
{
	TimerCallbackFunction callback;
	CObjectPtr<IBACnetThreadPool> tp;
	PTP_TIMER timer;

	void TimerEntry(CallbackHandle h, PTP_TIMER t);

public:
	CThreadpoolTimer(TimerCallbackFunction pCallback, CObjectPtr<IBACnetThreadPool> pThreadPool, PTP_CALLBACK_ENVIRON env);
	~CThreadpoolTimer();

	BACnetResult BACNETMETHODCALLTYPE WaitUntil(I64 AbsoluteTime, U32 MaxAllowedDelay = 100, U32 RepeatAfter = 0);
	BACnetResult BACNETMETHODCALLTYPE WaitFor(I64 RelativeTime, U32 MaxAllowedDelay = 100, U32 RepeatAfter = 0);
	BACnetResult BACNETMETHODCALLTYPE Cancel();
};

