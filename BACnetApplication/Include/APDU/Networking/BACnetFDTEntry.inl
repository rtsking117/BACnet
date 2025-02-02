#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//FDT Entry
class BACnetFDTEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetOctetStringType>,
		BACnetSequenceElement<1, BACnetUnsigned16Type>,
		BACnetSequenceElement<2, BACnetUnsigned16Type>
	>
{
public:

};
