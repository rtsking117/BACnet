#pragma once

#include "BACnetBasicTypes.inl"
#include "BACnetCommonTypes.inl"

//Property Access Result

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
