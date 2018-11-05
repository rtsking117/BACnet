#pragma once

#include "BACnetBasicTypes.inl"

//=============================================================================================
//								COMPLEX TYPES
//=============================================================================================

//Accumulator Record
class BACnetAccumulatorRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, false>,
		BACnetSequenceElement<3, BACnetEnumeratedType, false>
	>
{
public:

};

//Action Command
class BACnetActionCommand : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, true>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetPropertyIdentifierType, false>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetAnyType, false>,
		BACnetSequenceElement<5, BACnetUnsignedType, true>,
		BACnetSequenceElement<6, BACnetUnsignedType, true>,
		BACnetSequenceElement<7, BACnetBooleanType, false>,
		BACnetSequenceElement<8, BACnetBooleanType, false>
	>
{
public:

};

//Action List
class BACnetActionList : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetActionCommand>, false>
	>
{
public:

};

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
class BACnetAddressBinding : public 
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag, BACnetAddress, false>
	>
{
public:

};

//Assigned Landing Calls
class BACnetAssignedLandingCalls : public 
	BACnetSequence<
		BACnetSequenceElement<0, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
					BACnetSequenceElement<1, BACnetLiftCarDirectionType, false>,
				>
			>,
			false
		>
	>
{
public:

};

//BDT Entry
class BACnetBDTEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetHostNPort, false>,
		BACnetSequenceElement<1, BACnetOctetStringType, true>,
	>
{
public:

};

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
class BACnetFDTEntry : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetOctetStringType, false>,
		BACnetSequenceElement<1, BACnetUnsigned16Type, false>,
		BACnetSequenceElement<2, BACnetUnsigned16Type, false>
	>
{
public:

};

//Host Address
class BACnetHostAddress : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetNullType>,
		BACnetChoiceElement<1, BACnetOctetStringType>,
		BACnetChoiceElement<2, BACnetCharacterStringType>,
	>
{
public: 

};

//Host and Port
class BACnetHostNPort : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetHostAddress, false>,
		BACnetSequenceElement<1, BACnetUnsigned16Type, false>
	>
{
public:

};


//Key Identifier
class BACnetKeyIdentifier : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<1, BACnetUnsigned8Type, false>
	>
{
public:

};

//Landing Call Status
class BACnetLandingCallStatus : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<NoTag, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<1, BACnetLiftCarDirectionType>,
				BACnetChoiceElement<2, BACnetUnsigned8Type>,
			>,
			false
		>,
		BACnetSequenceElement<3, BACnetCharacterStringType, true>,
	>
{
public:

};


//Landing Door Status
class BACnetLandingDoorStatus : public
	BACnetSequence<
		BACnetSequenceElement<0,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
					BACnetSequenceElement<1, BACnetDoorStatusType, false>,
				>
			>,
			false
		>
	>
{
public:

};
//Lift Call Car State
class BACnetLiftCallCarState : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetUnsigned8Type>, false>
	>
{
public:

};

//Lighting Command
class BACnetLightingCommand : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetLightingOperationType, false>,
		BACnetSequenceElement<1, BACnetRealValueType, true>,
		BACnetSequenceElement<2, BACnetRealValueType, true>,
		BACnetSequenceElement<3, BACnetRealValueType, true>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>,
		BACnetSequenceElement<5, BACnetUnsignedType, true>
	>
{
public:

};

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
class BACnetNetworkSecurityPolicy : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<1, BACnetSecurityPolicyType, false>
	>
{
public:

};

//Optional Binary PV
class BACnetOptionalBinaryPV : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetBinaryPVType>
	>
{
public:

};

//Optional Character String
class BACnetOptionalCharacterString : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>
	>
{
public:

};

//Optional Real
class BACnetOptionalReal : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetRealValueType>
	>
{
public:

};

//Optional Unsigned
class BACnetOptionalUnsigned : public
	BACnetChoice<NoDefault, 
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>
	>
{
public:

};

//Port Permission
class BACnetPortPermission : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<1, BACnetBooleanType, false>
	>
{
public:

};

//Prescale
class BACnetPrescale : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsignedType, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, false>
	>
{
public:

};

//Priority Array
class BACnetPriorityArray : public
	BACnetSequenceOf<BACnetPriorityValue>
{
public:

};

//Priority Value
class BACnetPriorityValue : public 
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetRealValueType>,
		BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>,
		BACnetChoiceElement<NoTag, BACnetBooleanType>,
		BACnetChoiceElement<NoTag, BACnetSignedType>,
		BACnetChoiceElement<NoTag, BACnetDoubleType>,
		BACnetChoiceElement<NoTag, BACnetTimeType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
		BACnetChoiceElement<NoTag, BACnetOctetStringType>,
		BACnetChoiceElement<NoTag, BACnetBitStringType>,
		BACnetChoiceElement<NoTag, BACnetDateType>,
		BACnetChoiceElement<NoTag, BACnetObjectIDType>,
		BACnetChoiceElement<0, BACnetAnyType>,
		BACnetChoiceElement<1, BACnetDateTimeType>
	>
{
public:

};

//Process ID Selection
class BACnetProcessIDSelection : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetUnsigned32Type>,
		BACnetChoiceElement<NoTag, BACnetNullType>
	>
{
public:

};

//Router Entry
class BACnetRouterEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
		BACnetSequenceElement<1, BACnetOctetStringType, false>,
		BACnetSequenceElement<2, BACnetEnumeratedType, false>,
		BACnetSequenceElement<3, BACnetUnsigned8Type, true>
	>
{
public:

};

//Scale
class BACnetScale : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetRealValueType>,
		BACnetChoiceElement<1, BACnetSignedType>
	>
{
public:

};

//Security Key Set
class BACnetSecurityKeySet : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<1, BACnetDateTimeType, false>,
		BACnetSequenceElement<2, BACnetDateTimeType, false>,
		BACnetSequenceElement<3, BACnetSequenceOf<BACnetKeyIdentifier>, false>
	>
{
public:

};

//Setpoint Reference
class BACnetSetpointReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSequenceOf<BACnetObjectPropertyReference>, true>
	>
{
public:

};

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

//Timer State Change Value
class BACnetTimerStateChangeValue : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetNullType>,
		BACnetChoiceElement<NoTag, BACnetBooleanType>,
		BACnetChoiceElement<NoTag, BACnetUnsignedType>,
		BACnetChoiceElement<NoTag, BACnetSignedType>,
		BACnetChoiceElement<NoTag, BACnetRealValueType>,
		BACnetChoiceElement<NoTag, BACnetDoubleType>,
		BACnetChoiceElement<NoTag, BACnetOctetStringType>,
		BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
		BACnetChoiceElement<NoTag, BACnetBitStringType>,
		BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
		BACnetChoiceElement<NoTag, BACnetDateType>,
		BACnetChoiceElement<NoTag, BACnetTimeType>,
		BACnetChoiceElement<NoTag, BACnetObjectIDType>,
		BACnetChoiceElement<0, BACnetNullType>,
		BACnetChoiceElement<1, BACnetAnyType>,
		BACnetChoiceElement<2, BACnetDateTimeType>,
		BACnetChoiceElement<3, BACnetLightingCommand>
	>
{
public:

};

//VMAC Entry
class BACnetVMACEntry : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetOctetStringType, false>,
		BACnetSequenceElement<1, BACnetOctetStringType, false>
	>
{
public:

};

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

