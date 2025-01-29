#pragma once

#include "BACnetBasicTypes.inl"
#include "BACnetComplexTypes.inl"
#include "BACnetPropertyTypes.inl"


//Access Rule
class BACnetAccessRule : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType>,
		BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetDeviceObjectReference, true>,
		BACnetSequenceElement<4, BACnetBooleanType>
	>
{
public:

};

//Assigned Access Rights
class BACnetAssignedAccessRights : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDeviceObjectReference>,
		BACnetSequenceElement<1, BACnetBooleanType>,
	>
{
public:

};

//Authentication Factor
class BACnetAuthenticationFactor : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorTypeType>,	
		BACnetSequenceElement<1, BACnetUnsignedType>,
		BACnetSequenceElement<2, BACnetOctetStringType>
	>
{
public:

};

//Authentication Factor Format
class BACnetAuthenticationFactorFormat : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorTypeType>,
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
					BACnetSequenceElement<0, BACnetDeviceObjectReference>,
					BACnetSequenceElement<1, BACnetUnsignedType>,
				>
			>, false
		>,
		BACnetSequenceElement<1, BACnetBooleanType>,
		BACnetSequenceElement<2, BACnetUnsignedType>
	>
{
public:

};

//Credential Authentication Factor
class BACnetCredentialAuthenticationFactor : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAuthenticationFactorDisableType>,
		BACnetSequenceElement<1, BACnetAuthenticationFactor>
	>
{
public:

};
