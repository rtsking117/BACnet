#pragma once

#include "BACnetBasicTypes.inl"

//=============================================================================================
//								COMPLEX TYPES
//=============================================================================================

//Access Rule

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

//Assigned Access Rights

//Assigned Landing Calls

//Authentication Factor

//Authentication Factor Format

//Authentication Policy

//BDT Entry

//Calendar Entry

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

//Client COV

//COV Multiple Subscription

//COV Subscription

//Credential Authentication Factor

//Daily Schedule

//Date Range

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

//Device Object Property Reference
class BACnetDeviceObjectPropertyReference : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetPropertyIdentifierType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, true>,
	BACnetSequenceElement<3, BACnetObjectIDType, true>
	>
{
public:

};

//Device Object Property Value
class BACnetDeviceObjectPropertyValue : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetObjectIDType, false>,
	BACnetSequenceElement<2, BACnetPropertyIdentifierType, false>,
	BACnetSequenceElement<3, BACnetUnsignedType, true>,
	BACnetSequenceElement<4, BACnetAnyType, false>
	>
{
public:

};

//Device Object Reference
class BACnetDeviceObjectReference : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, true>,
	BACnetSequenceElement<1, BACnetObjectIDType, false>
	>
{
public:

};

//Event Log Record

//Event Notification Subscription

//Event Parameter

//Fault Parameter

//FDT Entry

//Group Channel Value
class BACnetGroupChannelValue : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, true>,
	BACnetSequenceElement<NoTag, BACnetChannelValue, false>
	>
{
public:

};

//Host Address

//Host and Port

//Key Identifier

//Landing Call Status

//Landing Door Status

//Lift Call Car State

//Lighting Command

//Log Data

//Log Multiple Record

//Log Record

//Name Value

//Name Value Collection

//Network Security Policy

//Time Stamp
class BACnetTimeStamp : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetTimeType, false>,
	BACnetSequenceElement<1, BACnetUnsigned16Type, false>,
	BACnetSequenceElement<2, BACnetDateTimeType, false>
	>
{
public:

};


