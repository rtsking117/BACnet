#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Shed Level
class BACnetShedLevel : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetUnsignedType>,
		BACnetChoiceElement<1, BACnetUnsignedType>,
		BACnetChoiceElement<2, BACnetRealValueType>
	>
{
public:

};
