#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/AccessControl/BACnetAuthenticationFactor.inl>

//Credential Authentication Factor
class BACnetCredentialAuthenticationFactor : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorDisableType>,
		BACnetSequenceElement<1, BACnetAuthenticationFactor>
	>
{
public:

};
