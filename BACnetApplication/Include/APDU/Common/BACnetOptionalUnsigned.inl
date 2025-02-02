#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Optional Unsigned
class BACnetOptionalUnsigned : public
	BACnetChoice<NoDefault, 
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>
	>
{
public:

};
