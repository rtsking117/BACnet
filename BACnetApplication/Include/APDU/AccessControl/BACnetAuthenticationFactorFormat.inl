#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Authentication Factor Format
class BACnetAuthenticationFactorFormat : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorTypeType>,
		BACnetSequenceElement<1, BACnetUnsigned16Type, true>,
		BACnetSequenceElement<2, BACnetUnsigned16Type, true>
	>
{
public:

};
