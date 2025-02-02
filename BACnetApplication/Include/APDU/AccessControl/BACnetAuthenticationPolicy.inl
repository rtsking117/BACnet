#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectReference.inl>

//Authentication Policy
class BACnetAuthenticationPolicy : public 
	BACnetSequence<
		BACnetSequenceElement<0, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetDeviceObjectReference>,
					BACnetSequenceElement<1, BACnetUnsignedType>
				>
			>
		>,
		BACnetSequenceElement<1, BACnetBooleanType>,
		BACnetSequenceElement<2, BACnetUnsignedType>
	>
{
public:

};
