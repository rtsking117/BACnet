#ifndef _COMPTR_H_
#define _COMPTR_H_

#include <type_traits>
#include "BACnetInterface.h"

template<typename T> class CObjectPtr
{
private:
	T* pInterface;
public:
	CObjectPtr(T* pSource = nullptr, bool IsSoleOwner=false) :pInterface(pSource)
	{
		static_assert(std::tr1::is_base_of<IBACnetUnknown, T>::value, "T needs to be IBACnetUnknown based");
		if(!IsSoleOwner)
		{
			AddRef();
		}
	}
	CObjectPtr(const CObjectPtr<T>& rCObjectPtr) : pInterface(rCObjectPtr.pInterface)
	{
		static_assert(std::tr1::is_base_of<IBACnetUnknown, T>::value, "T needs to be IBACnetUnknown based");
		AddRef();
	}
	CObjectPtr(CObjectPtr<T>&& rCObjectPtr) : pInterface(rCObjectPtr.pInterface)
    {
        rCObjectPtr.pInterface = nullptr;
    }
	~CObjectPtr()
	{
		Release();
	}

	void AddRef()
	{
		if(pInterface)
		{
			pInterface->AddRef();
		}
	}
	void Release()
	{
		if(pInterface)
		{
			pInterface->Release();
			pInterface=nullptr;
		}
	}

	T* operator=(T* lCObjectPtr)
    {
        Release();

        pInterface = lCObjectPtr;

		AddRef();

        return pInterface;
    }

    T* operator=(const CObjectPtr<T>& lCObjectPtrObj)
    {
        Release();

        pInterface = lCObjectPtrObj.pInterface;

        AddRef();

        return pInterface;
    }

	template <typename Q>
	operator CObjectPtr<Q>() const
	{
		static_assert(std::is_base_of<Q,T>::value, "T does not inherit from Q");
		return CObjectPtr<Q>(static_cast<Q*>(pInterface));
	}

	operator T*() const
    {
        return pInterface;
    }

    T* GetInterface() const
    {
        return pInterface;
    }

    T& operator*() const
    {
        return *pInterface;
    }

    T** operator&()
    {
        //The assert on operator& usually indicates a bug. Could be a potential memory leak.
        // If this really what is needed, however, use GetInterface() explicitly.
        assert(nullptr == pInterface);
        return &pInterface;
    }

    T* operator->() const
    {
        return pInterface;
    }

    bool operator!() const
    {    
        return (nullptr == pInterface);
    }

    bool operator<(T* lCObjectPtr) const
    {
        return pInterface < lCObjectPtr;
    }

    bool operator!=(T* lCObjectPtr) const
    {
        return !operator==(lCObjectPtr);
    }

    bool operator==(T* lCObjectPtr) const
    {
        return pInterface == lCObjectPtr;
    }

};

#endif