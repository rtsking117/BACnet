#include "BACnetTypes.h"
#include <WinSock2.h>
#include <type_traits>

U16 ToNet16(U16 uiHost)
{
	return htons(uiHost);
}

U32 ToNet32(U32 uiHost)
{
	return htonl(uiHost);
}

U64 ToNet64(U64 uiHost)
{
	return htonll(uiHost);
}

U16 ToHost16(U16 uiNet)
{
	return ntohs(uiNet);
}

U32 ToHost32(U32 uiNet)
{
	return ntohl(uiNet);
}

U64 ToHost64(U64 uiNet)
{
	return ntohll(uiNet);
}

U32 BACNET_ENTRYPOINT CountLeadingZeros(U32 Value)
{
	ULONG ret = 0;
	//This cast is OK under Win32 since 
	// long and int are the same.
	if(BitScanReverse(&ret, (ULONG)Value))
	{
		return 31 - (ret);
	}
	return 32;
}

U32 BACNET_ENTRYPOINT CountTrailingZeros(U32 Value)
{
	ULONG ret = 0;
	//This cast is OK under Win32 since 
	// long and int are the same.
	if(BitScanForward(&ret, (ULONG)Value))
	{
		return (ret);
	}
	return 32;
}

U32 FindFirstSet(U32 Value)
{
	ULONG ret = 0;
	//This cast is OK under Win32 since 
	// long and int are the same.
	if(BitScanForward(&ret, (ULONG)Value))
	{
		return (ret);
	}
	return -1;
}

U32 Log2(U32 Value)
{
	ULONG ret = 0;
	//This cast is OK under Win32 since 
	// long and int are the same.
	if(BitScanReverse(&ret, (ULONG)Value))
	{
		return (ret);
	}
	return -1;
}

#ifdef _X64_

U32 BACNET_ENTRYPOINT CountLeadingZeros64(U64 Value)
{
	ULONG ret = 0;
	if(_BitScanReverse64(&ret, Value))
	{
		return 63 - (ret);
	}
	return 64;
}

U32 BACNET_ENTRYPOINT CountTrailingZeros64(U64 Value)
{
	ULONG ret = 0;
	if(_BitScanForward64(&ret, Value))
	{
		return (ret);
	}
	return 64;
}

U32 BACNET_ENTRYPOINT FindFirstSet64(U64 Value)
{
	ULONG ret = 0;
	if(_BitScanForward64(&ret, Value))
	{
		return (ret);
	}
	return -1;
}

U32 BACNET_ENTRYPOINT Log2_64(U64 Value)
{
	ULONG ret = 0;
	if(_BitScanReverse64(&ret, Value))
	{
		return (ret);
	}
	return -1;
}

#else

//x86 does not support the BSR/BSF intrinsics for 64 bit math.
//We synthesize them with two BSR/BSF 32 bit instructions.
U32 BACNET_ENTRYPOINT CountLeadingZeros64(U64 Value)
{
	U32 High = (Value >> 32) & 0xFFFFFFFF;
	U32 Low = (Value & 0xFFFFFFFF);
	DWORD ret;
	if(High)
	{
		//BSR, add 32, and return.
		BitScanReverse(&ret, (ULONG)High);
		//63 - (x + 32) = 63 + (-x - 32) =  63 - 32 + -x = 31 - x
		return (31 - ret);
	}
	if(Low)
	{
		BitScanReverse(&ret, (ULONG)Low);
		return 63 - (ret);
	}
	return 64;
}

U32 BACNET_ENTRYPOINT CountTrailingZeros64(U64 Value)
{
	U32 High = (Value >> 32) & 0xFFFFFFFF;
	U32 Low = (Value & 0xFFFFFFFF);
	DWORD ret;
	if(High)
	{
		//BSF, add 32, and return.
		BitScanForward(&ret, (ULONG)High);
		return (ret) + 32;
	}
	if(Low)
	{
		BitScanForward(&ret, (ULONG)Low);
		return (ret);
	}
	return 64;
}


U32 BACNET_ENTRYPOINT FindFirstSet64(U64 Value)
{
	U32 High = (Value >> 32) & 0xFFFFFFFF;
	U32 Low = (Value & 0xFFFFFFFF);
	DWORD ret;
	if(High)
	{
		BitScanForward(&ret, (ULONG)High);
		return (ret) + 32;
	}
	if(Low)
	{
		BitScanForward(&ret, (ULONG)Low);
		return ret;
	}
	return -1;
}

U32 BACNET_ENTRYPOINT Log2_64(U64 Value)
{
	U32 High = (Value >> 32) & 0xFFFFFFFF;
	U32 Low = (Value & 0xFFFFFFFF);
	DWORD ret;
	if(High)
	{
		BitScanReverse(&ret, (ULONG)High);
		return (ret)+32;
	}
	if(Low)
	{
		BitScanReverse(&ret, (ULONG)Low);
		return ret;
	}
	return -1;
}

#endif

template<int> size_t FinalizeHash(U64 Hash);

//under x64, use the hash output directly.
template<> size_t BACNET_FORCEINLINE FinalizeHash<sizeof(U64)>(U64 Intermediate)
{
	return (size_t)(Intermediate);
}

//under x86, XOR mix the hash to a 32 bit value.
template<> size_t BACNET_FORCEINLINE FinalizeHash<sizeof(U32)>(U64 Intermediate)
{
	return (size_t)((Intermediate >> 32) ^ (Intermediate));
}

template<typename T>
T GenerateHashCode(U8 * pDataBuffer, size_t BufferLength)
{
	static const U64 FNV1aOffsetBasis = 0xcbf29ce484222325;
	static const U64 FNV1aPrime = 0x100000001b3;
	U64 ret = FNV1aOffsetBasis;
	for(size_t i = 0; i < BufferLength; ++i)
	{
		ret ^= ((U8*)pDataBuffer)[i];
		ret *= FNV1aPrime;
	}
	return (T)FinalizeHash<sizeof(T)>(ret);
}

U32 BACNET_ENTRYPOINT GenerateHash32(U8* pDataBuffer, size_t BufferLength)
{
	return GenerateHashCode<U32>(pDataBuffer, BufferLength);
}

U64 BACNET_ENTRYPOINT GenerateHash64(U8* pDataBuffer, size_t BufferLength)
{
	return GenerateHashCode<U64>(pDataBuffer, BufferLength);
}

size_t BACNET_ENTRYPOINT GenerateHash(U8* pDataBuffer, size_t BufferLength)
{
	return GenerateHashCode<size_t>(pDataBuffer, BufferLength);
}
