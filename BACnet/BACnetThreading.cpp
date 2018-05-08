#include "BACnetThreading.h"
#include "ThreadPool.h"
#include <Windows.h>


BACnetResult BACNET_ENTRYPOINT WaitForObject(CObjectPtr<IBACnetWaitableObject> pObject, U32 msTimeout)
{
	DWORD result = WaitForSingleObject(pObject->GetWaitHandle(), msTimeout); //<--- Cannot get WAIT_IO_COMPLETION - This is not alertable
	switch(result)
	{
	case WAIT_OBJECT_0:
		return BC_OK;
	case WAIT_TIMEOUT:
		return BCE_WAIT_TIMEOUT;
	default:
		return BCNRESULT_FROM_SYSTEM(GetLastError());
	}
}

BACnetResult BACNET_ENTRYPOINT WaitForObjects(CObjectPtr<IBACnetWaitableObject>* pObjectList, U32 nObjects, U32& SignaledObject, bool WaitForAll, U32 msTimeout)
{
	SignaledObject = 0;
	HANDLE* handles = (HANDLE*)malloc(nObjects * sizeof(HANDLE));
	for(U32 i = 0; i < nObjects; ++i)
	{
		handles[i] = pObjectList[i]->GetWaitHandle();
	}
	DWORD result = WaitForMultipleObjects(nObjects, handles, WaitForAll, msTimeout); //<--- Cannot get WAIT_IO_COMPLETION - This is not alertable
	switch(result)
	{
	case WAIT_FAILED:
		return BCNRESULT_FROM_SYSTEM(GetLastError());
	case WAIT_TIMEOUT:
		return BCE_WAIT_TIMEOUT;
	default:
		if(result >= WAIT_ABANDONED_0)
		{
			SignaledObject = (result - WAIT_ABANDONED_0);
			return BCS_MUTEX_ABANDONED;
		}
		else
		{
			SignaledObject = (result - WAIT_OBJECT_0);
			return BC_OK;
		}
	}
}

