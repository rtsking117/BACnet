#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Generic Error
class BACnetError : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetEnumeratedType>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType>
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
