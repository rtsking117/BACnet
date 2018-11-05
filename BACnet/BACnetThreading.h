#pragma once

#include "BACnetInterface.h"

#ifndef __IBACnetWaitableObject__FWD_DEFINED__
#define __IBACnetWaitableObject__FWD_DEFINED__
typedef struct IBACnetWaitableObject IBACnetWaitableObject;
#endif

#ifndef __IBACnetEvent__FWD_DEFINED__
#define __IBACnetEvent__FWD_DEFINED__
typedef struct IBACnetEvent IBACnetEvent;
#endif

#ifndef __IBACnetMutex__FWD_DEFINED__
#define __IBACnetMutex__FWD_DEFINED__
typedef struct IBACnetMutex IBACnetMutex;
#endif

#ifndef __IBACnetSpinLock__FWD_DEFINED__
#define __IBACnetSpinLock__FWD_DEFINED__
typedef struct IBACnetSpinLock IBACnetSpinLock;
#endif

#ifndef __IBACnetThreadpool__FWD_DEFINED__
#define __IBACnetThreadpool__FWD_DEFINED__
typedef struct IBACnetThreadpool IBACnetThreadpool;
#endif

#ifndef __IBACnetThreadpoolTimer__FWD_DEFINED__
#define __IBACnetThreadpoolTimer__FWD_DEFINED__
typedef struct IBACnetThreadpoolTimer IBACnetThreadpoolTimer;
#endif

#ifndef __IBACnetThread__FWD_DEFINED__
#define __IBACnetThread__FWD_DEFINED__
typedef struct IBACnetThread IBACnetThread;
#endif

BACNET_INTERFACE("{C2561F13-F8B2-4D2C-9D91-B401ABE22798}")
IBACnetWaitableObject : public IBACnetUnknown
{
	BCNMETHODTYPE(void*, GetWaitHandle() const) BCPURE;
};

typedef void* CallbackHandle;

BACNET_INTERFACE("{B339F202-031D-46D6-A826-ADD59E13A5D1}")
IBACnetEvent : public IBACnetWaitableObject
{
	BCNMETHODTYPE(void, Set()) BCPURE;
	BCNMETHODTYPE(void, Reset()) BCPURE;
	BCNMETHODTYPE(bool, IsSet()) BCPURE;
	BCNMETHODTYPE(void, SetOnReturn(CallbackHandle pHandle)) BCPURE;
};

BACNET_INTERFACE("{AA32AC88-14CF-4688-ACD1-1627F1390E56}")
IBACnetMutex : public IBACnetWaitableObject
{
	BCNMETHODTYPE(bool, Lock(U32 msTimeout = (-1))) BCPURE;
	BCNMETHODTYPE(void, Unlock()) BCPURE;
	BCNMETHODTYPE(void, UnlockOnReturn(CallbackHandle pHandle)) BCPURE;
};

BACNET_INTERFACE("{EEF23F65-83E1-43BC-8FA0-2824C0B1F660}")
IBACnetSpinLock : public IBACnetUnknown
{
	BCNMETHODTYPE(void, Lock()) BCPURE;
	BCNMETHODTYPE(bool, TryLock()) BCPURE;
	BCNMETHODTYPE(void, Unlock()) BCPURE;
	BCNMETHODTYPE(void, UnlockOnReturn(CallbackHandle pHandle)) BCPURE;
};

BACNET_INTERFACE("{F136F239-49B5-4D9F-94F1-9E9A343CADA2}")
IBACnetTimer : public IBACnetWaitableObject
{
	BCNMETHOD(WaitUntil(I64 AbsoluteTime, U32 RepeatAfter = 0)) BCPURE;
	BCNMETHOD(WaitFor(I64 RelativeTime, U32 RepeatAfter = 0)) BCPURE;
	BCNMETHOD(Cancel()) BCPURE;
};

