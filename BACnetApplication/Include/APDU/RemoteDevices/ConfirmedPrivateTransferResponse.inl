#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Confirmed Private Transfer Ack
class ConfirmedPrivateTransferResponse : public
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

	bool HasResultParameters()
	{
		return is_present<2>();
	}

	BACnetValue GetResultParameters()
	{
		if(HasResultParameters())
		{
			return BACnetValue();
		}
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

	void SetResultParameters(BACnetValue EncodedServiceParameters)
	{
		make_present<2>(true);
		get<2>().set(EncodedServiceParameters);
	}
};
