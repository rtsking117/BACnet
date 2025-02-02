#include "BACnetError.inl"


//Change List Error
class ChangeListError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1, BACnetUnsignedType>
	>
{
public:

};