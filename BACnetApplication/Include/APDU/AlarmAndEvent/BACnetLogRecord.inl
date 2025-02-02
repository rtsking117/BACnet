#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Common/BACnetNamedTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/Errors/BACnetError.inl>

//Log Record
class BACnetLogRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetLogStatusType>,
				BACnetChoiceElement<1, BACnetBooleanType>,
				BACnetChoiceElement<2, BACnetRealValueType>,
				BACnetChoiceElement<3, BACnetEnumeratedType>,
				BACnetChoiceElement<4, BACnetUnsignedType>,
				BACnetChoiceElement<5, BACnetSignedType>,
				BACnetChoiceElement<6, BACnetBitStringType>,
				BACnetChoiceElement<7, BACnetNullType>,
				BACnetChoiceElement<8, BACnetError>,
				BACnetChoiceElement<9, BACnetRealValueType>,
				BACnetChoiceElement<10, BACnetAnyType>
			>
		>,
		BACnetSequenceElement<2, BACnetStatusFlagsType, true>
	>
{
public:

};