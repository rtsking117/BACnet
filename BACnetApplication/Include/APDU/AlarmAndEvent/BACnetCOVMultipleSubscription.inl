#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/AlarmAndEvent/BACnetRecipientProcess.inl>
#include <APDU/PropertyAccess/BACnetPropertyReference.inl>

class BACnetSubscribedProperty : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetPropertyReference>,
		BACnetSequenceElement<1, BACnetRealValueType, true>,
		BACnetSequenceElement<2, BACnetBooleanType>
	>
{

};

class BACnetSubscribedObject : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetSequenceOf<BACnetSubscribedProperty>>
	>
{

};

//COV Multiple Subscription
class BACnetCOVMultipleSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipientProcess>,
		BACnetSequenceElement<1, BACnetBooleanType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetSubscribedObject>>
	>
{
public:

};
