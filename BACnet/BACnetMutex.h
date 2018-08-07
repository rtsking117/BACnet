#pragma once
#include "ObjectWrapper.h"
#include <Windows.h>

class CBACnetMutex :
	public ObjectWrapper<IBACnetMutex>
{
	HANDLE mutex;

public:
	CBACnetMutex(bool CreateOwned);
	~CBACnetMutex();

	BCNMETHODTYPE(void*, GetWaitHandle() const) { return (void*)mutex; }

	BCNMETHODTYPE(bool, Lock(U32 msTimeout = (-1)))
	{
		DWORD ret = WaitForSingleObject(mutex, msTimeout);;
		switch(ret)
		{
		case WAIT_OBJECT_0:
			return true;
		case WAIT_ABANDONED_0:
			//We did lock it, but it wasn't closed correctly.
			return true;
		case WAIT_TIMEOUT:
			return false;
		default:
			__debugbreak();
			return false;
		}
	}
	BCNMETHODTYPE(void, Unlock()) { ReleaseMutex(mutex); }

	BCNMETHODTYPE(void, UnlockOnReturn(CallbackHandle pHandle))
	{
		ReleaseMutexWhenCallbackReturns((PTP_CALLBACK_INSTANCE)pHandle, mutex);
	}

};