//Property States
class BACnetPropertyStates : public
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0, BACnetBooleanType>,
	BACnetChoiceElement<1, BACnetBinaryPVType>,
	BACnetChoiceElement<2, BACnetEventTypeType>,
	BACnetChoiceElement<3, BACnetPolarityType>,
	BACnetChoiceElement<4, BACnetProgramRequestType>,
	BACnetChoiceElement<5, BACnetProgramStateType>,
	BACnetChoiceElement<6, BACnetProgramErrorType>,
	BACnetChoiceElement<7, BACnetReliabilityType>,
	BACnetChoiceElement<8, BACnetEventStateType>,
	BACnetChoiceElement<9, BACnetDeviceStatusType>,
	BACnetChoiceElement<10, BACnetEngineeringUnitsType>,
	BACnetChoiceElement<11, BACnetUnsignedType>,
	BACnetChoiceElement<12, BACnetLifeSafetyModeType>,
	BACnetChoiceElement<13, BACnetLifeSafetyStateType>,
	BACnetChoiceElement<14, BACnetRestartReasonType>,
	BACnetChoiceElement<15, BACnetDoorAlarmStateType>,
	BACnetChoiceElement<16, BACnetActionType>,
	BACnetChoiceElement<17, BACnetDoorSecuredStatusType>,
	BACnetChoiceElement<18, BACnetDoorStatusType>,
	BACnetChoiceElement<19, BACnetDoorValueType>,
	BACnetChoiceElement<20, BACnetFileAccessMethodType>,
	BACnetChoiceElement<21, BACnetLockStatusType>,
	BACnetChoiceElement<22, BACnetLifeSafetyOperationType>,
	BACnetChoiceElement<23, BACnetMaintenanceType>,
	BACnetChoiceElement<24, BACnetNodeTypeType>,
	BACnetChoiceElement<25, BACnetNotifyTypeType>,
	BACnetChoiceElement<26, BACnetSecurityLevelType>,
	BACnetChoiceElement<27, BACnetShedStateType>,
	BACnetChoiceElement<28, BACnetSilencedStateType>,
	BACnetChoiceElement<30, BACnetAccessEventType>,
	BACnetChoiceElement<31, BACnetAccessZoneOccupancyStateType>,
	BACnetChoiceElement<32, BACnetAccessCredentialDisableReasonType>,
	BACnetChoiceElement<33, BACnetAccessCredentialDisableType>,
	BACnetChoiceElement<34, BACnetAuthenticationStatusType>,
	BACnetChoiceElement<36, BACnetBackupStateType>,
	BACnetChoiceElement<37, BACnetWriteStatusType>,
	BACnetChoiceElement<38, BACnetLightingInProgressType>,
	BACnetChoiceElement<39, BACnetLightingOperationType>,
	BACnetChoiceElement<30, BACnetLightingTransitionType>,
	BACnetChoiceElement<41, BACnetSignedType>,
	BACnetChoiceElement<42, BACnetBinaryLightingPVType>,
	BACnetChoiceElement<43, BACnetTimerStateType>,
	BACnetChoiceElement<44, BACnetTimerTransitionType>,
	BACnetChoiceElement<45, BACnetIPModeType>,
	BACnetChoiceElement<46, BACnetNetworkPortCommandType>,
	BACnetChoiceElement<47, BACnetNetworkTypeType>,
	BACnetChoiceElement<48, BACnetNetworkNumberQualityType>,
	BACnetChoiceElement<49, BACnetEscalatorOperationDirectionType>,
	BACnetChoiceElement<40, BACnetEscalatorFaultType>,
	BACnetChoiceElement<31, BACnetEscalatorModeType>,
	BACnetChoiceElement<52, BACnetLiftCarDirectionType>,
	BACnetChoiceElement<53, BACnetLiftCarDoorCommandType>,
	BACnetChoiceElement<54, BACnetLiftCarDriveStatusType>,
	BACnetChoiceElement<55, BACnetLiftCarModeType>,
	BACnetChoiceElement<56, BACnetLiftGroupModeType>,
	BACnetChoiceElement<57, BACnetLiftFaultType>,
	BACnetChoiceElement<58, BACnetProtocolLevelType>,
	BACnetChoiceElement<63, BACnetUnsigned32Type>
	>
{
public:

};

//Propery Value
class BACnetPropertyValue : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetPropertyIdentifierType, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, true>,
	BACnetSequenceElement<2, BACnetAnyType, false>,
	BACnetSequenceElement<3, BACnetUnsignedType, true>
	>
{
public:
	BACnetPropertyValue() = default;
	BACnetPropertyValue(U32 Property, const BACnetValue& Value, U32 ArrayIndex = -1, U32 Priority = -1)
	{
		SetProperty(Property);
		if(ArrayIndex != -1)
		{
			SetArrayIndex(ArrayIndex);
		}
		else
		{
			ClearArrayIndex();
		}
		SetValue(Value);
		if(Priority != -1)
		{
			SetPriority(Priority);
		}
		else
		{
			ClearPriority();
		}
	}

	U32 GetProperty()
	{
		return get<0>().get();
	}

	bool HasIndex()
	{
		return is_present<1>();
	}

	U32 GetIndex()
	{
		return get<1>().get();
	}

	BACnetValue GetPropertyValue()
	{
		return get<2>().get();
	}

	bool HasPriority()
	{
		return is_present<3>();
	}

	U32 GetPriority()
	{
		return get<3>().get();
	}

	void SetProperty(U32 Property)
	{
		get<0>().set(Property);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<1>(true);
		get<1>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<1>(false);
	}

	void SetValue(const BACnetValue& Value)
	{
		get<2>().set(Value);
	}

	void SetPriority(U32 Priority)
	{
		make_present<3>(true);
		get<3>().set(Priority);
	}

	void ClearPriority()
	{
		make_present<3>(false);
	}
};

