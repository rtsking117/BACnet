#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

class BACnetNotifyingProperty : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>,
		BACnetSequenceElement<2, BACnetAnyType>,
		BACnetSequenceElement<3, BACnetTimeType, true>
	>
{

};

class BACnetNotifyingDevice : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetSequenceOf<BACnetNotifyingProperty>>
	>
{

};
