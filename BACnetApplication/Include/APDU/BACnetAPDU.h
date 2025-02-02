#pragma once

//=============================================================================================
//								 BASIC TYPES
//=============================================================================================

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetEnumeratedTypes.inl>
#include <APDU/Common/BACnetNamedTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>
#include <APDU/Common/BACnetTimeStamp.inl>

//=============================================================================================
//								COMPLEX TYPES
//=============================================================================================

#include <APDU/Common/BACnetAccumulatorRecord.inl>
#include <APDU/Common/BACnetActionCommand.inl>
#include <APDU/Common/BACnetActionList.inl>
#include <APDU/Common/BACnetLightingCommand.inl>
#include <APDU/Common/BACnetNameValue.inl>
#include <APDU/Common/BACnetNameValueCollection.inl>
#include <APDU/Common/BACnetOptionalBinaryPV.inl>
#include <APDU/Common/BACnetOptionalCharacterString.inl>
#include <APDU/Common/BACnetOptionalReal.inl>
#include <APDU/Common/BACnetOptionalUnsigned.inl>
#include <APDU/Common/BACnetPrescale.inl>
#include <APDU/Common/BACnetProcessIDSelection.inl>
#include <APDU/Common/BACnetScale.inl>
#include <APDU/Common/BACnetShedLevel.inl>
#include <APDU/Common/BACnetTimerStateChangeValue.inl>

//=============================================================================================
//								   ERRORS
//=============================================================================================

#include <APDU/Errors/BACnetError.inl>
#include <APDU/Errors/ChangeListError.inl>
#include <APDU/Errors/CreateObjectError.inl>
#include <APDU/Errors/ConfirmedPrivateTransferError.inl>
#include <APDU/Errors/SubscribeCOVPropertyMultipleError.inl>
#include <APDU/Errors/WritePropertyMultipleError.inl>
#include <APDU/Errors/VTCloseError.inl>

//=============================================================================================
//								 NETWORKING
//=============================================================================================

#include <APDU/Networking/BACnetAddress.inl>
#include <APDU/Networking/BACnetAddressBinding.inl>
#include <APDU/Networking/BACnetBDTEntry.inl>
#include <APDU/Networking/BACnetFDTEntry.inl>
#include <APDU/Networking/BACnetHostAddress.inl>
#include <APDU/Networking/BACnetHostAndPort.inl>
#include <APDU/Networking/BACnetRouterEntry.inl>
#include <APDU/Networking/BACnetVMACEntry.inl>

//=============================================================================================
//						CONFIRMED OBJECT ACCESS SERVICES
//=============================================================================================

#include <APDU/ObjectAccess/AddListElementRequest.inl>
#include <APDU/ObjectAccess/CreateObjectRequest.inl>
#include <APDU/ObjectAccess/CreateObjectResponse.inl>
#include <APDU/ObjectAccess/DeleteObjectRequest.inl>
#include <APDU/ObjectAccess/ReadPropertyMultipleRequest.inl>
#include <APDU/ObjectAccess/ReadPropertyMultipleResponse.inl>
#include <APDU/ObjectAccess/ReadPropertyRequest.inl>
#include <APDU/ObjectAccess/ReadPropertyResponse.inl>
#include <APDU/ObjectAccess/ReadRangeRequest.inl>
#include <APDU/ObjectAccess/ReadRangeResponse.inl>
#include <APDU/ObjectAccess/RemoveListElementRequest.inl>
#include <APDU/ObjectAccess/WritePropertyMultipleRequest.inl>
#include <APDU/ObjectAccess/WritePropertyRequest.inl>

//=============================================================================================
//					   UNCONFIRMED OBJECT ACCESS SERVICES
//=============================================================================================

#include <APDU/ObjectAccess/WriteGroupRequest.inl>

//=============================================================================================
//							   PROPERTY ACCESS
//=============================================================================================

