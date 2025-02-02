#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Object Property Reference
class BACnetObjectPropertyReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>
	>
{
public:

};
