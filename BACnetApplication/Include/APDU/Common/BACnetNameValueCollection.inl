#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetNameValue.inl>

//Name Value Collection
class BACnetNameValueCollection : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetNameValue>>
	>
{
public:

};
