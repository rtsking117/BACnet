#include "BACnetTypes.h"
#include <WinSock2.h>

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

U32 FindFirstSet(U32 Value)
{
	ULONG ret = 0;
	//This cast is OK under Win32 since 
	// long and int are the same.
	if(BitScanForward(&ret, (ULONG)Value))
	{
		return (ret+1);
	}
	return 0;
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
