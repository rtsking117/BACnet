#include "BACnetSpinLock.h"
#include <exception>

CBACnetSpinLock::CBACnetSpinLock(U32 SpinCount)
{
	if(!InitializeCriticalSectionAndSpinCount(&cs, SpinCount))
	{
		throw std::exception("Critical Section object could not be created!");
	}
}

CBACnetSpinLock::~CBACnetSpinLock()
{
	DeleteCriticalSection(&cs);
}

void CBACnetSpinLock::Lock()
{
	EnterCriticalSection(&cs);
}

bool CBACnetSpinLock::TryLock()
{
	return TryEnterCriticalSection(&cs) == TRUE;
}

void CBACnetSpinLock::Unlock()
{
	LeaveCriticalSection(&cs);
}

void CBACnetSpinLock::UnlockOnReturn(CallbackHandle pHandle)
{
	LeaveCriticalSectionWhenCallbackReturns((PTP_CALLBACK_INSTANCE)pHandle, &cs);
}


CObjectPtr<IBACnetSpinLock> CreateBACnetSpinLock(U32 SpinCount)
{
	return CObjectPtr<IBACnetSpinLock>(new CBACnetSpinLock(SpinCount),true);
}

