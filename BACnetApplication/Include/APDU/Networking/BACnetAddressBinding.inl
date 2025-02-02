#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Networking/BACnetAddress.inl>

//Address Binding
class BACnetAddressBinding : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetObjectIDType>,
	BACnetSequenceElement<NoTag, BACnetAddress>
	>
{
public:

};
