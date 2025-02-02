#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>

//Priority Value
class BACnetPriorityValue : public 
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetRealValueType>,
		BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>,
		BACnetChoiceElement<NoTag, BACnetBooleanType>,
		BACnetChoiceElement<NoTag, BACnetSignedType>,
		BACnetChoiceElement<NoTag, BACnetDoubleType>,
		BACnetChoiceElement<NoTag, BACnetTimeType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
		BACnetChoiceElement<NoTag, BACnetOctetStringType>,
		BACnetChoiceElement<NoTag, BACnetBitStringType>,
		BACnetChoiceElement<NoTag, BACnetDateType>,
		BACnetChoiceElement<NoTag, BACnetObjectIDType>,
		BACnetChoiceElement<0, BACnetAnyType>,
		BACnetChoiceElement<1, BACnetDateTimeType>
	>
{
public:

};
