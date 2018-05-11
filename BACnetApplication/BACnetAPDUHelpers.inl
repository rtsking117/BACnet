
#include "BACnetAPDU.h"

//=============================================================================================
//								BASIC TYPES
//=============================================================================================

typedef BACnetApplicationValue<ValueType_Null, void> BACnetNullType;
typedef BACnetApplicationValue<ValueType_Boolean, bool> BACnetBooleanType;
typedef BACnetApplicationValue<ValueType_Unsigned, U8> BACnetUnsigned8Type;
typedef BACnetApplicationValue<ValueType_Unsigned, U16> BACnetUnsigned16Type;
typedef BACnetApplicationValue<ValueType_Unsigned, U32> BACnetUnsignedType, BACnetUnsigned32Type;
typedef BACnetApplicationValue<ValueType_Unsigned, U64> BACnetUnsigned64Type;
typedef BACnetApplicationValue<ValueType_Signed, I8> BACnetSigned8Type;
typedef BACnetApplicationValue<ValueType_Signed, I16> BACnetSigned16Type;
typedef BACnetApplicationValue<ValueType_Signed, I32> BACnetSignedType, BACnetSigned32Type;
typedef BACnetApplicationValue<ValueType_Signed, I64> BACnetSigned64Type;
typedef BACnetApplicationValue<ValueType_Real, float> BACnetRealValueType, BACnetFloatType;
typedef BACnetApplicationValue<ValueType_Double, double> BACnetDoubleType;
typedef BACnetApplicationValue<ValueType_OctetString, BACnetByteString> BACnetOctetStringType;
typedef BACnetApplicationValue<ValueType_CharacterString, BACnetString> BACnetCharacterStringType;
typedef BACnetApplicationValue<ValueType_BitString, BACnetBitString> BACnetBitStringType;
typedef BACnetApplicationValue<ValueType_Enumerated, U32> BACnetEnumeratedType;
typedef BACnetApplicationValue<ValueType_Date, U32> BACnetDateType;
typedef BACnetApplicationValue<ValueType_Time, U32> BACnetTimeType;
typedef BACnetApplicationValue<ValueType_ObjectID, BACnetObjectID> BACnetObjectIDType;

//=============================================================================================
//								   TYPEDEFS
//=============================================================================================

typedef BACnetEnumeratedType BACnetAuthenticationFactorDisableType;
typedef BACnetEnumeratedType BACnetAccessCredentialDisableType;
typedef BACnetEnumeratedType BACnetAccessCredentialDisableReasonType;
typedef BACnetEnumeratedType BACnetAccessEventType;
typedef BACnetEnumeratedType BACnetAccessPassbackModeType;
typedef BACnetUnsignedType BACnetAccessThreatLevelType;
typedef BACnetEnumeratedType BACnetAccessUserTypeType;
typedef BACnetEnumeratedType BACnetAccessZoneOccupancyStateType;
typedef BACnetEnumeratedType BACnetActionType;
typedef BACnetEnumeratedType BACnetAuthenticationFactorType;
typedef BACnetEnumeratedType BACnetAuthenticationStatusType;
typedef BACnetEnumeratedType BACnetAuthorizationExemptionType;
typedef BACnetEnumeratedType BACnetAuthorizationModeType;
typedef BACnetEnumeratedType BACnetBackupStateType;
typedef BACnetEnumeratedType BACnetBinaryLightingPVType;
typedef BACnetEnumeratedType BACnetBinaryPVType;
typedef BACnetBitStringType BACnetDaysOfWeekType;
typedef BACnetEnumeratedType BACnetDeviceStatusType;
typedef BACnetEnumeratedType BACnetDoorAlarmStateType;
typedef BACnetEnumeratedType BACnetDoorSecuredStatusType;
typedef BACnetEnumeratedType BACnetDoorStatusType;
typedef BACnetEnumeratedType BACnetDoorValueType;
typedef BACnetEnumeratedType BACnetEngineeringUnitsType;
typedef BACnetEnumeratedType BACnetEscalatorFaultType;
typedef BACnetEnumeratedType BACnetEscalatorModeType;
typedef BACnetEnumeratedType BACnetEscalatorOperationDirectionType;
typedef BACnetEnumeratedType BACnetEventStateType;
typedef BACnetBitStringType BACnetEventTransitionBits;
typedef BACnetEnumeratedType BACnetEventTypeType;
typedef BACnetEnumeratedType BACnetFaultTypeType;
typedef BACnetEnumeratedType BACnetFileAccessMethodType;
typedef BACnetEnumeratedType BACnetIPModeType;
typedef BACnetEnumeratedType BACnetLifeSafetyModeType;
typedef BACnetEnumeratedType BACnetLifeSafetyOperationType;
typedef BACnetEnumeratedType BACnetLifeSafetyStateType;
typedef BACnetEnumeratedType BACnetLiftCarDirectionType;
typedef BACnetEnumeratedType BACnetLiftCarDoorCommandType;
typedef BACnetEnumeratedType BACnetLiftCarDriveStatusType;
typedef BACnetEnumeratedType BACnetLiftCarModeType;
typedef BACnetEnumeratedType BACnetLiftFaultType;
typedef BACnetEnumeratedType BACnetLiftGroupModeType;
typedef BACnetEnumeratedType BACnetLightingInProgressType;
typedef BACnetEnumeratedType BACnetLightingOperationType;
typedef BACnetEnumeratedType BACnetLightingTransitionType;
typedef BACnetBitStringType BACnetLimitEnableType;
typedef BACnetEnumeratedType BACnetLockStatusType;
typedef BACnetEnumeratedType BACnetLoggingTypeType;
typedef BACnetBitStringType BACnetLogStatusType;
typedef BACnetEnumeratedType BACnetMaintenanceType;
typedef BACnetEnumeratedType BACnetNetworkNumberQualityType;
typedef BACnetEnumeratedType BACnetNetworkPortCommandType;
typedef BACnetEnumeratedType BACnetNetworkTypeType;
typedef BACnetEnumeratedType BACnetNodeTypeType;
typedef BACnetEnumeratedType BACnetNotifyTypeType;
typedef BACnetEnumeratedType BACnetObjectTypeType;
typedef BACnetBitStringType BACnetObjectTypesSupportedType;
typedef BACnetEnumeratedType BACnetPolarityType;
typedef BACnetEnumeratedType BACnetProgramErrorType;
typedef BACnetEnumeratedType BACnetProgramRequestType;
typedef BACnetEnumeratedType BACnetProgramStateType;
typedef BACnetEnumeratedType BACnetPropertyIdentifierType;
typedef BACnetEnumeratedType BACnetProtocolLevelType;
typedef BACnetEnumeratedType BACnetRelationshipType;
typedef BACnetEnumeratedType BACnetReliabilityType;
typedef BACnetEnumeratedType BACnetRestartReasonType;
typedef BACnetBitStringType BACnetResultFlagsType;
typedef BACnetEnumeratedType BACnetSecurityLevelType;
typedef BACnetEnumeratedType BACnetSecurityPolicyType;
typedef BACnetEnumeratedType BACnetSegmentationType;
typedef BACnetBitStringType BACnetServicesSupportedType;
typedef BACnetEnumeratedType BACnetShedStateType;
typedef BACnetEnumeratedType BACnetSilencedStateType;
typedef BACnetBitStringType BACnetStatusFlagsType;
typedef BACnetEnumeratedType BACnetTimerStateType;
typedef BACnetEnumeratedType BACnetTimerTransitionType;
typedef BACnetEnumeratedType BACnetVTClassType;
typedef BACnetOctetStringType BACnetWeekNDayType;
typedef BACnetEnumeratedType BACnetWriteStatusType;


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

