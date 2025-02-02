#include "BACnetError.inl"

//VT Close Error
class VTCloseError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetSequenceOf<BACnetUnsigned8Type>, true>
	>
{
public:

};