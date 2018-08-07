#pragma once

#include <atomic>
#include <type_traits>
#include <exception>
#include "BACnetInterface.h"

/*
ObjectWrapper.h - Contains the ObjectWrapper template class,
 which implements the AddRef and Release methods of
 IBACnetUnknown.

*/

struct BACnetException : public std::exception
{
	BACnetResult errorcode;
	BACnetException(char* message, BACnetResult code) : std::exception(message), errorcode(code) {}

};

template<typename T> class ObjectWrapper: public T
{
	//AddRef and Release are IBACnetUnknown methods. If we don't inherit from IBACnetUnknown, we may not 
	//implement the methods correctly, or add methods that don't exist. So we check here, and statically.
	// This check has no runtime cost.
	static_assert(std::is_base_of<IBACnetUnknown, T>::value, "Class T must be derived from IBACnetUnknown.");
	//atomic counter for multithreaded access/updates
	std::atomic<U32> refcount;
public:
	ObjectWrapper() :refcount(1)
	{
	}
	virtual ~ObjectWrapper()
	{}

	U32 BACNETMETHODCALLTYPE AddRef() { return ++refcount; }
	//We need an equivalence with zero. Otherwise, if a free pushed the counter into the negatives, we'd end up with a double free.
	//That should never happen. But with multithreading, you never know.
	U32 BACNETMETHODCALLTYPE Release() { U32 r = --refcount; if(r == 0) { delete this; } return r; }
	//Other inherited methods can be implemented by the derived class.
};

