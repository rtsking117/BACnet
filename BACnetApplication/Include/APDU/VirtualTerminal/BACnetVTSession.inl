#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Networking/BACnetAddress.inl>

//VT Session
class BACnetVTSession : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type>,
		BACnetSequenceElement<NoTag, BACnetAddress>
	>
{
public:

};