//=============================================================================================
//							CONFIRMED ALARM AND EVENT SERVICES
//=============================================================================================

//Acknowledge Alarm
class AcknowledgeAlarmRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetEnumeratedType, false>,
		BACnetSequenceElement<3, BACnetTimeStamp, false>,
		BACnetSequenceElement<4, BACnetCharacterStringType, false>
	>
{
public:

};

//Confirmed COV Notification
class ConfirmedCOVNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetObjectIDType, false>,
		BACnetSequenceElement<3, BACnetUnsignedType, false>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetPropertyValue>, false>
	>
{
public:

};

//Confirmed COV Notification Multiple
class ConfirmedCOVNotificationMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, false>,
		BACnetSequenceElement<3, BACnetDateTimeType, true>,
		BACnetSequenceElement<4,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType, false>,
					BACnetSequenceElement<1, 
						BACnetSequenceOf<
							BACnetSequence<
								BACnetSequenceElement<0, BACnetEnumeratedType, false>,
								BACnetSequenceElement<1, BACnetUnsignedType, true>,
								BACnetSequenceElement<2, BACnetAnyType, false>,
								BACnetSequenceElement<3, BACnetTimeType, true>
							>
						>, false
					>
				>
			>, false
		>
	>
{
public:

};

//Confirmed Event Notification
class ConfirmedEventNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetObjectIDType, false>,
		BACnetSequenceElement<3, BACnetTimeStamp, false>,
		BACnetSequenceElement<4, BACnetUnsignedType, false>,
		BACnetSequenceElement<5, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<6, BACnetEnumeratedType, false>,
		BACnetSequenceElement<7, BACnetCharacterStringType, true>,
		BACnetSequenceElement<8, BACnetEnumeratedType, false>,
		BACnetSequenceElement<9, BACnetBooleanType, true>,
		BACnetSequenceElement<10, BACnetEnumeratedType, true>,
		BACnetSequenceElement<11, BACnetEnumeratedType, false>,
		BACnetSequenceElement<12, BACnetNotificationParameters, true>
	>
{
public:

};

//Get Alarm Summary Ack
class GetAlarmSummaryResponse : public
	BACnetSequenceOf<
		BACnetSequence<
			BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
			BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
			BACnetSequenceElement<NoTag, BACnetBitStringType, false>
		>
	>
{
public:

};

//Get Enrollment Summary
class GetEnrollmentSummaryRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType, false>,
		BACnetSequenceElement<1, BACnetRecipientProcess, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType, true>,
		BACnetSequenceElement<3, BACnetEnumeratedType, true>,
		BACnetSequenceElement<4,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsigned8Type, false>,
				BACnetSequenceElement<1, BACnetUnsigned8Type, false>
			>,
		true>,
		BACnetSequenceElement<5, BACnetUnsignedType, true>
	>
{
public:

};

//Get Enrollement Summary Ack
class GetEnrollmentSummaryResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType, true>
	>
{
public:

};

//Get Event Information
class GetEventInformationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, true>
	>
{
public:

};

//Get Event Information Ack
class GetEventInformationResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectID, false>,
					BACnetSequenceElement<1, BACnetEnumeratedType, false>,
					BACnetSequenceElement<2, BACnetBitStringType, false>,
					BACnetSequenceElement<3, BACnetSequenceOf<BACnetTimeStamp>, false>,
					BACnetSequenceElement<4, BACnetEnumeratedType, false>,
					BACnetSequenceElement<5, BACnetBitStringType, false>,
					BACnetSequenceElement<6, BACnetSequenceOf<BACnetUnsignedType>, false>
				>
			>, 
		false>,
		BACnetSequenceElement<1, BACnetBooleanType, false>
	>
{
public:

};

//Life Safety Operation
class LifeSafetyOperationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetCharacterStringType, false>,
		BACnetSequenceElement<2, BACnetEnumeratedType, false>,
		BACnetSequenceElement<3, BACnetObjectIDType, true>
	>
{

};

//Subscribe COV
class SubscribeCOVRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetBooleanType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>
	>
{
public:

};

//Subscribe COV Property
class SubscribeCOVPropertyRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetBooleanType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetPropertyReference, false>,
		BACnetSequenceElement<5, BACnetRealValueType, true>
	>
{
public:

};

