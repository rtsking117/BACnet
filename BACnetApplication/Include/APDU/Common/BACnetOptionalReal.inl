#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Optional Real
class BACnetOptionalReal : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetRealValueType>
	>
{
public:

};
