#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Networking/BACnetAddress.inl>

//Recipient
class BACnetRecipient : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetObjectIDType>,
		BACnetChoiceElement<1, BACnetAddress>
	>
{
public:

};