//Subscribe COV Property Multiple
class SubscribeCOVPropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetBooleanType, true>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType, false>,
					BACnetSequenceElement<1, 
						BACnetSequenceOf<
							BACnetSequence<
								BACnetSequenceElement<0, BACnetPropertyReference, false>,
								BACnetSequenceElement<1, BACnetRealValueType, true>,
								BACnetSequenceElement<2, BACnetBooleanType, false>
							>
						>,
					false>
				>
			>,
		false>
	>
{
public:

};

//=============================================================================================
//								FILE SERVICES
//=============================================================================================

//Read File
class ReadFileRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, 
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>
						>
					>,
					BACnetChoiceElement<1, 
						BACnetSequence<BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>
						>
					>
				>, 
			false>
		>
{
public:

	BACnetObjectID GetObject()
	{
		return get<0>().get();
	}

	bool IsStreamBased()
	{
		return get<1>().is_selected(0);
	}

	bool IsRecordBased()
	{
		return get<1>().is_selected(1);
	}

	I32 GetByteOffset()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<0>().get();
	}

	U32 GetByteCount()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<1>().get();
	}

	I32 GetStartingRecord()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<0>().get();
	}

	U32 GetRecordCount()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<1>().get();
	}

	void SetObject(BACnetObjectID Object)
	{
		get<0>().set(Object);
	}

	void SetOffsetAndSize(I32 ByteOffset, U32 ByteSize)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().get<0>().set(ByteOffset);
		get<1>().get<0>().get<1>().set(ByteSize);
	}

	void SetRecordAndCount(I32 StartingRecord, U32 RecordCount)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().get<0>().set(StartingRecord);
		get<1>().get<1>().get<1>().set(RecordCount);
	}
};

//Read File Ack
class ReadFileResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetBooleanType, false>,
		BACnetSequenceElement<NoTag, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, 
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetOctetStringType, false>
					>
				>,
				BACnetChoiceElement<1, 
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
						BACnetSequenceElement<NoTag, 
							BACnetSequenceOf<BACnetOctetStringType>, false
						>
					>
				>
			>, false
		>
	>
{

public:
	
	bool IsValid()
	{
		if(IsRecordBased())
		{
			if(GetRecordCount() != GetRecordData().size())
			{
				return false;
			}
		}
		return true;
	}

	bool IsEndOfFile()
	{
		return get<0>().get();
	}

	bool IsStreamBased()
	{
		return get<1>().is_selected(0);
	}

	bool IsRecordBased()
	{
		return get<1>().is_selected(1);
	}

	I32 GetStartPosition()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<0>().get();
	}

	BACnetByteString GetFileData()
	{
		if(!IsStreamBased())
		{
			return BACnetByteString(nullptr, 0);
		}
		return get<1>().get<0>().get<1>().get();
	}

	I32 GetStartRecord()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<0>().get();
	}

	U32 GetRecordCount()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<1>().get();
	}

	std::vector<BACnetByteString> GetRecordData()
	{
		if(!IsRecordBased())
		{
			return {};
		}
		std::vector<BACnetByteString> ret;
		auto v = get<1>().get<1>().get<2>().get_list();
		for each(auto i in v)
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	void SetEndOfFile()
	{
		get<0>().set(true);
	}

	void ClearEndOfFile()
	{
		get<0>().set(false);
	}

	void SetStreamOffsetAndData(I32 Offset, BACnetByteString Data)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().get<0>().set(Offset);
		get<1>().get<0>().get<1>().set(Data);
	}

	void SetStartRecordAndData(I32 StartRecord, std::vector<BACnetByteString> Data)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().get<0>().set(StartRecord);
		get<1>().get<1>().get<1>().set((U32)Data.size());
		for(U32 i = 0; i < (U32)Data.size(); ++i)
		{
			get<1>().get<1>().get<2>().get(i).set(Data.at(i));
		}
	}
};

//Write File
class WriteFileRequest : public
	BACnetSequence <
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetOctetStringType, false>
					>
				>,
				BACnetChoiceElement<1,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
						BACnetSequenceElement<NoTag,
							BACnetSequenceOf<BACnetOctetStringType>,
						false>
					>
				>
			>, false
		>
	>
{

public:

	bool IsValid()
	{
		if (IsRecordBased())
		{
			if (GetRecordCount() != GetRecordData().size())
			{
				return false;
			}
		}
		return true;
	}

	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	bool IsStreamBased()
	{
		return get<1>().is_selected(0);
	}

	bool IsRecordBased()
	{
		return get<1>().is_selected(1);
	}

	I32 GetStartPosition()
	{
		if (!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<0>().get();
	}

	BACnetByteString GetFileData()
	{
		if (!IsStreamBased())
		{
			return BACnetByteString(nullptr, 0);
		}
		return get<1>().get<0>().get<1>().get();
	}

	I32 GetStartRecord()
	{
		if (!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<0>().get();
	}

	U32 GetRecordCount()
	{
		if (!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<1>().get();
	}

	std::vector<BACnetByteString> GetRecordData()
	{
		if (!IsRecordBased())
		{
			return {};
		}
		std::vector<BACnetByteString> ret;
		auto v = get<1>().get<1>().get<2>().get_list();
		for each(auto i in v)
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetStreamOffsetAndData(I32 Offset, BACnetByteString Data)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().get<0>().set(Offset);
		get<1>().get<0>().get<1>().set(Data);
	}

	void SetStartRecordAndData(I32 StartRecord, std::vector<BACnetByteString> Data)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().get<0>().set(StartRecord);
		get<1>().get<1>().get<1>().set((U32)Data.size());
		for (U32 i = 0; i < (U32)Data.size(); ++i)
		{
			get<1>().get<1>().get<2>().get(i).set(Data.at(i));
		}
	}

};

//Write File Ack
class WriteFileResponse : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetSignedType>,
		BACnetChoiceElement<1, BACnetSignedType>
	>
{
public:

	bool IsStreamBased()
	{
		return is_selected(0);
	}
	
	bool IsRecordBased()
	{
		return is_selected(1);
	}

	I32 GetNewStreamPosition()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<0>().get();
	}

	I32 GetNewRecordNumber()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get();
	}

	void SetNewStreamPosition(I32 NewPosition)
	{
		make_selected(0);
		get<0>().set(NewPosition);
	}

	void SetNewRecordNumber(I32 NewRecordNumber)
	{
		make_selected(1);
		get<1>().set(NewRecordNumber);
	}
};

