#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectPropertyReference.inl>
#include <APDU/PropertyAccess/BACnetPropertyStates.inl>

//Event Parameter
class BACnetEventParameter : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetBitStringType>,
				BACnetSequenceElement<2, BACnetSequenceOf<BACnetBitStringType>>
			>
		>,
		BACnetChoiceElement<1,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyStates>>
			>
		>,
		BACnetChoiceElement<2, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, 
					BACnetChoice<NoDefault,
						BACnetChoiceElement<0, BACnetBitStringType>,
						BACnetChoiceElement<1, BACnetRealValueType>
					>
				>
			>
		>,
		BACnetChoiceElement<3,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<4,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>,
				BACnetSequenceElement<2, BACnetRealValueType>,
				BACnetSequenceElement<3, BACnetRealValueType>,
				BACnetSequenceElement<4, BACnetRealValueType>
			>
		>,
		BACnetChoiceElement<5,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetRealValueType>,
				BACnetSequenceElement<2, BACnetRealValueType>,
				BACnetSequenceElement<3, BACnetRealValueType>
			>
		>,
		BACnetChoiceElement<8,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetLifeSafetyStateType>>,
				BACnetSequenceElement<2, BACnetSequenceOf<BACnetLifeSafetyStateType>>,
				BACnetSequenceElement<3, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<9, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsigned16Type>,
				BACnetSequenceElement<1, BACnetUnsignedType>,
				BACnetSequenceElement<2, 
					BACnetSequenceOf<
						BACnetChoice<NoDefault,
							BACnetChoiceElement<NoTag, BACnetNullType>,
							BACnetChoiceElement<NoTag, BACnetRealValueType>,
							BACnetChoiceElement<NoTag, BACnetUnsignedType>,
							BACnetChoiceElement<NoTag, BACnetBooleanType>,
							BACnetChoiceElement<NoTag, BACnetSignedType>,
							BACnetChoiceElement<NoTag, BACnetDoubleType>,
							BACnetChoiceElement<NoTag, BACnetOctetStringType>,
							BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
							BACnetChoiceElement<NoTag, BACnetBitStringType>,
							BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
							BACnetChoiceElement<NoTag, BACnetDateType>,
							BACnetChoiceElement<NoTag, BACnetTimeType>,
							BACnetChoiceElement<NoTag, BACnetObjectIDType>,
							BACnetChoiceElement<0, BACnetDeviceObjectPropertyReference>
						>
					>
				>
			>
		>,
		BACnetChoiceElement<10,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsigned32Type>
			>
		>,
		BACnetChoiceElement<11,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsignedType>,
				BACnetSequenceElement<2, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<13, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetAccessEventType>>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<14, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetDoubleType>,
				BACnetSequenceElement<2, BACnetDoubleType>,
				BACnetSequenceElement<3, BACnetDoubleType>
			>
		>,
		BACnetChoiceElement<15,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSignedType>,
				BACnetSequenceElement<2, BACnetSignedType>,
				BACnetSequenceElement<3, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<16,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsignedType>,
				BACnetSequenceElement<2, BACnetUnsignedType>,
				BACnetSequenceElement<3, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<17,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetCharacterStringType>>
			>
		>,
		BACnetChoiceElement<18,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetStatusFlagsType>
			>
		>,
		BACnetChoiceElement<20, BACnetNullType>,
		BACnetChoiceElement<21, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<22,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetTimerStateType>>,
				BACnetSequenceElement<2, BACnetDeviceObjectPropertyReference>
			>
		>
	>
{
public:

};
