#pragma once

#include "BACnetBasicTypes.inl"

//=============================================================================================
//								COMPLEX TYPES
//=============================================================================================

//Accumulator Record

//Action Command

//Action List

//Address
class BACnetAddress : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned16Type, false>,
		BACnetSequenceElement<NoTag, BACnetOctetStringType, false>
	>
{
public:

};

//Address Binding

//Assigned Landing Calls

//BDT Entry

//Channel Value
class BACnetChannelValue : public
	BACnetChoice<0,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetBooleanType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>,
		BACnetChoiceElement<NoTag, BACnetSignedType>,
		BACnetChoiceElement<NoTag, BACnetFloatType>,
		BACnetChoiceElement<NoTag, BACnetDoubleType>,
		BACnetChoiceElement<NoTag, BACnetOctetStringType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
		BACnetChoiceElement<NoTag, BACnetBitStringType>,
		BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
		BACnetChoiceElement<NoTag, BACnetDateType>,
		BACnetChoiceElement<NoTag, BACnetTimeType>,
		BACnetChoiceElement<NoTag, BACnetObjectIDType>,
		BACnetChoiceElement<0, BACnetUnsignedType>
	>
{
public:

};

//Date Time
class BACnetDateTimeType : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetDateType, false>,
		BACnetSequenceElement<NoTag, BACnetTimeType, false>
	>
{
public:
	U32 GetDate()
	{
		return get<0>().get();
	}

	U32 GetTime()
	{
		return get<1>().get();
	}

	void SetDate(U32 Date)
	{
		get<0>().set(Date);
	}

	void SetTime(U32 Time)
	{
		get<1>().set(Time);
	}
};

//Destination

//FDT Entry

//Host Address

//Host and Port

//Key Identifier

//Landing Call Status

//Landing Door Status

//Lift Call Car State

//Lighting Command

//Name Value
class BACnetNameValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetCharacterStringType, false>,
		BACnetSequenceElement<NoTag, BACnetApplicationAnyDateTimeType, true>
	>
{
public:

};

//Name Value Collection
class BACnetNameValueCollection : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetNameValue>, false>
	>
{
public:

};

//Network Security Policy

//Optional Binary PV

//Optional Character String

//Optional Real

//Optional Unsigned

//Port Permission

//Prescale

//Priority Array

//Priority Value

//Process ID Selection

//Router Entry

//Scale

//Security Key Set

//Setpoint Reference

//Shed Level

//Timer State Change Value

//VMAC Entry

//VT Session
class BACnetVTSession : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<NoTag, BACnetAddress, false>
	>
{
public:

};

