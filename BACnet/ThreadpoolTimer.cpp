#include "ThreadpoolTimer.h"



void CThreadpoolTimer::TimerEntry(CallbackHandle h, PTP_TIMER t)
{
	//just double check - is this us?
	if(t != timer)
	{
		//uhhhh.....
		return;
	}
	//call our timer callback.
	BACnetResult r = callback(tp, h, this);
	if(BCE_FAILED(r))
	{
		//Log it.
	}
}

CThreadpoolTimer::CThreadpoolTimer(TimerCallbackFunction pCallback, CObjectPtr<IBACnetThreadpool> pThreadPool, PTP_CALLBACK_ENVIRON env) :
	timer(nullptr),
	callback(pCallback),
	tp(pThreadPool)
{
	timer = CreateThreadpoolTimer([](PTP_CALLBACK_INSTANCE cbh, void* param, PTP_TIMER timer)
	{
		CThreadpoolTimer* me = (CThreadpoolTimer*)param;
		me->TimerEntry(cbh, timer);
	}, this, env);
}


CThreadpoolTimer::~CThreadpoolTimer()
{
	Cancel();
	CloseThreadpoolTimer(timer);
}

BACnetResult BACNETMETHODCALLTYPE CThreadpoolTimer::WaitUntil(I64 AbsoluteTime, U32 MaxAllowedDelay, U32 RepeatAfter)
{
	LARGE_INTEGER li;
	if(AbsoluteTime < 0)
	{
		li.QuadPart = -AbsoluteTime;
	}
	else
	{
		li.QuadPart = AbsoluteTime;
	}
	FILETIME duetime;
	duetime.dwHighDateTime = li.HighPart;
	duetime.dwLowDateTime = li.LowPart;
	SetThreadpoolTimerEx(timer, &duetime, RepeatAfter, MaxAllowedDelay);
	return BC_OK;
}

BACnetResult BACNETMETHODCALLTYPE CThreadpoolTimer::WaitFor(I64 RelativeTime, U32 MaxAllowedDelay, U32 RepeatAfter)
{
	LARGE_INTEGER li;
	if(RelativeTime < 0)
	{
		li.QuadPart = RelativeTime;
	}
	else
	{
		li.QuadPart = -RelativeTime;
	}
	FILETIME duetime;
	duetime.dwHighDateTime = li.HighPart;
	duetime.dwLowDateTime = li.LowPart;
	SetThreadpoolTimerEx(timer, &duetime, RepeatAfter, MaxAllowedDelay);
	return BC_OK;
}

BACnetResult BACNETMETHODCALLTYPE CThreadpoolTimer::Cancel()
{
	SetThreadpoolTimerEx(timer, nullptr, 0, 0);
	return BC_OK;
}


CObjectPtr<IBACnetThreadpoolTimer> CreateBACnetThreadpoolTimer(TimerCallbackFunction pTimerCallback)
{
	return CObjectPtr<IBACnetThreadpoolTimer>(new CThreadpoolTimer(pTimerCallback, nullptr, nullptr), true);
}