//Notification Parameters
class BACnetNotificationParameters : public
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetBitStringType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>
	>
	>,
	BACnetChoiceElement<1,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetPropertyStates, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>
	>
	>,
	BACnetChoiceElement<2,
	BACnetSequence<
	BACnetSequenceElement<0,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0, BACnetBitStringType>,
	BACnetChoiceElement<1, BACnetRealValueType>
	>,
	false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>
	>
	>,
	BACnetChoiceElement<3,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetAnyType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetAnyType, false>
	>
	>,
	BACnetChoiceElement<4,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetRealValueType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetRealValueType, false>,
	BACnetSequenceElement<3, BACnetRealValueType, false>
	>
	>,
	BACnetChoiceElement<5,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetRealValueType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetRealValueType, false>,
	BACnetSequenceElement<3, BACnetRealValueType, false>
	>
	>,
	BACnetChoiceElement<6, BACnetSequenceOf<BACnetPropertyValue>>,
	BACnetChoiceElement<8,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetLifeSafetyStateType, false>,
	BACnetSequenceElement<1, BACnetLifeSafetyModeType, false>,
	BACnetSequenceElement<2, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<3, BACnetLifeSafetyOperationType, false>
	>
	>,
	BACnetChoiceElement<9,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, false>,
	BACnetSequenceElement<2,
	BACnetSequenceOf<
	BACnetChoice<NoDefault,
	BACnetChoiceElement<NoTag, BACnetNullType>,
	BACnetChoiceElement<NoTag, BACnetRealValueType>,
	BACnetChoiceElement<NoTag, BACnetUnsignedType>,
	BACnetChoiceElement<NoTag, BACnetBooleanType>,
	BACnetChoiceElement<NoTag, BACnetSignedType>,
	BACnetChoiceElement<NoTag, BACnetDoubleType>,
	BACnetChoiceElement<NoTag, BACnetOctetStringType>,
	BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
	BACnetChoiceElement<NoTag, BACnetBitStringType>,
	BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
	BACnetChoiceElement<NoTag, BACnetDateType>,
	BACnetChoiceElement<NoTag, BACnetTimeType>,
	BACnetChoiceElement<NoTag, BACnetObjectIDType>,
	BACnetChoiceElement<0, BACnetDeviceObjectPropertyValue>
	>
	>,
	false>
	>
	>,
	BACnetChoiceElement<10,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetDeviceObjectPropertyValue, false>,
	BACnetSequenceElement<1, BACnetUnsigned32Type, false>,
	BACnetSequenceElement<2, BACnetUnsigned32Type, false>
	>
	>,
	BACnetChoiceElement<11,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsignedType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, false>
	>
	>,
	BACnetChoiceElement<13,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetAccessEventType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, false>,
	BACnetSequenceElement<3, BACnetTimeStamp, false>,
	BACnetSequenceElement<4, BACnetDeviceObjectReference, false>,
	BACnetSequenceElement<5, BACnetAuthenticationFactorType, true>
	>
	>,
	BACnetChoiceElement<14,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetDoubleType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetDoubleType, false>,
	BACnetSequenceElement<3, BACnetDoubleType, false>
	>
	>,
	BACnetChoiceElement<15,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetSignedType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, false>,
	BACnetSequenceElement<3, BACnetSignedType, false>
	>
	>,
	BACnetChoiceElement<16,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetUnsignedType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetUnsignedType, false>,
	BACnetSequenceElement<3, BACnetUnsignedType, false>
	>
	>,
	BACnetChoiceElement<17,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetCharacterStringType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetCharacterStringType, false>
	>
	>,
	BACnetChoiceElement<18,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetAnyType, true>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>
	>
	>,
	BACnetChoiceElement<19,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetReliabilityType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetSequenceOf<BACnetPropertyValue>, false>
	>
	>,
	BACnetChoiceElement<21,
	BACnetSequence<
	BACnetSequenceElement<0,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<NoTag, BACnetBooleanType>,
	BACnetChoiceElement<NoTag, BACnetUnsignedType>,
	BACnetChoiceElement<NoTag, BACnetSignedType>,
	BACnetChoiceElement<NoTag, BACnetEnumeratedType>,
	BACnetChoiceElement<NoTag, BACnetCharacterStringType>,
	BACnetChoiceElement<NoTag, BACnetOctetStringType>,
	BACnetChoiceElement<NoTag, BACnetDateType>,
	BACnetChoiceElement<NoTag, BACnetTimeType>,
	BACnetChoiceElement<NoTag, BACnetObjectIDType>,
	BACnetChoiceElement<0, BACnetDateTimeType>
	>,
	false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>
	>
	>,
	BACnetChoiceElement<22,
	BACnetSequence<
	BACnetSequenceElement<0, BACnetTimerStateType, false>,
	BACnetSequenceElement<1, BACnetStatusFlagsType, false>,
	BACnetSequenceElement<2, BACnetDateTimeType, false>,
	BACnetSequenceElement<3, BACnetTimerTransitionType, true>,
	BACnetSequenceElement<4, BACnetUnsignedType, true>,
	BACnetSequenceElement<5, BACnetDateTimeType, true>
	>
	>
	>
{
public:

};

