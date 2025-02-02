#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Networking/BACnetHostAndPort.inl>

//BDT Entry
class BACnetBDTEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetHostAndPort>,
		BACnetSequenceElement<1, BACnetOctetStringType, true>
	>
{
public:

};
