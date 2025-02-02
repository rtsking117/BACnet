#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Device Object Property Value
class BACnetDeviceObjectPropertyValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetAnyType>
	>
{
public:

};
