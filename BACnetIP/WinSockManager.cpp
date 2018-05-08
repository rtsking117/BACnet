#include "WinSockManager.h"

CObjectPtr<WinSockManager> wsminst = nullptr;

WinSockManager::WinSockManager()
{
	memset(&wsa, 0, sizeof(wsa));
	WORD ver = MAKEWORD(2, 2);
	int err=WSAStartup(ver, &wsa);
	if(err != 0)
	{
		throw BACnetException("Failed to start Windows Sockets.", BCNRESULT_FROM_SYSTEM(err));
	}
	if(wsa.wVersion != ver)
	{
		WSACleanup();
		throw BACnetException("Windows Sockets version 2.2 is not available.", BCE_VERSION_MISMATCH);
	}
}


WinSockManager::~WinSockManager()
{
	WSACleanup();
}

BACnetResult CreateWSADevice(CObjectPtr<WinSockManager> &wsm)
{
	if(!wsminst)
	{
		try
		{
			wsminst = new WinSockManager();
			wsm = wsminst;
			return BC_OK;
		}
		catch(BACnetException ex)
		{
			wsminst = nullptr;
			return ex.errorcode;
		}
	}
	else
	{
		wsm = wsminst;
		return BC_OK;
	}
}