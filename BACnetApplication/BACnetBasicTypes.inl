#pragma once

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
