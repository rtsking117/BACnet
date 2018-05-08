#pragma once

#include <BACnetInterface.h>

#ifdef BACNETNETWORK_EXPORTS
#define BACNETNETWORK_ENTRYPOINT BACNET_EXPORT
#else
#define BACNETNETWORK_ENTRYPOINT BACNET_IMPORT
#endif

BACNET_INTERFACE("{0E492A84-1F5D-46A7-A467-C182CF6AD467}")
IBACnetSimpleNetwork : public IBACnetNetwork
{

};

typedef std::function<BACnetResult(U16 NetworkNumber, CObjectPtr<IBACnetPort> Port)> PortEnumerationCallback;

BACNET_INTERFACE("{08EC1E34-C0ED-43ED-BBAB-A31CE011AB11}")
IBACnetRoutingNetwork : public IBACnetNetwork
{
	BCNMETHODTYPE(U16, GetNetworkAtIndex(U32 Index) const);
	BCNMETHOD(EnumeratePorts(PortEnumerationCallback PortEnumerator));
};


CObjectPtr<IBACnetSimpleNetwork> 
BACNETNETWORK_ENTRYPOINT
CreateSimpleNetwork(
	CObjectPtr<IBACnetThreadPool> pThreadPool);

CObjectPtr<IBACnetRoutingNetwork>
BACNETNETWORK_ENTRYPOINT
CreateRoutingNetwork(
	CObjectPtr<IBACnetThreadPool> pThreadPool);