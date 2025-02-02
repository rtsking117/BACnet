#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Network Security Policy
class BACnetNetworkSecurityPolicy : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type>,
		BACnetSequenceElement<1, BACnetSecurityPolicyType>
	>
{
public:

};