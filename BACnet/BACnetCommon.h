#pragma once

#ifndef BACNET_NOVTABLE
#ifdef _MSC_VER
#define BACNET_NOVTABLE __declspec(novtable)
#else
#define BACNET_NOVTABLE __attribute__((novtable))
#endif
#endif

#ifndef BACNET_UUID
#ifdef _MSC_VER
#define BACNET_UUID(x) __declspec(uuid(x))
#else
#define BACNET_UUID(x) 
#endif
#endif

#ifndef BACNET_NOTHROW
#ifdef _MSC_VER
#define BACNET_NOTHROW __declspec(nothrow)
#else
#define BACNET_NOTHROW __attribute__((nothrow))
#endif
#endif

#ifndef BACNET_SELECTANY
#ifdef _MSC_VER
#define BACNET_SELECTANY __declspec(selectany)
#else
#define BACNET_SELECTANY __attribute__((weak))
#endif
#endif

#ifndef BACNET_STDCALL
#ifdef _MSC_VER
#define BACNET_STDCALL __stdcall
#else
#define BACNET_STDCALL 
#endif
#endif

#ifndef BACNET_CDECL
#ifdef _MSC_VER
#define BACNET_CDECL __cdecl
#else
#define BACNET_CDECL
#endif
#endif

#ifndef BACNET_FORCEINLINE
#ifdef _MSC_VER
#define BACNET_FORCEINLINE inline __forceinline
#else
#define BACNET_FORCEINLINE inline __attribute((always_inline))
#endif
#endif

#ifndef BACNET_UNREACHABLECASE
#ifdef _MSC_VER
#define BACNET_UNREACHABLECASE default: __assume(0)
#else
#define BACNET_UNEACHABLECASE default: __builtin_unreachable()
#endif
#endif

#ifndef BACNET_EXPORT
#ifdef _MSC_VER
#define BACNET_EXPORT __declspec(dllexport)
#define BACNET_IMPORT __declspec(dllimport)
#else
#define BACNET_EXPORT 
#define BACNET_IMPORT
#endif
#endif

#ifdef BACNET_EXPORTS
#define BACNET_ENTRYPOINT BACNET_EXPORT
#else
#define BACNET_ENTRYPOINT BACNET_IMPORT
#endif
