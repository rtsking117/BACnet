#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//I Am
class IAmRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType>,
		BACnetSequenceElement<NoTag, BACnetSegmentationType>,
		BACnetSequenceElement<NoTag, BACnetUnsigned16Type>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetMaxAPDUSize()
	{
		return get<1>().get();
	}

	BACnetSegmentation GetSegmentationSettings()
	{
		return (BACnetSegmentation)get<2>().get();
	}

	U16 GetVendorID()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ID)
	{
		get<0>().set(ID);
	}

	void SetMaxAPDUSize(U32 APDUSize)
	{
		get<1>().set(APDUSize);
	}

	void SetSegmentationSettings(BACnetSegmentation segmentation)
	{
		get<2>().set((U32)segmentation);
	}

	void SetVendorID(U16 VendorID)
	{
		get<3>().set(VendorID);
	}
};
