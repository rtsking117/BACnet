#include "WinSockManager.h"

static CObjectPtr<WinSockManager> wsminst = nullptr;

WinSockManager::WinSockManager()
{
	memset(&wsa, 0, sizeof(wsa));
	WORD ver = MAKEWORD(2, 2);
	int err = WSAStartup(ver, &wsa);
	if(err != 0)
	{
		throw BACnetException("Failed to start Windows Sockets.", BCNRESULT_FROM_SYSTEM(err));
	}
	if(wsa.wVersion < ver)
	{
		WSACleanup();
		throw BACnetException("Windows Sockets version 2.2 or greater is not available.", BCE_VERSION_MISMATCH);
	}
}


WinSockManager::~WinSockManager()
{
	WSACleanup();
}

bool WinSockManager::GetVersion(U8 & MajorVersion, U8 & MinorVersion)
{
	return false;
}

BOOL CALLBACK InitWinSockSingleton(
	PINIT_ONCE initOnce,
	PVOID Parameter,
	PVOID *Context)
{
	BACnetResult* r = (BACnetResult*)Context;
	try
	{
		wsminst = new WinSockManager();
		*r = BC_OK;
	}
	catch(BACnetException e)
	{
		*r = e.errorcode;
	}
	return BCE_SUCCEEDED(*r);
}


BACnetResult CreateWSADevice(CObjectPtr<WinSockManager> &wsm)
{
	static INIT_ONCE initOnce = INIT_ONCE_STATIC_INIT;
	BACnetResult Result;
	if(InitOnceExecuteOnce(&initOnce,
		InitWinSockSingleton,
		nullptr, (void**)&Result))
	{
		wsm = wsminst;
		return BC_OK;
	}
	wsm = nullptr;
	return BC_OK;
}