#include <APDU/PropertyAccess/BACnetChannelValue.inl>
#include <APDU/PropertyAccess/BACnetGroupChannelValue.inl>

#include <APDU/PropertyAccess/BACnetDeviceObjectPropertyReference.inl>
#include <APDU/PropertyAccess/BACnetDeviceObjectReference.inl>
#include <APDU/PropertyAccess/BACnetObjectPropertyReference.inl>
#include <APDU/PropertyAccess/BACnetPropertyReference.inl>

#include <APDU/PropertyAccess/BACnetDeviceObjectPropertyValue.inl>
#include <APDU/PropertyAccess/BACnetObjectPropertyValue.inl>
#include <APDU/PropertyAccess/BACnetPropertyValue.inl>

#include <APDU/PropertyAccess/BACnetPropertyStates.inl>
#include <APDU/PropertyAccess/BACnetPriorityValue.inl>
#include <APDU/PropertyAccess/BACnetPriorityArray.inl>

#include <APDU/PropertyAccess/BACnetSetpointReference.inl>

#include <APDU/PropertyAccess/BACnetPropertyAccessResult.inl>
#include <APDU/PropertyAccess/ReadAccessSpecification.inl>
#include <APDU/PropertyAccess/ReadAccessResult.inl>
#include <APDU/PropertyAccess/WriteAccessSpecification.inl>

//=============================================================================================
//				   CONFIRMED REMOTE DEVICE MANAGEMENT SERVICES
//=============================================================================================

#include <APDU/RemoteDevices/ConfirmedPrivateTransferRequest.inl>
#include <APDU/RemoteDevices/ConfirmedPrivateTransferResponse.inl>
#include <APDU/RemoteDevices/ConfirmedTextMessageRequest.inl>
#include <APDU/RemoteDevices/DeviceCommunicationControlRequest.inl>
#include <APDU/RemoteDevices/ReinitializeDeviceRequest.inl>

//=============================================================================================
//				  UNCONFIRMED REMOTE DEVICE MANAGEMENT SERVICES
//=============================================================================================

#include <APDU/RemoteDevices/IAmRequest.inl>
#include <APDU/RemoteDevices/IHaveRequest.inl>
#include <APDU/RemoteDevices/TimeSynchronizationRequest.inl>
#include <APDU/RemoteDevices/UnconfirmedPrivateTransferRequest.inl>
#include <APDU/RemoteDevices/UnconfirmedTextMessageRequest.inl>
#include <APDU/RemoteDevices/UTCTimeSynchronizationRequest.inl>
#include <APDU/RemoteDevices/WhoHasRequest.inl>
#include <APDU/RemoteDevices/WhoIsRequest.inl>

//=============================================================================================
//								  SCHEDULES
//=============================================================================================

#include <APDU/Schedules/BACnetCalendarEntry.inl>
#include <APDU/Schedules/BACnetDailySchedule.inl>
#include <APDU/Schedules/BACnetDateRange.inl>
#include <APDU/Schedules/BACnetSpecialEvent.inl>
#include <APDU/Schedules/BACnetTimeValue.inl>

//=============================================================================================
//							ALARM AND EVENT TYPES
//=============================================================================================

#include <APDU/AlarmAndEvent/BACnetClientCOV.inl>
#include <APDU/AlarmAndEvent/BACnetCOVSubscription.inl>
#include <APDU/AlarmAndEvent/BACnetCOVMultipleSubscription.inl>
#include <APDU/AlarmAndEvent/BACnetEventLogRecord.inl>
#include <APDU/AlarmAndEvent/BACnetEventNotificationSubscription.inl>
#include <APDU/AlarmAndEvent/BACnetEventParameter.inl>
#include <APDU/AlarmAndEvent/BACnetFaultParameter.inl>
#include <APDU/AlarmAndEvent/BACnetLogData.inl>
#include <APDU/AlarmAndEvent/BACnetLogRecord.inl>
#include <APDU/AlarmAndEvent/BACnetLogMultipleRecord.inl>
#include <APDU/AlarmAndEvent/BACnetNotificationParameters.inl>
#include <APDU/AlarmAndEvent/BACnetPortPermission.inl>
#include <APDU/AlarmAndEvent/BACnetRecipient.inl>
#include <APDU/AlarmAndEvent/BACnetRecipientProcess.inl>

