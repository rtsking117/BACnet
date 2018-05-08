#pragma once

#include <BACnetInterface.h>
#include <vector>
using namespace std;

#ifdef BACNETAPPLICATION_EXPORTS
#define BACNETAPP_ENTRYPOINT BACNET_EXPORT
#else
#define BACNETAPP_ENTRYPOINT BACNET_IMPORT
#endif

#ifndef __IBACnetApplication__FWD_DEFINED__
#define __IBACnetApplication__FWD_DEFINED__
typedef struct IBACnetApplication IBACnetApplication;
#endif

#ifndef __IBACnetRequestParser__FWD_DEFINED__
#define __IBACnetRequestParser__FWD_DEFINED__
typedef struct IBACnetRequestParser IBACnetRequestParser;
#endif

typedef U32 BACnetObjectID;

BACNET_FORCEINLINE BACnetObjectID CreateBACnetObjectID(U32 ObjectType, U32 InstanceNumber)
{
	return ((ObjectType & 0x3FF) << 22) | (InstanceNumber & 0x3FFFFF);
}

BACNET_FORCEINLINE U32 GetInstanceIDFromObjectID(BACnetObjectID Id)
{
	return (Id & 0x3FFFFF);
}

BACNET_FORCEINLINE U16 GetObjectTypeFromObjectID(BACnetObjectID Id)
{
	return ((Id & 0xFFC) >> 22);
}

#include "BACnetValue.h"
#include "BACnetError.h"
#include "BACnetEnum.h"
#include "ASN1.h"
#include "BACnetAPDU.h"


//BACNET_INTERFACE("{BAD64972-A8F0-463D-B03C-B8E9DCFB3B64}")
//IBACnetApplication: public IBACnetStackComponent
//{
//	BCNMETHOD(AttachTransactionManager(CObjectPtr<IBACnetTransactionManager> pAssembler)) BCPURE;
//	BCNMETHODTYPE(CObjectPtr<IBACnetTransactionManager>, GetTransactionManager()) BCPURE;
//	BCNMETHOD(DetachTransactionManager(void)) BCPURE;
//};
//
//BACNET_INTERFACE("{9A00ABDF-B0F7-49E3-95A7-E9CB400363C1}")
//IBACnetRequestParser : public IBACnetApplication
//{
//	BCNMETHOD(RegisterPreliminaryDisplayCallback(DisplayCallback pCallback)) BCPURE;
//};

