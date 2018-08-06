#pragma once

#include "BACnetBasicTypes.inl"

//=============================================================================================
//							ERROR PRODUCTIONS
//=============================================================================================

//Generic Error
class BACnetError : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
	BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>
	>
{
public:
	U16 GetErrorClass()
	{
		return (U16)get<0>().get();
	}

	U16 GetErrorCode()
	{
		return (U16)get<1>().get();
	}

	bool SetError(ErrorClass Class, ErrorCode Code)
	{
		return SetError((U16)Class, (U16)Code);
	}

	bool SetError(U16 Class, U16 Code)
	{
		return get<0>().set(Class) && get<1>().set(Code);
	}
};

//Change List Error


//Create Object Error
class CreateObjectError : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetError, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>
	>
{
public:
	CreateObjectError()
	{
		//make the First Failed Element Number 0 on init.
		//compilance with 15.3.1.3.2
		get<1>().set(0);
	}

	U16 GetErrorClass()
	{
		return get<0>().GetErrorClass();
	}

	U16 GetErrorCode()
	{
		return get<0>().GetErrorCode();
	}

	U32 GetLastFailedProperty()
	{
		return get<1>().get();
	}

	template<typename T, typename Q>
	bool SetError(T ErrorClass, Q ErrorCode)
	{
		return get<0>().SetError(ErrorClass, ErrorCode);
	}

	bool SetLastFailedProperty(U32 PropIndex)
	{
		return get<1>().set(PropIndex);
	}


};

