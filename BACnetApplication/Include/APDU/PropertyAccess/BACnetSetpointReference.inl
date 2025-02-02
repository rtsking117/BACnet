#pragma once 
#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetObjectPropertyReference.inl>

//Setpoint Reference
class BACnetSetpointReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetObjectPropertyReference>, true>
	>
{
public:

};
