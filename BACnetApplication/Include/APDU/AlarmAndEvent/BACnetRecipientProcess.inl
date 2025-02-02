#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/AlarmAndEvent/BACnetRecipient.inl>

//Recipient Process
class BACnetRecipientProcess : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipient>,
		BACnetSequenceElement<1, BACnetUnsigned32Type>
	>
{
public:

};