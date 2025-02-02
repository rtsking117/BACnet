#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/PropertyAccess/BACnetPropertyReference.inl>

//Subscribe COV Property Multiple
class SubscribeCOVPropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetBooleanType, true>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType>,
					BACnetSequenceElement<1,
						BACnetSequenceOf<
							BACnetSequence<
								BACnetSequenceElement<0, BACnetPropertyReference>,
								BACnetSequenceElement<1, BACnetRealValueType, true>,
								BACnetSequenceElement<2, BACnetBooleanType>
							>
						>
					>
				>
			>
		>
	>
{
public:

};
