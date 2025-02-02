#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Channel Value
class BACnetChannelValue : public
	BACnetChoice<0,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetBooleanType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>,
		BACnetChoiceElement<NoTag, BACnetSignedType>,
		BACnetChoiceElement<NoTag, BACnetFloatType>,
		BACnetChoiceElement<NoTag, BACnetDoubleType>,
		BACnetChoiceElement<NoTag, BACnetOctetStringType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
		BACnetChoiceElement<NoTag, BACnetBitStringType>,
		BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
		BACnetChoiceElement<NoTag, BACnetDateType>,
		BACnetChoiceElement<NoTag, BACnetTimeType>,
		BACnetChoiceElement<NoTag, BACnetObjectIDType>,
		BACnetChoiceElement<0, BACnetUnsignedType>
	>
{
public:

};