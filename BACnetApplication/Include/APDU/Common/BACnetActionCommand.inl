#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Action Command
class BACnetActionCommand : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, true>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetAnyType>,
		BACnetSequenceElement<5, BACnetUnsignedType, true>,
		BACnetSequenceElement<6, BACnetUnsignedType, true>,
		BACnetSequenceElement<7, BACnetBooleanType>,
		BACnetSequenceElement<8, BACnetBooleanType>
	>
{
public:

};
