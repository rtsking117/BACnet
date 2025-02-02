#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectReference.inl>

//Assigned Access Rights
class BACnetAssignedAccessRights : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDeviceObjectReference>,
		BACnetSequenceElement<1, BACnetBooleanType>
	>
{
public:

};