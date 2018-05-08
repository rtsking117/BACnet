#include "BACnetEvent.h"

CBACnetEvent::CBACnetEvent(bool ManualReset, bool InitialState) : 
	evt(CreateEvent(nullptr,ManualReset,InitialState,nullptr))
{
	if(evt == INVALID_HANDLE_VALUE)
	{
		throw BACnetException("Failed to create event handle", BCNRESULT_FROM_SYSTEM(GetLastError()));
	}
}

CBACnetEvent::~CBACnetEvent()
{
	CloseHandle(evt);
}

CObjectPtr<IBACnetEvent> BACNET_ENTRYPOINT CreateBACnetEvent(bool ManualReset, bool InitialState)
{
	try
	{
		return CObjectPtr<IBACnetEvent>(new CBACnetEvent(ManualReset, InitialState), true);
	}
	catch(BACnetException e)
	{
		return nullptr;
	}
}