//=============================================================================================
//							CONFIRMED OBJECT ACCESS SERVICES
//=============================================================================================

//Add List Element
class AddListElementRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType, false>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetPropertyID()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if (!HasArrayIndex())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	BACnetValue GetElementValue()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetPropertyID(U32 PropertyID)
	{
		get<1>().set(PropertyID);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<2>(true);
		get<2>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetElementValue(const BACnetValue & Value)
	{
		get<3>().set(Value);
	}
};

//Create Object
class CreateObjectRequest : public 
	BACnetSequence<
		BACnetSequenceElement<0, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetEnumeratedType>,
				BACnetChoiceElement<1, BACnetObjectIDType>
			>, false
		>,
		BACnetSequenceElement<1, 
			BACnetSequenceOf<BACnetPropertyValue>
		, true>
	>
{
public:
	bool IsObjectType()
	{
		return get<0>().is_selected(0);
	}

	U32 GetObjectType()
	{
		if(!IsObjectType())
		{
			return 0;
		}
		return get<0>().get<0>().get();
	}

	bool IsObjectID()
	{
		return get<0>().is_selected(1);
	}

	BACnetObjectID GetObjectID()
	{
		if(!IsObjectID())
		{
			return 0;
		}
		return get<0>().get<1>().get();
	}

	bool HasInitialValues()
	{
		return is_present<1>();
	}

	std::vector<BACnetPropertyValue> GetInitialValueList()
	{
		if(!HasInitialValues())
		{
			return {};
		}
		return get<1>().get_list();
	}

	void SetObjectType(U32 ObjectType)
	{
		get<0>().make_selected(0);
		get<0>().get<0>().set(ObjectType);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().make_selected(1);
		get<0>().get<1>().set(ObjectID);
	}

	void SetInitialValueList(std::vector<BACnetPropertyValue> InitialValueList)
	{
		make_present<1>(true);
		get<1>().set_list(InitialValueList);
	}

	void ClearInitialValueList()
	{
		make_present<1>(false);
	}
};

//Create Object Ack
class CreateObjectResponse : public
	BACnetObjectIDType
{
public:

	BACnetObjectID GetObjectID()
	{
		return get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		set(ObjectID);
	}
};

//Delete Object
class DeleteObjectRequest :	public 
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>
	>
{
public:
	BACnetObjectID GetObject()
	{
		return get<0>().get();
	}

	void SetObject(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}
};

//Read Property
class ReadPropertyRequest : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>
	>
{
public:

	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool IsArrayIndexPresent()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if(IsArrayIndexPresent())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 Property)
	{
		get<1>().set(Property);
	}

	void SetArrayIndex(U32 Index)
	{
		make_present<2>(true);
		get<2>().set(Index);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}
};

//Read Property Ack
class ReadPropertyResponse : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType, false>
	>
{
public:
	
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool IsArrayIndexPresent()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if(IsArrayIndexPresent())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	BACnetValue GetPropertyValue()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 Property)
	{
		get<1>().set(Property);
	}

	void SetArrayIndex(U32 Index)
	{
		make_present<2>(true);
		get<2>().set(Index);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetPropertyValue(const BACnetValue& v)
	{
		get<3>().set(v);
	}
};

//Read Property Multiple
class ReadPropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<ReadAccessSpecification>, false>
	>
{
public:

	ReadAccessSpecification GetReadForObject(U32 Index)
	{
		return get<0>().get(Index);
	}

	std::vector<ReadAccessSpecification> GetReads()
	{
		return get<0>().get_list();
	}

	void ClearAllReads ()
	{
		get<0>().clear_list();
	}

	void AddReadForObject(ReadAccessSpecification PropertyRead)
	{
		get<0>().add(PropertyRead);
	}

	void AddReads(std::vector<ReadAccessSpecification> PropertyReads)
	{
		get<0>().add_list(PropertyReads);
	}

	void SetReads(std::vector<ReadAccessSpecification> PropertyReads)
	{
		get<0>().set_list(PropertyReads);
	}
};

//Read Property Multiple Ack
class ReadPropertyMultipleResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<ReadAccessResult>, false>
	>
{
public:
	ReadAccessResult GetReadForObject(U32 Index)
	{
		return get<0>().get(Index);
	}

	std::vector<ReadAccessResult> GetReads()
	{
		return get<0>().get_list();
	}

	void ClearAllReads()
	{
		get<0>().clear_list();
	}

	void AddReadForObject(ReadAccessResult PropertyRead)
	{
		get<0>().add(PropertyRead);
	}

	void AddReads(std::vector<ReadAccessResult> PropertyReads)
	{
		get<0>().add_list(PropertyReads);
	}

	void SetReads(std::vector<ReadAccessResult> PropertyReads)
	{
		get<0>().set_list(PropertyReads);
	}
};

