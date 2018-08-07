#pragma once
#include "ObjectWrapper.h"
#include <Windows.h>

class CBACnetSpinLock :
	public ObjectWrapper<IBACnetSpinLock>
{
	CRITICAL_SECTION cs;
public:
	CBACnetSpinLock(U32 SpinCount);
	~CBACnetSpinLock();

	void BACNETMETHODCALLTYPE Lock();
	bool BACNETMETHODCALLTYPE TryLock();
	void BACNETMETHODCALLTYPE Unlock();
	void BACNETMETHODCALLTYPE UnlockOnReturn(CallbackHandle pHandle);
};

