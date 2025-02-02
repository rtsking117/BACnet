#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/NetworkSecurity/BACnetKeyIdentifier.inl>

//Security Key Set
class BACnetSecurityKeySet : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type>,
		BACnetSequenceElement<1, BACnetDateTimeType>,
		BACnetSequenceElement<2, BACnetDateTimeType>,
		BACnetSequenceElement<3, BACnetSequenceOf<BACnetKeyIdentifier>>
	>
{
public:

};
