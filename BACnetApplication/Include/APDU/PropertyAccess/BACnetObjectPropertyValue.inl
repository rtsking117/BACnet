#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>

//Object Property Value
class BACnetObjectPropertyValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>
	>
{
public:

};
