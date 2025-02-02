#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetChannelValue.inl>

//Group Channel Value
class BACnetGroupChannelValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>,
		BACnetSequenceElement<NoTag, BACnetChannelValue>
	>
{
public:

};