//Read Range
class ReadRangeRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<3,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
						BACnetSequenceElement<NoTag, BACnetSigned16Type, false>
					>
				>,
				BACnetChoiceElement<6,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
						BACnetSequenceElement<NoTag, BACnetSigned16Type, false>
					>
				>,
				BACnetChoiceElement<7,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetDateTimeType, false>,
						BACnetSequenceElement<NoTag, BACnetSigned16Type, false>
					>
				>
			>, true
		>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if(HasArrayIndex())
		{
			return InvalidIndex;
		}
		return get<2>().get();
	}

	bool HasRange()
	{
		return is_present<3>();
	}

	bool IsRangePosition()
	{
		return HasRange() && get<3>().is_selected(0);
	}

	U32 GetReferenceIndex()
	{
		if(!IsRangePosition())
		{
			return 0;
		}
		return get<3>().get<0>().get<0>().get();
	}

	bool IsRangeSequenceNumber()
	{
		return HasRange() && get<3>().is_selected(1);
	}

	U32 GetReferenceSequenceNumber()
	{
		if(!IsRangeSequenceNumber())
		{
			return 0;
		}
		return get<3>().get<1>().get<0>().get();
	}

	bool IsRangeTime()
	{
		return HasRange() && get<3>().is_selected(2);
	}

	BACnetDateTimeType GetReferenceTime()
	{
		if(!IsRangeTime())
		{
			return BACnetDateTimeType();
		}
		return get<3>().get<2>().get<0>();
	}

	I16 GetCount()
	{
		if(IsRangePosition())
		{
			return get<3>().get<0>().get<1>().get();
		}
		else if(IsRangeSequenceNumber())
		{
			return get<3>().get<1>().get<1>().get();
		}
		else if(IsRangeTime())
		{
			return get<3>().get<2>().get<1>().get();
		}
		else
		{
			return 0;
		}
	}
	
	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 PropertyID)
	{
		get<1>().set(PropertyID);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<2>(true);
		get<2>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetPositionRange(U32 StartIndex, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(0);
		get<3>().get<0>().get<0>().set(StartIndex);
		get<3>().get<0>().get<1>().set(Count);
	}

	void SetSequenceNumberRange(U32 StartSequenceNumber, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(1);
		get<3>().get<1>().get<0>().set(StartSequenceNumber);
		get<3>().get<1>().get<1>().set(Count);
	}

	void SetTimeRange(BACnetDateTimeType StartTime, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(2);
		get<3>().get<2>().get<0>() = StartTime;
		get<3>().get<2>().get<1>().set(Count);
	}

	void ClearRange()
	{
		make_present<3>(false);
	}
};

//Read Range Ack
class ReadRangeResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetBitStringType, false>,
		BACnetSequenceElement<4, BACnetUnsignedType, false>,
		BACnetSequenceElement<5,
			BACnetSequenceOf<BACnetAnyType>,
		false>,
		BACnetSequenceElement<6, BACnetUnsigned32Type, true>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if(!HasArrayIndex())
		{
			return InvalidIndex;
		}
		return get<2>().get();
	}

	BACnetBitString GetResultFlags()
	{
		return get<3>().get();
	}

	U32 GetItemCount()
	{
		return get<4>().get();
	}

	std::vector<BACnetValue> GetValues()
	{
		std::vector<BACnetValue> ret;
		for each(auto i in get<5>().get_list())
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	bool HasFirstSequenceNumber()
	{
		return is_present<6>();
	}

	U32 GetFirstSequenceNumber()
	{
		if(!HasFirstSequenceNumber())
		{
			return 0;
		}
		return get<6>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 PropertyID)
	{
		get<1>().set(PropertyID);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<2>(true);
		get<2>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetResultFlags(BACnetBitString ResultFlags)
	{
		get<3>().set(ResultFlags);
	}

	void SetItems(std::vector<BACnetValue> Items)
	{
		get<4>().set((U32)Items.size());
		get<5>().clear_list();
		for each(auto i in Items)
		{
			get<5>().add(BACnetAnyType(i));
		}
	}

	void AddItem(BACnetValue Item)
	{
		get<4>().set(get<4>().get()+1);
		get<5>().add(BACnetAnyType(Item));
	}

	void AddItems(std::vector<BACnetValue> Items)
	{
		get<4>().set(get<4>().get() + (U32)Items.size());
		for each(auto i in Items)
		{
			get<5>().add(BACnetAnyType(i));
		}
	}

	void ClearItems()
	{
		get<4>().set(0);
		get<5>().clear_list();
	}

	void SetFirstSequenceNumber(U32 FirstSequenceNumber)
	{
		make_present<6>(true);
		get<6>().set(FirstSequenceNumber);
	}

	void ClearFirstSequenceNumber()
	{
		make_present<6>(false);
	}
};

//Remove List Element
class RemoveListElementRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType, false>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetPropertyID()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if(!HasArrayIndex())
		{
			return (U32)-1;
		}
		return get<2>().get();
	}

	BACnetValue GetElementValue()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetPropertyID(U32 PropertyID)
	{
		get<1>().set(PropertyID);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<2>(true);
		get<2>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetElementValue(const BACnetValue & Value)
	{
		get<3>().set(Value);
	}
};

//Write Property
class WritePropertyRequest : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType, false>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>
	>
{
public:
	BACnetObjectID GetObject()
	{
		return get<0>().get();
	}
	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if(HasArrayIndex())
		{
			return get<2>().get();
		}
		return (U32)-1;
	}

	BACnetValue GetPropertyValue()
	{
		return get<3>().get();
	}

	bool HasPriority()
	{
		return is_present<4>();
	}

	U32 GetPriority()
	{
		if(HasPriority())
		{
			return get<4>().get();
		}
		return (U32)-1;
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 Property)
	{
		get<1>().set(Property);
	}

	void SetArrayIndex(U32 Index)
	{
		make_present<2>(true);
		get<2>().set(Index);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetPropertyValue(const BACnetValue& v)
	{
		get<3>().set(v);
	}

	void SetPriority(U32 Priority)
	{
		make_present<4>(true);
		get<4>().set(Priority);
	}

	void ClearPriority()
	{
		make_present<4>(false);
	}

};

//Write Property Multiple
class WritePropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetSequenceOf<WriteAccessSpecification>, false>
	>
{
public:

	WriteAccessSpecification GetWriteForObject(U32 Index)
	{
		return get<0>().get(Index);
	}

	std::vector<WriteAccessSpecification> GetWrites()
	{
		return get<0>().get_list();
	}

	void ClearAllWrites()
	{
		get<0>().clear_list();
	}

	void AddWriteForObject(WriteAccessSpecification PropertyWrite)
	{
		get<0>().add(PropertyWrite);
	}

	void AddWrites(std::vector<WriteAccessSpecification> PropertyWrites)
	{
		get<0>().add_list(PropertyWrites);
	}

	void SetWrites(std::vector<WriteAccessSpecification> PropertyWrites)
	{
		get<0>().set_list(PropertyWrites);
	}
};

