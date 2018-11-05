#pragma once
#include "ObjectWrapper.h"
#include <Windows.h>

class CThreadpoolTimer :
	public ObjectWrapper<IBACnetThreadpoolTimer>
{
	TimerCallbackFunction callback;
	CObjectPtr<IBACnetThreadpool> tp;
	PTP_TIMER timer;

	void TimerEntry(CallbackHandle h, PTP_TIMER t);

public:
	CThreadpoolTimer(TimerCallbackFunction pCallback, CObjectPtr<IBACnetThreadpool> pThreadPool, PTP_CALLBACK_ENVIRON env);
	~CThreadpoolTimer();

	BACnetResult BACNETMETHODCALLTYPE WaitUntil(I64 AbsoluteTime, U32 MaxAllowedDelay = 100, U32 RepeatAfter = 0);
	BACnetResult BACNETMETHODCALLTYPE WaitFor(I64 RelativeTime, U32 MaxAllowedDelay = 100, U32 RepeatAfter = 0);
	BACnetResult BACNETMETHODCALLTYPE Cancel();
};

