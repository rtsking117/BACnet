#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Networking/BACnetHostAddress.inl>

//Host and Port
class BACnetHostAndPort : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetHostAddress>,
		BACnetSequenceElement<1, BACnetUnsigned16Type>
	>
{
public:

};
