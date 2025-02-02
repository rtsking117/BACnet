#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Get Event Information
class GetEventInformationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, true>
	>
{
public:

};
