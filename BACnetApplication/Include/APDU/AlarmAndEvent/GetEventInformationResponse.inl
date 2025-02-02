#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetTimeStamp.inl>

//Get Event Information Ack
class GetEventInformationResponse : public
	BACnetSequence<
		BACnetSequenceElement<0,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType>,
					BACnetSequenceElement<1, BACnetEnumeratedType>,
					BACnetSequenceElement<2, BACnetBitStringType>,
					BACnetSequenceElement<3, BACnetSequenceOf<BACnetTimeStamp>>,
					BACnetSequenceElement<4, BACnetEnumeratedType>,
					BACnetSequenceElement<5, BACnetBitStringType>,
					BACnetSequenceElement<6, BACnetSequenceOf<BACnetUnsignedType>>
				>
			>
		>,
		BACnetSequenceElement<1, BACnetBooleanType>
	>
{
public:

};