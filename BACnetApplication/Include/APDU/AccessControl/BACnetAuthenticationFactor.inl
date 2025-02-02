#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Authentication Factor
class BACnetAuthenticationFactor : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorTypeType>,
		BACnetSequenceElement<1, BACnetUnsignedType>,
		BACnetSequenceElement<2, BACnetOctetStringType>
	>
{
public:

};