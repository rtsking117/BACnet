#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Address
class BACnetAddress : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetUnsigned16Type>,
	BACnetSequenceElement<NoTag, BACnetOctetStringType>
	>
{
public:

};