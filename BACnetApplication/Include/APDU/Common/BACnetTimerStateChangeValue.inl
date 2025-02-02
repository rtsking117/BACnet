#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/Common/BACnetLightingCommand.inl>

//Timer State Change Value
class BACnetTimerStateChangeValue : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetBooleanType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>,
		BACnetChoiceElement<NoTag, BACnetSignedType>,
		BACnetChoiceElement<NoTag, BACnetRealValueType>,
		BACnetChoiceElement<NoTag, BACnetDoubleType>,
		BACnetChoiceElement<NoTag, BACnetOctetStringType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
		BACnetChoiceElement<NoTag, BACnetBitStringType>,
		BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
		BACnetChoiceElement<NoTag, BACnetDateType>,
		BACnetChoiceElement<NoTag, BACnetTimeType>,
		BACnetChoiceElement<NoTag, BACnetObjectIDType>,
		BACnetChoiceElement<0, BACnetNullType>,
		BACnetChoiceElement<1, BACnetAnyType>,
		BACnetChoiceElement<2, BACnetDateTimeType>,
		BACnetChoiceElement<3, BACnetLightingCommand>
	>
{
public:

};
