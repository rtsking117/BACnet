#pragma once

#include <vector>
#include <functional>
#include "BACnetCommon.h"
#include "BACnetTypes.h"

#ifndef BACNET_INTERFACE
#define BACNET_INTERFACE(x) struct BACNET_UUID(x) BACNET_NOVTABLE
#endif

#ifndef BACNET_INTERFACE_METHODS
#define BACNET_INTERFACE_METHODS

#define BACNETMETHODCALLTYPE BACNET_STDCALL
#define BACNETMETHODVCALLTYPE BACNET_CDECL

#define BCNMETHOD(method) virtual BACNET_NOTHROW BACnetResult BACNETMETHODCALLTYPE method
#define BCNMETHODTYPE(type,method) virtual BACNET_NOTHROW type BACNETMETHODCALLTYPE method
#define BCNMETHODV(method) virtual BACNET_NOTHROW BACnetResult BACNETMETHODVCALLTYPE method
#define BCNMETHODVTYPE(type,method) virtual BACNET_NOTHROW type BACNETMETHODVCALLTYPE method
#define BCPURE = 0
#endif

#ifndef __IBACnetUnknown__FWD_DEFINED__
#define __IBACnetUnknown__FWD_DEFINED__
typedef struct IBACnetUnknown IBACnetUnknown;
#endif

#include "ObjectPtr.h"

BACNET_INTERFACE("{D3D7F2CD-5930-495E-93AB-596A4A2395EE}")
IBACnetUnknown
{
	BCNMETHODTYPE(U32, AddRef()) BCPURE;
	BCNMETHODTYPE(U32, Release()) BCPURE;
};

#include "BACnetResult.h"
#include "BACnetCore.h"
#include "BACnetBuffer.h"
#include "BACnetThreading.h"
