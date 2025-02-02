#include "BACnetError.inl"
#include "../PropertyAccess/BACnetPropertyReference.inl"

//Subscribe COV Property Multiple Error
class SubscribeCOVPropertyMultipleError : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError>,
		BACnetSequenceElement<1,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetObjectIDType>,
				BACnetSequenceElement<1, BACnetPropertyReference>,
				BACnetSequenceElement<2, BACnetError>
			>
		>
	>
{
public:

};