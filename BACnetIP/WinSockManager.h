#pragma once

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

#include <BACnetInterface.h>
#include <ComWrapper.h>

class WinSockManager :
	public ComWrapper < IBACnetUnknown >
{
	WSADATA wsa;
public:
	WinSockManager();
	~WinSockManager();
};

BACnetResult CreateWSADevice(CObjectPtr<WinSockManager> &wsm);