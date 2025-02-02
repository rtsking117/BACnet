#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPropertyValue.inl>

//Write Access Specification
class WriteAccessSpecification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyValue>>
	>
{
public:

};