#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Device Object Reference
class BACnetDeviceObjectReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, true>,
		BACnetSequenceElement<1, BACnetObjectIDType>
	>
{
public:

};
