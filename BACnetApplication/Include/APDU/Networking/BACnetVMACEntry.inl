#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//VMAC Entry
class BACnetVMACEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetOctetStringType>,
		BACnetSequenceElement<1, BACnetOctetStringType>
	>
{
public:

};