#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Unconfirmed Private Transfer
class UnconfirmedPrivateTransferRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type>,
		BACnetSequenceElement<1, BACnetUnsignedType>,
		BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:

	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	BACnetValue GetServiceParameters()
	{
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetServiceParameters(const BACnetValue& ServiceParams)
	{
		get<2>().set(ServiceParams);
	}

};
