#pragma once
#include <list>
#include <Windows.h>
#include "ComWrapper.h"

class CThreadPool :
	public ComWrapper<IBACnetThreadPool>
{
	struct CallbackDispatchStruct
	{
		CObjectPtr<CThreadPool> pThreadPool;
		AsyncCallbackFunction pCallbackFunction;
	};

	std::list<CallbackDispatchStruct*> freelist;
	TP_CALLBACK_ENVIRON env;
	PTP_POOL tpool;
	SRWLOCK srw;

	void LockList();
	void UnlockList();

	CallbackDispatchStruct* GetDispatchStruct();
	void ReleaseDispatchStruct(CallbackDispatchStruct* cbds);

public:
	CThreadPool();
	~CThreadPool();

	BACnetResult BACNETMETHODCALLTYPE QueueAsyncCallback(AsyncCallbackFunction pCallbackFunction);
	bool BACNETMETHODCALLTYPE CallbackRunsLong(CallbackHandle pHandle);
	CObjectPtr<IBACnetThreadpoolTimer> BACNETMETHODCALLTYPE CreateThreadpoolTimer(TimerCallbackFunction pCallback);
};

