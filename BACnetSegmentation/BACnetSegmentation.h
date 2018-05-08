#pragma once

#include <BACnetInterface.h>

#ifdef BACNETSEGMENT_EXPORTS
#define BACNETSEGMENT_ENTRYPOINT BACNET_EXPORT
#else
#define BACNETSEGMENT_ENTRYPOINT BACNET_IMPORT
#endif

CObjectPtr<IBACnetTransactionManager>
BACNETSEGMENT_ENTRYPOINT
CreateTransactionManager(U16 MaxSegments);
