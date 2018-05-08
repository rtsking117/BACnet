#include "ThreadPool.h"
#include "ThreadpoolTimer.h"

void CThreadPool::LockList()
{
	AcquireSRWLockExclusive(&srw);
}

void CThreadPool::UnlockList()
{
	ReleaseSRWLockExclusive(&srw);
}

CThreadPool::CallbackDispatchStruct * CThreadPool::GetDispatchStruct()
{
	//pop the first one off the free list.
	LockList();
	CallbackDispatchStruct* ret;
	if(freelist.empty())
	{
		//no choice. Allocate a new one.
		//We can unlock the list beforehand as we will not need to modify it anymore.
		UnlockList();
		ret = new CallbackDispatchStruct();
	}
	else
	{
		ret = freelist.front();
		freelist.pop_front();
		UnlockList();
	}
	return ret;
}

void CThreadPool::ReleaseDispatchStruct(CThreadPool::CallbackDispatchStruct* cbds)
{
	//push this one onto the free list.
	LockList();
	freelist.push_back(cbds);
	UnlockList();
}

CThreadPool::CThreadPool() :
	tpool(CreateThreadpool(nullptr))
{
	SetThreadpoolThreadMinimum(tpool, 2);
	SetThreadpoolThreadMaximum(tpool, 8);
	InitializeThreadpoolEnvironment(&env);
	SetThreadpoolCallbackPool(&env, tpool);
	for(int i=0;i<16;++i)
	{
		freelist.push_back(new CallbackDispatchStruct());
	}
}

CThreadPool::~CThreadPool()
{
	freelist.clear();
	DestroyThreadpoolEnvironment(&env);
	CloseThreadpool(tpool);
}

BACnetResult CThreadPool::QueueAsyncCallback(AsyncCallbackFunction pCallbackFunction)
{
	CallbackDispatchStruct* cds = GetDispatchStruct();
	cds->pCallbackFunction = pCallbackFunction;
	cds->pThreadPool = CObjectPtr<CThreadPool>(this);
	if(!TrySubmitThreadpoolCallback([](PTP_CALLBACK_INSTANCE inst, void * param)
	{
		CallbackDispatchStruct cds = *(CallbackDispatchStruct*)param;
		cds.pThreadPool->ReleaseDispatchStruct((CallbackDispatchStruct*)param);
		BACnetResult r = cds.pCallbackFunction(CObjectPtr<IBACnetThreadPool>(cds.pThreadPool), (CallbackHandle)inst);
		//check result.
		if(BCE_FAILED(r))
		{
			//log it.
		}
	}, cds, &env))
	{
		return BCNRESULT_FROM_SYSTEM(GetLastError());
	}
	return BC_OK;
}

bool CThreadPool::CallbackRunsLong(CallbackHandle pHandle)
{
	return CallbackMayRunLong((PTP_CALLBACK_INSTANCE)pHandle) == TRUE;
}

CObjectPtr<IBACnetThreadpoolTimer> CThreadPool::CreateThreadpoolTimer(TimerCallbackFunction pCallback)
{
	return CObjectPtr<IBACnetThreadpoolTimer>(new CThreadpoolTimer(pCallback, CObjectPtr<IBACnetThreadPool>(this), &env), true);
}

CObjectPtr<IBACnetThreadPool> CreateThreadPool()
{
	try
	{
		return CObjectPtr<IBACnetThreadPool>(new CThreadPool(), true);
	}
	catch(BACnetException e)
	{
		return nullptr;
	}
}