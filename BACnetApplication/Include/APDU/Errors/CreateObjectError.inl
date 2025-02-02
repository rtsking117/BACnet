#include "BACnetError.inl"

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