//=============================================================================================
//						CONFIRMED ALARM AND EVENT SERVICES
//=============================================================================================

#include <APDU/AlarmAndEvent/AcknowledgeAlarmRequest.inl>
#include <APDU/AlarmAndEvent/ConfirmedCOVNotificationRequest.inl>
#include <APDU/AlarmAndEvent/ConfirmedCOVNotificationMultipleRequest.inl>
#include <APDU/AlarmAndEvent/ConfirmedEventNotificationRequest.inl>
#include <APDU/AlarmAndEvent/GetAlarmSummaryResponse.inl>
#include <APDU/AlarmAndEvent/GetEnrollmentSummaryRequest.inl>
#include <APDU/AlarmAndEvent/GetEnrollmentSummaryResponse.inl>
#include <APDU/AlarmAndEvent/GetEventInformationRequest.inl>
#include <APDU/AlarmAndEvent/GetEventInformationResponse.inl>
#include <APDU/AlarmAndEvent/LifeSafetyOperationRequest.inl>
#include <APDU/AlarmAndEvent/SubscribeCOVRequest.inl>
#include <APDU/AlarmAndEvent/SubscribeCOVPropertyRequest.inl>
#include <APDU/AlarmAndEvent/SubscribeCOVPropertyMultipleRequest.inl>

//=============================================================================================
//						UNCONFIRMED ALARM AND EVENT SERVICES
//=============================================================================================

#include <APDU/AlarmAndEvent/UnconfirmedCOVNotificationRequest.inl>
#include <APDU/AlarmAndEvent/UnconfirmedCOVNotificationMultipleRequest.inl>
#include <APDU/AlarmAndEvent/UnconfirmedEventNotificationRequest.inl>

//=============================================================================================
//								FILE SERVICES
//=============================================================================================

#include <APDU/Files/ReadFileRequest.inl>
#include <APDU/Files/ReadFileResponse.inl>
#include <APDU/Files/WriteFileRequest.inl>
#include <APDU/Files/WriteFileResponse.inl>

//=============================================================================================
//							   ACCESS CONTROL
//=============================================================================================

#include <APDU/AccessControl/BACnetAccessRule.inl>
#include <APDU/AccessControl/BACnetAssignedAccessRights.inl>
#include <APDU/AccessControl/BACnetAuthenticationFactor.inl>
#include <APDU/AccessControl/BACnetAuthenticationFactorFormat.inl>
#include <APDU/AccessControl/BACnetAuthenticationPolicy.inl>
#include <APDU/AccessControl/BACnetCredentialAuthenticationFactor.inl>

//=============================================================================================
//							VIRTUAL TERMINAL TYPES
//=============================================================================================

#include <APDU/VirtualTerminal/BACnetVTSession.inl>

//=============================================================================================
//						CONFIRMED VIRTUAL TERMINAL SERVICES
//=============================================================================================

#include <APDU/VirtualTerminal/VTOpenRequest.inl>
#include <APDU/VirtualTerminal/VTOpenResponse.inl>
#include <APDU/VirtualTerminal/VTDataRequest.inl>
#include <APDU/VirtualTerminal/VTDataResponse.inl>
#include <APDU/VirtualTerminal/VTCloseRequest.inl>

//=============================================================================================
//							   NETWORK SECURITY
//=============================================================================================

#include <APDU/NetworkSecurity/BACnetKeyIdentifier.inl>
#include <APDU/NetworkSecurity/BACnetNetworkSecurityPolicy.inl>
#include <APDU/NetworkSecurity/BACnetSecurityKeySet.inl>
