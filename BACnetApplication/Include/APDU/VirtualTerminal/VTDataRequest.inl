#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//VT Data
class VTDataRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type>,
		BACnetSequenceElement<NoTag, BACnetOctetStringType>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType>
	>
{
public:
	U8 GetSessionID()
	{
		return get<0>().get();
	}

	BACnetByteString GetVTData()
	{
		return get<1>().get();
	}

	U32 GetDataFlag()
	{
		return get<2>().get();
	}

	void SetSessionID(U8 SessionID)
	{
		get<0>().set(SessionID);
	}

	void SetVTData(BACnetByteString VTData)
	{
		get<1>().set(VTData);
	}

	void SetDataFlag(bool DataFlag)
	{
		get<2>().set(DataFlag ? 1 : 0);
	}
};
