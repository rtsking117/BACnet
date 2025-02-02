#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Port Permission
class BACnetPortPermission : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type>,
		BACnetSequenceElement<1, BACnetBooleanType>
	>
{
public:

};
