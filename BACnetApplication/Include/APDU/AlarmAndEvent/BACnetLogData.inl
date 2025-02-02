#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Errors/BACnetError.inl>

//Log Data
class BACnetLogData : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetLogStatusType>,
		BACnetChoiceElement<1, 
			BACnetSequenceOf<
				BACnetChoice<NoDefault,
					BACnetChoiceElement<0, BACnetBooleanType>,
					BACnetChoiceElement<1, BACnetRealValueType>,
					BACnetChoiceElement<2, BACnetEnumeratedType>,
					BACnetChoiceElement<3, BACnetUnsignedType>,
					BACnetChoiceElement<4, BACnetSignedType>,
					BACnetChoiceElement<5, BACnetBitStringType>,
					BACnetChoiceElement<6, BACnetNullType>,
					BACnetChoiceElement<7, BACnetError>,
					BACnetChoiceElement<8, BACnetAnyType>
				>
			>
		>
	>
{
public:

};