BACNET_INTERFACE("{F136F239-49B5-4D9F-94F1-9E9A343CADA2}")
IBACnetThreadpoolTimer : public IBACnetUnknown
{
	BCNMETHOD(WaitUntil(I64 AbsoluteTime, U32 MaxAllowedDelay = 100, U32 RepeatAfter = 0)) BCPURE;
	BCNMETHOD(WaitFor(I64 RelativeTime, U32 MaxAllowedDelay = 100, U32 RepeatAfter = 0)) BCPURE;
	BCNMETHOD(Cancel()) BCPURE;
};

BACnetResult
BACNET_ENTRYPOINT
WaitForObject(CObjectPtr<IBACnetWaitableObject> pObject, U32 msTimeout = (-1));

BACnetResult
BACNET_ENTRYPOINT
WaitForObjects(CObjectPtr<IBACnetWaitableObject> *pObjectList, U32 nObjects, U32& SignaledObject, bool WaitForAll, U32 msTimeout = (-1));

template<size_t size>
inline BACnetResult 
WaitForObjects(CObjectPtr<IBACnetWaitableObject> (&pObjectList)[size], U32& SignaledObject, bool WaitForAll, U32 msTimeout = (-1))
{
	return WaitForObjects(pObjectList, size, SignaledObject, WaitForAll, msTimeout);
}

typedef std::function<BACnetResult(CObjectPtr<IBACnetThreadpool> pPool, CallbackHandle pHandle)> AsyncCallbackFunction;
typedef std::function<BACnetResult(CObjectPtr<IBACnetThreadpool> pPool, CallbackHandle pHandle, CObjectPtr<IBACnetThreadpoolTimer> pTimer)> TimerCallbackFunction;

BACNET_INTERFACE("{D4629B16-4755-4719-93C7-B3D82B1C7181}")
IBACnetThreadpool : public IBACnetUnknown
{
	BCNMETHOD(QueueAsyncCallback(AsyncCallbackFunction pCallbackFunction)) BCPURE;
	BCNMETHODTYPE(bool, CallbackRunsLong(CallbackHandle pHandle)) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetThreadpoolTimer>, CreateThreadpoolTimer(TimerCallbackFunction pTimerCallback)) BCPURE;
};

typedef std::function<BACnetResult(CObjectPtr<IBACnetThread> pThread)> ThreadFunction;

BACNET_INTERFACE("{0E492A84-1F5D-46A7-A467-C182CF6AD467}")
IBACnetThread : public IBACnetWaitableObject
{
	BCNMETHOD(Start()) BCPURE;
	BCNMETHOD(Cancel()) BCPURE;
	BCNMETHODTYPE(bool, IsRunning()) BCPURE;
	BCNMETHODTYPE(CObjectPtr<IBACnetEvent>, GetCancellationEvent()) BCPURE;
	BCNMETHOD(Terminate(BACnetResult TerminationCode)) BCPURE;
	BCNMETHOD(Stop(U32 Timeout = 10000)) BCPURE;
	BCNMETHOD(GetExitCode()) BCPURE;
};

CObjectPtr<IBACnetThread>
BACNET_ENTRYPOINT
CreateBACnetThread(
	ThreadFunction pThreadFunction);

CObjectPtr<IBACnetThreadpool>
BACNET_ENTRYPOINT
CreateThreadpool();

CObjectPtr<IBACnetEvent>
BACNET_ENTRYPOINT
CreateBACnetEvent(
	bool ManualReset,
	bool InitialState);

CObjectPtr<IBACnetMutex>
BACNET_ENTRYPOINT
CreateBACnetMutex(
	bool CreateOwned);

CObjectPtr<IBACnetSpinLock>
BACNET_ENTRYPOINT
CreateBACnetSpinLock(
	U32 SpinCount = 0);

CObjectPtr<IBACnetTimer>
BACNET_ENTRYPOINT
CreateBACnetTimer(
	bool ManualReset);

CObjectPtr<IBACnetThreadpoolTimer>
BACNET_ENTRYPOINT
CreateBACnetThreadpoolTimer(
	TimerCallbackFunction pTimerCallback
);