//Object Property Reference

//Object Property Value

//Optional Binary PV

//Optional Character String

//Optional Real

//Optional Unsigned

//Port Permission

//Prescale

//Priority Array

//Priority Value

//Process ID Selection

//Property Access Result

//Property Reference
class BACnetPropertyReference : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetPropertyIdentifierType, false>,
	BACnetSequenceElement<1, BACnetUnsignedType, true>
	>
{
public:
	BACnetPropertyReference() = default;
	BACnetPropertyReference(U32 Property, U32 ArrayIndex = -1)
	{
		SetProperty(Property);
		if(ArrayIndex != -1)
		{
			SetArrayIndex(ArrayIndex);
		}
		else
		{
			ClearArrayIndex();
		}
	}

	U32 GetProperty()
	{
		return get<0>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<1>();
	}

	U32 GetArrayIndex()
	{
		if(!HasArrayIndex())
		{
			return (U32)-1;
		}
		return get<1>().get();
	}

	void SetProperty(U32 Property)
	{
		get<0>().set(Property);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<1>(true);
		get<1>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<1>(false);
	}

};

//Recipient
class BACnetRecipient : public
	BACnetChoice<NoDefault,
	BACnetChoiceElement<0, BACnetObjectIDType>,
	BACnetChoiceElement<1, BACnetAddress>
	>
{
public:

};

//Recipient Process
class BACnetRecipientProcess : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetRecipient, false>,
	BACnetSequenceElement<1, BACnetUnsigned32Type, false>
	>
{
public:

};

//Router Entry

//Scale

//Security Key Set

//Setpoint Reference

//Shed Level

//Special Event

//Timer State Change Value

//Time Value
class BACnetTimeValue : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetTimeType, false>,
	BACnetSequenceElement<NoTag, BACnetApplicationAnyType, false>
	>
{

};

//VMAC Entry

//VT Session
class BACnetVTSession : public
	BACnetSequence<
	BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
	BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
	BACnetSequenceElement<NoTag, BACnetAddress, false>
	>
{

};

//forward declaration because BACnet is mean and self-referencing. :(
class BACnetError;

//Read Access Result
class ReadAccessResult : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1,
	BACnetSequenceOf<
	BACnetSequence<
	BACnetSequenceElement<2, BACnetPropertyIdentifierType, false>,
	BACnetSequenceElement<3, BACnetUnsignedType, true>,
	BACnetSequenceElement<NoTag,
	BACnetChoice<NoDefault,
	BACnetChoiceElement<4, BACnetAnyType>,
	BACnetChoiceElement<5, BACnetError>
	>,
	false>
	>
	>,
	true
	>
	>
{
public:

};

//Read Access Specification
class ReadAccessSpecification : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyReference>, false>
	>
{
public:

};

//Write Access Result
class WriteAccessSpecification : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType, false>,
	BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyValue>, false>
	>
{
public:

};
