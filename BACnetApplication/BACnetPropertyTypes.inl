#pragma once

#include "BACnetBasicTypes.inl"
#include "BACnetComplexTypes.inl"
#include "BACnetErrorTypes.inl"


//Device Object Property Reference
class BACnetDeviceObjectPropertyReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetObjectIDType, true>
	>
{
public:

};

//Device Object Property Value
class BACnetDeviceObjectPropertyValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetAnyType>
	>
{
public:

};

//Device Object Reference
class BACnetDeviceObjectReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType, true>,
		BACnetSequenceElement<1, BACnetObjectIDType>
	>
{
public:

};

//Group Channel Value
class BACnetGroupChannelValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned16Type>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>,
		BACnetSequenceElement<NoTag, BACnetChannelValue, false>
	>
{
public:

};

//Object Property Reference
class BACnetObjectPropertyReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>
	>
{
public:

};

//Object Property Value
class BACnetObjectPropertyValue : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetAnyType>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>
	>
{
public:

};

//Property Access Result
class BACnetPropertyAccessResult : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetObjectIDType, true>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<4, BACnetAnyType>,
				BACnetChoiceElement<5, BACnetError>
			>, false
		>
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
		BACnetChoiceElement<63, BACnetUnsigned32Type>,
		BACnetChoiceElement<64, BACnetUnsigned32Type>,
		BACnetChoiceElement<65, BACnetUnsigned32Type>,
		BACnetChoiceElement<66, BACnetUnsigned32Type>,
		BACnetChoiceElement<67, BACnetUnsigned32Type>,
		BACnetChoiceElement<68, BACnetUnsigned32Type>,
		BACnetChoiceElement<69, BACnetUnsigned32Type>,
		BACnetChoiceElement<70, BACnetUnsigned32Type>,
		BACnetChoiceElement<71, BACnetUnsigned32Type>,
		BACnetChoiceElement<72, BACnetUnsigned32Type>,
		BACnetChoiceElement<73, BACnetUnsigned32Type>,
		BACnetChoiceElement<73, BACnetUnsigned32Type>,
		BACnetChoiceElement<74, BACnetUnsigned32Type>,
		BACnetChoiceElement<75, BACnetUnsigned32Type>,
		BACnetChoiceElement<76, BACnetUnsigned32Type>,
		BACnetChoiceElement<77, BACnetUnsigned32Type>,
		BACnetChoiceElement<78, BACnetUnsigned32Type>,
		BACnetChoiceElement<79, BACnetUnsigned32Type>,
		BACnetChoiceElement<80, BACnetUnsigned32Type>,
		BACnetChoiceElement<81, BACnetUnsigned32Type>,
		BACnetChoiceElement<82, BACnetUnsigned32Type>,
		BACnetChoiceElement<83, BACnetUnsigned32Type>,
		BACnetChoiceElement<84, BACnetUnsigned32Type>,
		BACnetChoiceElement<85, BACnetUnsigned32Type>,
		BACnetChoiceElement<86, BACnetUnsigned32Type>,
		BACnetChoiceElement<87, BACnetUnsigned32Type>,
		BACnetChoiceElement<88, BACnetUnsigned32Type>,
		BACnetChoiceElement<89, BACnetUnsigned32Type>,
		BACnetChoiceElement<90, BACnetUnsigned32Type>,
		BACnetChoiceElement<91, BACnetUnsigned32Type>,
		BACnetChoiceElement<92, BACnetUnsigned32Type>,
		BACnetChoiceElement<93, BACnetUnsigned32Type>,
		BACnetChoiceElement<94, BACnetUnsigned32Type>,
		BACnetChoiceElement<95, BACnetUnsigned32Type>,
		BACnetChoiceElement<96, BACnetUnsigned32Type>,
		BACnetChoiceElement<97, BACnetUnsigned32Type>,
		BACnetChoiceElement<98, BACnetUnsigned32Type>,
		BACnetChoiceElement<99, BACnetUnsigned32Type>,
		BACnetChoiceElement<100, BACnetUnsigned32Type>,
		BACnetChoiceElement<101, BACnetUnsigned32Type>,
		BACnetChoiceElement<102, BACnetUnsigned32Type>,
		BACnetChoiceElement<103, BACnetUnsigned32Type>,
		BACnetChoiceElement<104, BACnetUnsigned32Type>,
		BACnetChoiceElement<105, BACnetUnsigned32Type>,
		BACnetChoiceElement<106, BACnetUnsigned32Type>,
		BACnetChoiceElement<107, BACnetUnsigned32Type>,
		BACnetChoiceElement<108, BACnetUnsigned32Type>,
		BACnetChoiceElement<109, BACnetUnsigned32Type>,
		BACnetChoiceElement<110, BACnetUnsigned32Type>,
		BACnetChoiceElement<111, BACnetUnsigned32Type>,
		BACnetChoiceElement<112, BACnetUnsigned32Type>,
		BACnetChoiceElement<113, BACnetUnsigned32Type>,
		BACnetChoiceElement<114, BACnetUnsigned32Type>,
		BACnetChoiceElement<115, BACnetUnsigned32Type>,
		BACnetChoiceElement<116, BACnetUnsigned32Type>,
		BACnetChoiceElement<117, BACnetUnsigned32Type>,
		BACnetChoiceElement<118, BACnetUnsigned32Type>,
		BACnetChoiceElement<119, BACnetUnsigned32Type>,
		BACnetChoiceElement<120, BACnetUnsigned32Type>,
		BACnetChoiceElement<121, BACnetUnsigned32Type>,
		BACnetChoiceElement<122, BACnetUnsigned32Type>,
		BACnetChoiceElement<123, BACnetUnsigned32Type>,
		BACnetChoiceElement<124, BACnetUnsigned32Type>,
		BACnetChoiceElement<125, BACnetUnsigned32Type>,
		BACnetChoiceElement<126, BACnetUnsigned32Type>,
		BACnetChoiceElement<127, BACnetUnsigned32Type>,
		BACnetChoiceElement<128, BACnetUnsigned32Type>,
		BACnetChoiceElement<129, BACnetUnsigned32Type>,
		BACnetChoiceElement<130, BACnetUnsigned32Type>,
		BACnetChoiceElement<131, BACnetUnsigned32Type>,
		BACnetChoiceElement<132, BACnetUnsigned32Type>,
		BACnetChoiceElement<133, BACnetUnsigned32Type>,
		BACnetChoiceElement<134, BACnetUnsigned32Type>,
		BACnetChoiceElement<135, BACnetUnsigned32Type>,
		BACnetChoiceElement<136, BACnetUnsigned32Type>,
		BACnetChoiceElement<137, BACnetUnsigned32Type>,
		BACnetChoiceElement<138, BACnetUnsigned32Type>,
		BACnetChoiceElement<139, BACnetUnsigned32Type>,
		BACnetChoiceElement<140, BACnetUnsigned32Type>,
		BACnetChoiceElement<141, BACnetUnsigned32Type>,
		BACnetChoiceElement<142, BACnetUnsigned32Type>,
		BACnetChoiceElement<143, BACnetUnsigned32Type>,
		BACnetChoiceElement<144, BACnetUnsigned32Type>,
		BACnetChoiceElement<145, BACnetUnsigned32Type>,
		BACnetChoiceElement<146, BACnetUnsigned32Type>,
		BACnetChoiceElement<147, BACnetUnsigned32Type>,
		BACnetChoiceElement<148, BACnetUnsigned32Type>,
		BACnetChoiceElement<149, BACnetUnsigned32Type>,
		BACnetChoiceElement<150, BACnetUnsigned32Type>,
		BACnetChoiceElement<151, BACnetUnsigned32Type>,
		BACnetChoiceElement<152, BACnetUnsigned32Type>,
		BACnetChoiceElement<153, BACnetUnsigned32Type>,
		BACnetChoiceElement<154, BACnetUnsigned32Type>,
		BACnetChoiceElement<155, BACnetUnsigned32Type>,
		BACnetChoiceElement<156, BACnetUnsigned32Type>,
		BACnetChoiceElement<157, BACnetUnsigned32Type>,
		BACnetChoiceElement<158, BACnetUnsigned32Type>,
		BACnetChoiceElement<159, BACnetUnsigned32Type>,
		BACnetChoiceElement<160, BACnetUnsigned32Type>,
		BACnetChoiceElement<161, BACnetUnsigned32Type>,
		BACnetChoiceElement<162, BACnetUnsigned32Type>,
		BACnetChoiceElement<163, BACnetUnsigned32Type>,
		BACnetChoiceElement<164, BACnetUnsigned32Type>,
		BACnetChoiceElement<165, BACnetUnsigned32Type>,
		BACnetChoiceElement<166, BACnetUnsigned32Type>,
		BACnetChoiceElement<167, BACnetUnsigned32Type>,
		BACnetChoiceElement<168, BACnetUnsigned32Type>,
		BACnetChoiceElement<169, BACnetUnsigned32Type>,
		BACnetChoiceElement<170, BACnetUnsigned32Type>,
		BACnetChoiceElement<171, BACnetUnsigned32Type>,
		BACnetChoiceElement<172, BACnetUnsigned32Type>,
		BACnetChoiceElement<173, BACnetUnsigned32Type>,
		BACnetChoiceElement<174, BACnetUnsigned32Type>,
		BACnetChoiceElement<175, BACnetUnsigned32Type>,
		BACnetChoiceElement<176, BACnetUnsigned32Type>,
		BACnetChoiceElement<177, BACnetUnsigned32Type>,
		BACnetChoiceElement<178, BACnetUnsigned32Type>,
		BACnetChoiceElement<179, BACnetUnsigned32Type>,
		BACnetChoiceElement<180, BACnetUnsigned32Type>,
		BACnetChoiceElement<181, BACnetUnsigned32Type>,
		BACnetChoiceElement<182, BACnetUnsigned32Type>,
		BACnetChoiceElement<183, BACnetUnsigned32Type>,
		BACnetChoiceElement<184, BACnetUnsigned32Type>,
		BACnetChoiceElement<185, BACnetUnsigned32Type>,
		BACnetChoiceElement<186, BACnetUnsigned32Type>,
		BACnetChoiceElement<187, BACnetUnsigned32Type>,
		BACnetChoiceElement<188, BACnetUnsigned32Type>,
		BACnetChoiceElement<189, BACnetUnsigned32Type>,
		BACnetChoiceElement<190, BACnetUnsigned32Type>,
		BACnetChoiceElement<191, BACnetUnsigned32Type>,
		BACnetChoiceElement<192, BACnetUnsigned32Type>,
		BACnetChoiceElement<193, BACnetUnsigned32Type>,
		BACnetChoiceElement<194, BACnetUnsigned32Type>,
		BACnetChoiceElement<195, BACnetUnsigned32Type>,
		BACnetChoiceElement<196, BACnetUnsigned32Type>,
		BACnetChoiceElement<197, BACnetUnsigned32Type>,
		BACnetChoiceElement<198, BACnetUnsigned32Type>,
		BACnetChoiceElement<199, BACnetUnsigned32Type>,
		BACnetChoiceElement<200, BACnetUnsigned32Type>,
		BACnetChoiceElement<201, BACnetUnsigned32Type>,
		BACnetChoiceElement<202, BACnetUnsigned32Type>,
		BACnetChoiceElement<203, BACnetUnsigned32Type>,
		BACnetChoiceElement<204, BACnetUnsigned32Type>,
		BACnetChoiceElement<205, BACnetUnsigned32Type>,
		BACnetChoiceElement<206, BACnetUnsigned32Type>,
		BACnetChoiceElement<207, BACnetUnsigned32Type>,
		BACnetChoiceElement<208, BACnetUnsigned32Type>,
		BACnetChoiceElement<209, BACnetUnsigned32Type>,
		BACnetChoiceElement<210, BACnetUnsigned32Type>,
		BACnetChoiceElement<211, BACnetUnsigned32Type>,
		BACnetChoiceElement<212, BACnetUnsigned32Type>,
		BACnetChoiceElement<213, BACnetUnsigned32Type>,
		BACnetChoiceElement<214, BACnetUnsigned32Type>,
		BACnetChoiceElement<215, BACnetUnsigned32Type>,
		BACnetChoiceElement<216, BACnetUnsigned32Type>,
		BACnetChoiceElement<217, BACnetUnsigned32Type>,
		BACnetChoiceElement<218, BACnetUnsigned32Type>,
		BACnetChoiceElement<219, BACnetUnsigned32Type>,
		BACnetChoiceElement<220, BACnetUnsigned32Type>,
		BACnetChoiceElement<221, BACnetUnsigned32Type>,
		BACnetChoiceElement<222, BACnetUnsigned32Type>,
		BACnetChoiceElement<223, BACnetUnsigned32Type>,
		BACnetChoiceElement<224, BACnetUnsigned32Type>,
		BACnetChoiceElement<225, BACnetUnsigned32Type>,
		BACnetChoiceElement<226, BACnetUnsigned32Type>,
		BACnetChoiceElement<227, BACnetUnsigned32Type>,
		BACnetChoiceElement<228, BACnetUnsigned32Type>,
		BACnetChoiceElement<229, BACnetUnsigned32Type>,
		BACnetChoiceElement<230, BACnetUnsigned32Type>,
		BACnetChoiceElement<231, BACnetUnsigned32Type>,
		BACnetChoiceElement<232, BACnetUnsigned32Type>,
		BACnetChoiceElement<233, BACnetUnsigned32Type>,
		BACnetChoiceElement<234, BACnetUnsigned32Type>,
		BACnetChoiceElement<235, BACnetUnsigned32Type>,
		BACnetChoiceElement<236, BACnetUnsigned32Type>,
		BACnetChoiceElement<237, BACnetUnsigned32Type>,
		BACnetChoiceElement<238, BACnetUnsigned32Type>,
		BACnetChoiceElement<239, BACnetUnsigned32Type>,
		BACnetChoiceElement<240, BACnetUnsigned32Type>,
		BACnetChoiceElement<241, BACnetUnsigned32Type>,
		BACnetChoiceElement<242, BACnetUnsigned32Type>,
		BACnetChoiceElement<243, BACnetUnsigned32Type>,
		BACnetChoiceElement<244, BACnetUnsigned32Type>,
		BACnetChoiceElement<245, BACnetUnsigned32Type>,
		BACnetChoiceElement<246, BACnetUnsigned32Type>,
		BACnetChoiceElement<247, BACnetUnsigned32Type>,
		BACnetChoiceElement<248, BACnetUnsigned32Type>,
		BACnetChoiceElement<249, BACnetUnsigned32Type>,
		BACnetChoiceElement<250, BACnetUnsigned32Type>,
		BACnetChoiceElement<251, BACnetUnsigned32Type>,
		BACnetChoiceElement<252, BACnetUnsigned32Type>,
		BACnetChoiceElement<253, BACnetUnsigned32Type>,
		BACnetChoiceElement<254, BACnetUnsigned32Type>
	>
{
public:

};

//Property Reference
class BACnetPropertyReference : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetPropertyIdentifierType>,
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
		BACnetSequenceElement<0, BACnetPropertyIdentifierType>,
		BACnetSequenceElement<1, BACnetUnsignedType, true>,
		BACnetSequenceElement<2, BACnetAnyType>,
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

//forward declaration because BACnet is mean and self-referencing. :(
class BACnetError;

//Read Access Result
class ReadAccessResult : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<2, BACnetPropertyIdentifierType>,
					BACnetSequenceElement<3, BACnetUnsignedType, true>,
					BACnetSequenceElement<NoTag,
						BACnetChoice<NoDefault,
							BACnetChoiceElement<4, BACnetAnyType>,
							BACnetChoiceElement<5, BACnetError>
						>,
						false
					>
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
	BACnetSequenceElement<0, BACnetObjectIDType>,
	BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyReference>, false>
	>
{
public:

};

//Write Access Result
class WriteAccessSpecification : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetObjectIDType>,
	BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyValue>, false>
	>
{
public:

};
