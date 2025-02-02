#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPriorityValue.inl>

//Priority Array
class BACnetPriorityArray : public
	BACnetSequenceOf<BACnetPriorityValue>
{
public:

};
