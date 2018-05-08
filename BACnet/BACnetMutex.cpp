#include "BACnetMutex.h"



CBACnetMutex::CBACnetMutex(bool CreateOwned) : 
	mutex(CreateMutex(nullptr,CreateOwned,nullptr))
{
	if(mutex == INVALID_HANDLE_VALUE)
	{
		throw BACnetException("Failed to create mutex handle", BCNRESULT_FROM_SYSTEM(GetLastError()));
	}
}


CBACnetMutex::~CBACnetMutex()
{
	CloseHandle(mutex);
}

CObjectPtr<IBACnetMutex> BACNET_ENTRYPOINT CreateBACnetMutex(bool CreateOwned)
{
	try
	{
		return CObjectPtr<IBACnetMutex>(new CBACnetMutex(CreateOwned), true);
	}
	catch(BACnetException e)
	{
		return nullptr;
	}
}