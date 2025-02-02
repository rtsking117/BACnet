#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPropertyReference.inl>

//Read Access Specification
class ReadAccessSpecification : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType>,
	BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyReference>>
	>
{
public:

};
