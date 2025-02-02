#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Errors/BACnetError.inl>


//Property Access Result
class BACnetPropertyAccessResult : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetObjectIDType, true>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<4, BACnetAnyType>,
				BACnetChoiceElement<5, BACnetError>
			>
		>
	>
{
public:

};
