#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Scale
class BACnetScale : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetRealValueType>,
		BACnetChoiceElement<1, BACnetSignedType>
	>
{
public:

};
