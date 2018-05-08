#pragma once
#include "ComWrapper.h"
#include <Windows.h>

class CBACnetEvent :
	public ComWrapper<IBACnetEvent>
{
	HANDLE evt;
public:
	CBACnetEvent(bool ManualReset, bool InitialState);
	~CBACnetEvent();

	BCNMETHODTYPE(void*, GetWaitHandle() const) { return (void*)evt; }

	BCNMETHODTYPE(void, Set()) { SetEvent(evt); }
	BCNMETHODTYPE(void, Reset()) { ResetEvent(evt); }
	BCNMETHODTYPE(bool, IsSet()) 
	{ 
		DWORD ret = WaitForSingleObject(evt, 0);
		switch(ret)
		{
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
			return false;
		default:
			//shouldn't reach here, but be "safe" about it.
			__debugbreak();
			return false;
		}
	}
	BCNMETHODTYPE(void, SetOnReturn(CallbackHandle pHandle))
	{
		SetEventWhenCallbackReturns((PTP_CALLBACK_INSTANCE)pHandle, evt);
	}
};

