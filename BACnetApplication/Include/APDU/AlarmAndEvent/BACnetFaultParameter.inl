#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectPropertyReference.inl>
#include <APDU/PropertyAccess/BACnetPropertyStates.inl>

//Fault Parameter
class BACnetFaultParameter : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetNullType>,
		BACnetChoiceElement<1, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetCharacterStringType>>
			>
		>,
		BACnetChoiceElement<2,
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
		BACnetChoiceElement<3, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetLifeSafetyStateType>>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<4, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetPropertyStates>>
			>
		>,
		BACnetChoiceElement<5, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<6,
			BACnetSequence<
				BACnetSequenceElement<0,
					BACnetChoice<NoDefault,
						BACnetChoiceElement<NoTag, BACnetRealValueType>,
						BACnetChoiceElement<NoTag, BACnetUnsignedType>,
						BACnetChoiceElement<NoTag, BACnetDoubleType>,
						BACnetChoiceElement<NoTag, BACnetSignedType>
					>
				>,
				BACnetSequenceElement<1,
					BACnetChoice<NoDefault,
						BACnetChoiceElement<NoTag, BACnetRealValueType>,
						BACnetChoiceElement<NoTag, BACnetUnsignedType>,
						BACnetChoiceElement<NoTag, BACnetDoubleType>,
						BACnetChoiceElement<NoTag, BACnetSignedType>
					>
				>
			>
		>,
		BACnetChoiceElement<7,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetDeviceObjectPropertyReference>
			>
		>
	>
{
public:

};
