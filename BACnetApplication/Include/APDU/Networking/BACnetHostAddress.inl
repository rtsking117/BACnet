#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Host Address
class BACnetHostAddress : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetNullType>,
		BACnetChoiceElement<1, BACnetOctetStringType>,
		BACnetChoiceElement<2, BACnetCharacterStringType>
	>
{
public:

};
