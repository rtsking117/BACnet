#pragma once

#include "BACnetBasicTypes.inl"
#include "BACnetComplexTypes.inl"
#include "BACnetPropertyTypes.inl"


//Access Rule
class BACnetAccessRule : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType, false>,
		BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType, false>,
		BACnetSequenceElement<3, BACnetDeviceObjectReference, true>,
		BACnetSequenceElement<4, BACnetBooleanType, false>
	>
{
public:

};

//Assigned Access Rights
class BACnetAssignedAccessRights : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDeviceObjectReference, false>,
		BACnetSequenceElement<1, BACnetBooleanType, false>,
	>
{
public:

};

//Authentication Factor
class BACnetAuthenticationFactor : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorTypeType, false>,	
		BACnetSequenceElement<1, BACnetUnsignedType, false>,
		BACnetSequenceElement<2, BACnetOctetStringType, false>
	>
{
public:

};

//Authentication Factor Format
class BACnetAuthenticationFactorFormat : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorTypeType, false>,
		BACnetSequenceElement<1, BACnetUnsigned16Type, true>,
		BACnetSequenceElement<2, BACnetUnsigned16Type, true>
	>
{
public:

};

//Authentication Policy
class BACnetAuthenticationPolicy : public 
	BACnetSequence<
		BACnetSequenceElement<0, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetDeviceObjectReference, false>,
					BACnetSequenceElement<1, BACnetUnsignedType, false>,
				>
			>, false
		>,
		BACnetSequenceElement<1, BACnetBooleanType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, false>
	>
{
public:

};

//Credential Authentication Factor
class BACnetCredentialAuthenticationFactor : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorDisableType, false>,
		BACnetSequenceElement<1, BACnetAuthenticationFactor, false>
	>
{
public:

};
