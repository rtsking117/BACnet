#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetActionCommand.inl>

//Action List
class BACnetActionList : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetActionCommand>>
	>
{
public:

};
