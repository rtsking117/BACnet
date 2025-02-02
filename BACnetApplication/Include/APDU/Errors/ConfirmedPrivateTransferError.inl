#include "BACnetError.inl"

//Confirmed Private Transfer Error
class ConfirmedPrivateTransferError : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetError>,
	BACnetSequenceElement<1, BACnetUnsigned16Type>,
	BACnetSequenceElement<2, BACnetUnsignedType>,
	BACnetSequenceElement<3, BACnetAnyType, true>
	>
{
public:

};