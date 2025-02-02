#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Name Value
class BACnetNameValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetCharacterStringType>,
		BACnetSequenceElement<NoTag, BACnetApplicationAnyDateTimeType, true>
	>
{
public:

};
