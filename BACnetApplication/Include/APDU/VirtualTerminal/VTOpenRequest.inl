#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//VT Open
class VTOpenRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetVTClassType>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type>
	>
{
public:

	U32 GetVTClass()
	{
		return get<0>().get();
	}

	U8 GetLocalSessionID()
	{
		return get<1>().get();
	}

	void SetVTClass(U32 VTClass)
	{
		get<0>().set(VTClass);
	}

	void SetLocalSessionID(U8 LocalSessionID)
	{
		get<1>().set(LocalSessionID);
	}
};
