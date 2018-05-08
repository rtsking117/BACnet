#include "BACnetIP.h"

#include "LocalSocket.h"

CObjectPtr<IBACnetLocalSubnet> CreateLocalSubnet(CObjectPtr<IBACnetThreadPool> pThreadPool, U16 PortNumber)
{
	try
	{
		return CObjectPtr<IBACnetLocalSubnet>(new LocalSocket(pThreadPool, PortNumber), true);
	}
	catch(BACnetException ex)
	{
		return nullptr;
	}
}
