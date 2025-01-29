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

#include "BACnetPropertyTypes.inl"

//Change List Error
class ChangeListError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetUnsignedType>
	>
{
public:

};

//Create Object Error
class CreateObjectError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetUnsignedType>
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

//Confirmed Private Transfer Error
class ConfirmedPrivateTransferError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetUnsigned16Type>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetAnyType, true>
	>
{
public:

};

//Subscribe COV Property Multiple Error
class SubscribeCOVPropertyMultipleError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetObjectIDType>,
				BACnetSequenceElement<1, BACnetPropertyReference>,
				BACnetSequenceElement<2, BACnetError>
			>, false
		>
	>
{
public:

};

//Write Property Multiple Error
class WritePropertyMultipleError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetObjectPropertyReference>
	>
{
public:

};

//VT Close Error
class VTCloseError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetSequenceOf<BACnetUnsigned8Type>, true>
	>
{
public:

};