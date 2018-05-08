#include "Thread.h"


DWORD CThread::ThreadEntry()
{
	//check on cancel.
	if(cancel->IsSet())
	{
		//don't even bother running.
		return 0;
	}
	return tf(this);
}

CThread::CThread(ThreadFunction tf):
	tf(tf),
	cancel(CreateBACnetEvent(true,false)),
	thread(INVALID_HANDLE_VALUE),
	exitcode(BCE_THREAD_NOT_STARTED)
{
}

CThread::~CThread()
{
	Stop();
	if(thread != INVALID_HANDLE_VALUE)
	{
		CloseHandle(thread);
		thread = INVALID_HANDLE_VALUE;
	}
}

BACnetResult CThread::Start()
{
	//is the thread currently live?
	if(thread != INVALID_HANDLE_VALUE)
	{
		if(GetExitCode() == BCE_THREAD_RUNNING)
		{
			//thread is still running!
			return BCE_THREAD_RUNNING;
		}
		//ok, it is stopped. Close it.
		CloseHandle(thread);
		thread = INVALID_HANDLE_VALUE;
	}
	cancel->Reset();
	thread = (HANDLE)_beginthreadex(nullptr, 0, [](void* param) -> U32
	{
		CThread* me = (CThread*)param;
		return me->ThreadEntry();
	}, this, CREATE_SUSPENDED, nullptr);
	if(thread == INVALID_HANDLE_VALUE)
	{
		return BCNRESULT_FROM_SYSTEM(GetLastError());
	}
	//thread is live. start it up.
	ResumeThread(thread);
	return BC_OK;
}

BACnetResult CThread::Cancel()
{
	cancel->Set();
	return BC_OK;
}

CObjectPtr<IBACnetEvent>CThread::GetCancellationEvent()
{
	return cancel;
}

BACnetResult CThread::Terminate(BACnetResult TerminationCode)
{
	TerminateThread(thread, TerminationCode);
	Release(); // <<<<<<<< WE NEED THIS TO BALANCE THE COMPTR WE GAVE TO THE THREAD FUNCTION
	//remember - TerminateThread allows no destructors to run - it just kills the thread.
	// that means we leak a reference every time we do this, if we don't balance here.
	return BC_OK;
}

BACnetResult CThread::Stop(U32 Timeout)
{
	Cancel();
	BACnetResult r = WaitForObject(this, Timeout);
	if(r == BCE_WAIT_TIMEOUT)
	{
		return Terminate(BCE_THREAD_TERMINATED);
	}
	cancel->Reset();
	return r;
}

BACnetResult CThread::GetExitCode()
{
	DWORD code = 0;
	GetExitCodeThread(thread, &code);
	if(code == STILL_ACTIVE)
	{
		return BCE_THREAD_RUNNING;
	}
	return (BACnetResult)code;
}

CObjectPtr<IBACnetThread> CreateBACnetThread(ThreadFunction pThreadFunction)
{
	return CObjectPtr<IBACnetThread>(new CThread(pThreadFunction), true);
}