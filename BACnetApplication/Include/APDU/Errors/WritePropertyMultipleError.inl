#pragma once

#include <APDU/Errors/BACnetError.inl>
#include <APDU/PropertyAccess/BACnetObjectPropertyReference.inl>

//Write Property Multiple Error
class WritePropertyMultipleError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetObjectPropertyReference>
	>
{
public:

};