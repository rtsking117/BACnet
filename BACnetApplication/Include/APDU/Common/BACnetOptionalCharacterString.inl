#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Optional Character String
class BACnetOptionalCharacterString : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>
	>
{
public:

};
