#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectPropertyReference.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectReference.inl>

//Access Rule
class BACnetAccessRule : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType>,
		BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetDeviceObjectReference, true>,
		BACnetSequenceElement<4, BACnetBooleanType>
	>
{
public:

};