//=============================================================================================
//						CONFIRMED REMOTE DEVICE MANAGEMENT SERVICES
//=============================================================================================

//Confirmed Private Transfer
class ConfirmedPrivateTransferRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, false>,
		BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:
	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	bool HasServiceParameters()
	{
		return is_present<2>();
	}

	BACnetValue GetServiceParameters()
	{
		if(HasServiceParameters())
		{
			return BACnetValue();
		}
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetServiceParameters(BACnetValue EncodedServiceParameters)
	{
		make_present<2>(true);
		get<2>().set(EncodedServiceParameters);
	}
};

//Confirmed Private Transfer Ack
class ConfirmedPrivateTransferResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, false>,
		BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:
	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	bool HasResultParameters()
	{
		return is_present<2>();
	}

	BACnetValue GetResultParameters()
	{
		if(HasResultParameters())
		{
			return BACnetValue();
		}
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetResultParameters(BACnetValue EncodedServiceParameters)
	{
		make_present<2>(true);
		get<2>().set(EncodedServiceParameters);
	}
};

//Confirmed Text Message
class ConfirmedTextMessageRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetUnsignedType>,
				BACnetChoiceElement<1, BACnetCharacterStringType>
			>
		, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType, false>,
		BACnetSequenceElement<3, BACnetCharacterStringType, false>
	>
{
public:
	BACnetObjectID GetMessageSource()
	{
		return get<0>().get();
	}

	bool HasMessageClass()
	{
		return is_present<1>();
	}

	bool IsMessageClassNumeric()
	{
		if (!HasMessageClass())
		{
			return false;
		}
		return get<1>().is_selected(0);
	}

	bool IsMessageClassString()
	{
		if (!HasMessageClass())
		{
			return false;
		}
		return get<1>().is_selected(1);
	}

	U32 GetMessageClassID()
	{
		if (!IsMessageClassNumeric())
		{
			return 0;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetMessageClassString()
	{
		if (!IsMessageClassString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	U32 GetMessagePriority()
	{
		return get<2>().get();
	}

	BACnetString GetMessageText()
	{
		return get<3>().get();
	}

	void SetMessageSource(BACnetObjectID SourceObject)
	{
		get<0>().set(SourceObject);
	}

	void SetMessageClassID(U32 MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(0);
		get<1>().get<0>().set(MessageClass);
	}

	void SetMessageClassString(BACnetString MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(1);
		get<1>().get<1>().set(MessageClass);
	}

	void ClearMessageClass()
	{
		make_present<1>(false);
	}

	void SetMessagePriority(U32 Priority)
	{
		get<2>().set(Priority);
	}

	void SetMessageText(BACnetString MessageText)
	{
		get<3>().set(MessageText);
	}
};

//Device Communication Control
class DeviceCommunicationControlRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type, true>,
		BACnetSequenceElement<1, BACnetEnumeratedType, false>,
		BACnetSequenceElement<2, BACnetCharacterStringType, true>
	>
{
public:
	bool HasTimeDuration()
	{
		return is_present<0>();
	}

	U16 GetTimeDuration()
	{
		if(!HasTimeDuration())
		{
			return 0;
		}
		return get<0>().get();
	}

	U32 GetEnableState()
	{
		return get<1>().get();
	}

	bool HasPassword()
	{
		return is_present<2>();
	}

	BACnetString GetPassword()
	{
		if(!HasPassword())
		{
			return BACnetString("");
		}
		return get<2>().get();
	}

	void SetTimeDuration(U16 TimeDuration)
	{
		make_present<0>(true);
		get<0>().set(TimeDuration);
	}

	void ClearTimeDuration()
	{
		make_present<0>(false);
	}

	void SetEnableState(U32 EnableState)
	{
		get<1>().set(EnableState);
	}

	void SetPassword(BACnetString Password)
	{
		make_present<2>(true);
		get<2>().set(Password);
	}

	void ClearPassword()
	{
		make_present<2>(false);
	}
};

//Reinitialize Device
class ReinitializeDeviceRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetEnumeratedType, false>,
		BACnetSequenceElement<1, BACnetCharacterStringType, true>
	>
{
public:
	U32 GetReinitializationState()
	{
		return get<0>().get();
	}

	bool HasPassword()
	{
		return is_present<1>();
	}

	BACnetString GetPassword()
	{
		if(!HasPassword())
		{
			return BACnetString("");
		}
		return get<1>().get();
	}

	void SetReinitalizationState(U32 ReinitializationState)
	{
		get<0>().set(ReinitializationState);
	}

	void SetPassword(BACnetString Password)
	{
		make_present<1>(true);
		get<1>().set(Password);
	}

	void ClearPassword()
	{
		make_present<1>(false);
	}
};

//=============================================================================================
//							CONFIRMED VIRTUAL TERMINAL SERVICES
//=============================================================================================

//VT Open
class VTOpenRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>
	>
{
public:
	
	U32 GetVTClass()
	{
		return get<0>().get();
	}

	U8 GetLocalSessionID()
	{
		return get<1>().get();
	}

	void SetVTClass(U32 VTClass)
	{
		get<0>().set(VTClass);
	}

	void SetLocalSessionID(U8 LocalSessionID)
	{
		get<1>().set(LocalSessionID);
	}
};

//VT Open Ack
class VTOpenResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>
	>
{
public:

	U8 GetRemoteSessionID()
	{
		return get<0>().get();
	}

	void SetRemoteSessionID(U8 RemoteSessionID)
	{
		get<0>().set(RemoteSessionID);
	}
};

//VT Close
class VTCloseRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, 
			BACnetSequenceOf<BACnetUnsigned8Type>
		, false>
	>
{
public:
	
	std::vector<U8> GetRemoteSessionIDs()
	{
		std::vector<U8> ret;
		for each(auto i in get<0>().get_list())
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	void SetRemoteSessionIDs(std::vector<U8> RemoteSessionIDs)
	{
		get<0>().clear_list();
		for each(U8 i in RemoteSessionIDs)
		{
			get<0>().add(BACnetUnsigned8Type(i));
		}
	}

	void AddRemoteSessionID(U8 RemoteSessionID)
	{
		get<0>().add(BACnetUnsigned8Type(RemoteSessionID));
	}

	void AddRemoteSessionIDs(std::vector<U8> RemoteSessionIDs)
	{
		for each(U8 i in RemoteSessionIDs)
		{
			get<0>().add(BACnetUnsigned8Type(i));
		}
	}

	void ClearRemoteSessionIDs()
	{
		get<0>().clear_list();
	}
};

//VT Data
class VTDataRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<NoTag, BACnetOctetStringType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType, false>
	>
{
public:
	U8 GetSessionID()
	{
		return get<0>().get();
	}

	BACnetByteString GetVTData()
	{
		return get<1>().get();
	}

	U32 GetDataFlag()
	{
		return get<2>().get();
	}

	void SetSessionID(U8 SessionID)
	{
		get<0>().set(SessionID);
	}

	void SetVTData(BACnetByteString VTData)
	{
		get<1>().set(VTData);
	}

	void SetDataFlag(bool DataFlag)
	{
		get<2>().set(DataFlag ? 1 : 0);
	}
};

//VT Data Ack
class VTDataResponse : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetBooleanType, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>
	>
{
public:
	bool IsValid()
	{
		if (WasAllDataAccepted())
		{
			return !HasAcceptedOctetCount();
		}
		return HasAcceptedOctetCount();
	}

	bool WasAllDataAccepted()
	{
		return get<0>().get();
	}

	bool HasAcceptedOctetCount()
	{
		return is_present<1>();
	}

	U32 GetAcceptedOctetCount()
	{
		if (!HasAcceptedOctetCount())
		{
			return (U32)-1;
		}
		return get<1>().get();
	}

	void SetAllDataAcceptedFlag(bool WasAllDataAccepted)
	{
		get<0>().set(WasAllDataAccepted);
		if (WasAllDataAccepted)
		{
			make_present<1>(false);
		}
	}

	void SetAcceptedOctetCount(U32 AcceptedOctetCount)
	{
		get<0>().set(false);
		make_present<1>(true);
		get<1>().set(AcceptedOctetCount);
	}
};

//=============================================================================================
//							UNCONFIRMED ALARM AND EVENT SERVICES
//=============================================================================================



//=============================================================================================
//							UNCONFIRMED OBJECT ACCESS SERVICES
//=============================================================================================

//Write Group
class WriteGroupRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, false>,
		BACnetSequenceElement<2,
			BACnetSequenceOf<BACnetGroupChannelValue>,
			false>,
		BACnetSequenceElement<3, BACnetBooleanType, true>
	>
{
public:
	U32 GetGroupNumber()
	{
		return get<0>().get();
	}

	U32 GetWritePriority()
	{
		return get<1>().get();
	}

	std::vector<BACnetGroupChannelValue> GetChangeList()
	{
		return get<2>().get_list();
	}

	bool HasInhibitDelay()
	{
		return is_present<3>();
	}

	bool IsInhibitDelaySet()
	{
		if(!HasInhibitDelay())
		{
			return false;
		}
		return get<3>().get();
	}
};

//=============================================================================================
//						UNCONFIRMED REMOTE DEVICE MANAGEMENT SERVICES
//=============================================================================================

//I Am
class IAmRequest : public 
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
		BACnetSequenceElement<NoTag, BACnetUnsigned16Type, false>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetMaxAPDUSize()
	{
		return get<1>().get();
	}

	BACnetSegmentation GetSegmentationSettings()
	{
		return (BACnetSegmentation)get<2>().get();
	}

	U16 GetVendorID()
	{
		return get<3>().get();
	}

	void SetObjectID(BACnetObjectID ID)
	{
		get<0>().set(ID);
	}

	void SetMaxAPDUSize(U32 APDUSize)
	{
		get<1>().set(APDUSize);
	}

	void SetSegmentationSettings(BACnetSegmentation segmentation)
	{
		get<2>().set((U32)segmentation);
	}

	void SetVendorID(U16 VendorID)
	{
		get<3>().set(VendorID);
	}
};

//I Have
class IHaveRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag, BACnetCharacterStringType, false>
	>
{
public:

	BACnetObjectID GetDeviceID()
	{
		return get<0>().get();
	}

	BACnetObjectID GetObjectID()
	{
		return get<1>().get();
	}

	BACnetString GetCharString()
	{
		return get<2>().get();
	}

	void SetDeviceID(BACnetObjectID DeviceID)
	{
		get<0>().set(DeviceID);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<1>().set(ObjectID);
	}

	void SetCharStringID(BACnetString CharString)
	{
		get<2>().set(CharString);
	}
};

//Unconfirmed Private Transfer
class UnconfirmedPrivateTransferRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type, false>,
		BACnetSequenceElement<1, BACnetUnsignedType, false>,
		BACnetSequenceElement<2, BACnetAnyType, true>
	>
{
public:
	
	U16 GetVendorID()
	{
		return get<0>().get();
	}

	U32 GetServiceNumber()
	{
		return get<1>().get();
	}

	BACnetValue GetServiceParameters()
	{
		return get<2>().get();
	}

	void SetVendorID(U16 VendorID)
	{
		get<0>().set(VendorID);
	}

	void SetServiceNumber(U32 ServiceNumber)
	{
		get<1>().set(ServiceNumber);
	}

	void SetServiceParameters(const BACnetValue& ServiceParams)
	{
		get<2>().set(ServiceParams);
	}

};

//Unconfirmed Text Message
class UnconfirmedTextMessageRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, false>,
		BACnetSequenceElement<1, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetUnsignedType>,
				BACnetChoiceElement<1, BACnetCharacterStringType>
			>, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType, false>,
		BACnetSequenceElement<3, BACnetCharacterStringType, false>
	>
{
public:

	bool IsValid()
	{
		return !is_present<1>() || get<1>().IsValid();
	}

	BACnetObjectID GetSourceDevice()
	{
		return get<0>().get();
	}

	bool HasMessageClass()
	{
		return is_present<1>();
	}

	bool IsMessageClassNumeric()
	{
		return HasMessageClass() && get<1>().is_selected(0);
	}

	bool IsMessageClassString()
	{
		return HasMessageClass() && get<1>().is_selected(1);
	}

	U32 GetMessageClassID()
	{
		if(!IsMessageClassNumeric())
		{
			return 0;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetMessageClassString()
	{
		if(!IsMessageClassString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	U32 GetMessagePriority()
	{
		return get<2>().get();
	}

	BACnetString GetMessageText()
	{
		return get<3>().get();
	}

	void SetSourceDevice(BACnetObjectID SourceDevice)
	{
		get<0>().set(SourceDevice);
	}

	void SetMessageClassID(U32 MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(0);
		get<1>().get<0>().set(MessageClass);
	}

	void SetMessageClassString(BACnetString MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(1);
		get<1>().get<1>().set(MessageClass);
	}

	void ClearMessageClass()
	{
		make_present<1>(false);
	}

	void SetMessagePriority(U32 Priority)
	{
		get<2>().set(Priority);
	}

	void SetMessageText(const BACnetString& MessageText)
	{
		get<3>().set(MessageText);
	}
};

//Time Synchronization
class TimeSynchronizationRequest : public
	BACnetSequence<BACnetSequenceElement<NoTag, BACnetDateTimeType, false>>
{
	U32 GetDate()
	{
		return get<0>().GetDate();
	}

	U32 GetTime()
	{
		return get<0>().GetTime();
	}

	void SetDate(U32 Date)
	{
		get<0>().SetDate(Date);
	}

	void SetTime(U32 Time)
	{
		get<0>().SetTime(Time);
	}
};

//UTC Time Synchronization
class UTCTimeSynchronizationRequest : public
	BACnetSequence<BACnetSequenceElement<NoTag, BACnetDateTimeType, false>>
{
	U32 GetDate()
	{
		return get<0>().GetDate();
	}

	U32 GetTime()
	{
		return get<0>().GetTime();
	}

	void SetDate(U32 Date)
	{
		get<0>().SetDate(Date);
	}

	void SetTime(U32 Time)
	{
		get<0>().SetTime(Time);
	}
};

//Who Has
class WhoHasRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType, false>,
				BACnetSequenceElement<1, BACnetUnsignedType, false>
			>, true
		>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<2, BACnetObjectIDType>,
				BACnetChoiceElement<3, BACnetCharacterStringType>
			>, false
		>
	>
{
public:
	
	bool HasLimits()
	{
		return is_present<0>();
	}

	U32 GetLowLimit()
	{
		if(!HasLimits())
		{
			return 0;
		}
		return get<0>().get<0>().get();
	}

	U32 GetHighLimit()
	{
		if(!HasLimits())
		{
			return 4194303;
		}
		return get<0>().get<1>().get();
	}

	bool IsObjectID()
	{
		return get<1>().is_selected(0);
	}

	bool IsObjectString()
	{
		return get<1>().is_selected(1);
	}

	BACnetObjectID GetObjectID()
	{
		if(!IsObjectID())
		{
			return InvalidObjectID;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetObjectString()
	{
		if(!IsObjectString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	void SetLimits(U32 LowLimit, U32 HighLimit)
	{
		make_present<0>(true);
		get<0>().get<0>().set(LowLimit);
		get<0>().get<1>().set(HighLimit);
	}

	void ClearLimits()
	{
		make_present<0>(false);
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().set(ObjectID);
	}

	void SetObjectString(BACnetString ObjectString)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().set(ObjectString);
	}
};


//Who Is
class WhoIsRequest : public 
	BACnetSequence<
		BACnetSequenceElement<NoTag,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType, false>,
				BACnetSequenceElement<1, BACnetUnsignedType, false>
			>, true
		>
	>
{
public:

	bool HasLimits()
	{
		return is_present<0>();
	}

	U32 GetLowLimit()
	{
		if(!HasLimits())
		{
			return 0;
		}
		return get<0>().get<0>().get();
	}

	U32 GetHighLimit()
	{
		if(!HasLimits())
		{
			return 4194303;
		}
		return get<0>().get<0>().get();
	}

	void SetLimits(U32 LowLimit = 0, U32 HighLimit = 4194303)
	{
		make_present<0>(true);
		get<0>().get<0>().set(LowLimit);
		get<0>().get<1>().set(HighLimit);
	}

	void RemoveLimits()
	{
		make_present<0>(false);
	}

};

//=============================================================================================
//							ERROR PRODUCTIONS
//=============================================================================================

//Generic Error
class BACnetError :	public 
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>,
		BACnetSequenceElement<NoTag, BACnetEnumeratedType, false>
	>
{
public:
	U16 GetErrorClass()
	{
		return (U16)get<0>().get();
	}

	U16 GetErrorCode()
	{
		return (U16)get<1>().get();
	}

	bool SetError(ErrorClass Class, ErrorCode Code)
	{
		return SetError((U16)Class, (U16)Code);
	}

	bool SetError(U16 Class, U16 Code)
	{
		return get<0>().set(Class) && get<1>().set(Code);
	}
};

//Change List Error


//Create Object Error
class CreateObjectError : public 
	BACnetSequence<
		BACnetSequenceElement<0, BACnetError, false>, 
		BACnetSequenceElement<1, BACnetUnsignedType, false>
	>
{
public:
	CreateObjectError()
	{
		//make the First Failed Element Number 0 on init.
		//compilance with 15.3.1.3.2
		get<1>().set(0);
	}

	U16 GetErrorClass()
	{
		return get<0>().GetErrorClass();
	}

	U16 GetErrorCode()
	{
		return get<0>().GetErrorCode();
	}

	U32 GetLastFailedProperty()
	{
		return get<1>().get();
	}

	template<typename T, typename Q>
	bool SetError(T ErrorClass, Q ErrorCode)
	{
		return get<0>().SetError(ErrorClass, ErrorCode);
	}

	bool SetLastFailedProperty(U32 PropIndex)
	{
		return get<1>().set(PropIndex);
	}


};

