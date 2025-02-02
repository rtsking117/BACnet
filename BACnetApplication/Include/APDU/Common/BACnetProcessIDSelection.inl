#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Process ID Selection
class BACnetProcessIDSelection : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetUnsigned32Type>,
		BACnetChoiceElement<NoTag, BACnetNullType>
	>
{
public:

};
