#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Key Identifier
class BACnetKeyIdentifier : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type>,
		BACnetSequenceElement<1, BACnetUnsigned8Type>
	>
{
public:

};
