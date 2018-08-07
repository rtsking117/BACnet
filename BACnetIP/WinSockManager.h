#pragma once

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

#include <BACnetInterface.h>
#include <ObjectWrapper.h>

class WinSockManager :
	public ObjectWrapper < IBACnetUnknown >
{
	WSADATA wsa;
public:
	WinSockManager();
	~WinSockManager();

	bool GetVersion(U8& MajorVersion, U8& MinorVersion);
};

BACnetResult CreateWSADevice(CObjectPtr<WinSockManager> &wsm);