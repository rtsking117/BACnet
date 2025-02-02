#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Errors/BACnetError.inl>

//Read Access Result
class ReadAccessResult : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<2, BACnetPropertyIdentifierType>,
					BACnetSequenceElement<3, BACnetUnsignedType, true>,
					BACnetSequenceElement<NoTag,
						BACnetChoice<NoDefault,
							BACnetChoiceElement<4, BACnetAnyType>,
							BACnetChoiceElement<5, BACnetError>
						>,
						false
					>
				>
			>,
			true
		>
	>
{
public:

};
