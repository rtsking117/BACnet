#pragma once

#include <BACnetTypes.h>

enum class ErrorClass : U16
{
	Device,
	Object,
	Property,
	Resources,
	Security,
	Services,
	VirtualTerminal,
	Communication,
	Vendor_0 = 64,
	Vendor_Max = 0xFFFF,
};

enum class ErrorCode : U16
{
	Other,
	ConfigurationInProgress = 2,
	DeviceBusy,
	DynamicCreationNotSupported,
	FileAccessDenied,
	InconsistentParameters = 7,
	InconsistentSelectionCriterion,
	InvalidDataType,
	InvalidFileAccessMethod,
	InvalidFileStartPosition,
	InvalidParameterDataType = 13,
	InvalidTimeStamp,
	MissingRequiredParameter = 16,
	NoObjectsOfSpecifiedType,
	NoSpaceForObject,
	NoSpaceToAddListElement,
	NoSpaceToWriteProperty,
	NoVTSessionsAvailable,
	PropertyIsNotAList,
	ObjectDeletionNotPermitted,
	ObjectIdentifierAlreadyExists,
	OperationalProblem,
	PasswordFailure,
	ReadAccessDenied,
	ServiceRequestDenied = 29,
	Timeout,
	UnknownObject,
	UnknownProperty,
	UnknownVTClass = 34,
	UnknownVTSession,
	UnsupportedObjectType,
	ValueOutOfRange,
	VTSessionAlreadyClosed,
	VTSessionTerminationFailure,
	WriteAccessDenied,
	CharacterSetNotSupported,
	InvalidArrayIndex,
	COVSubscriptionFailed,
	NotCOVProperty,
	OptionalFunctionalityNotSupported,
	InvalidConfigurationData,
	DatatypeNotSupported,
	DulicateName,
	DuplicateObjectID,
	PropertyIsNotAnArray,
	Abort_BufferOverflow,
	Abort_InvalidAPDUInThisState,
	Abort_PreemptedByHigherPriorityTask,
	Abort_SegmentationNotSupported,
	Abort_Proprietary,
	Abort_Other,
	InvalidTag,
	NetworkDown,
	Reject_BufferOverflow,
	Reject_InconsistentParameters,
	Reject_InvalidParameterDataType,
	Reject_InvalidTag,
	Reject_MissingRequiredParameter,
	Reject_ParameterOutOfRange,
	Reject_TooManyArguments,
	Reject_UndefinedEnumeration,
	Reject_UnrecognizedService,
	Reject_Proprietary,
	Reject_Other,
	UnknownDevice,
	UnknownRoute,
	ValueNotInitialized,
	InvalidEventState,
	NoAlarmConfigured,
	LogBufferFull,
	LoggedValuePurged,
	NoProertySpecified,
	NotConfiguredForTriggeredLogging,
	UnknownSubscription,
	ParameterOutOfRange,
	ListElementNotFound,
	Busy,
	CommunicationDisabled,
	Success,
	AccessDenied,
	BadDestinationAddress,
	BadDestinationDeviceID,
	BadSignature,
	BadSourceAddress,
	BadTimestamp,
	CannotUseKey,
	CannotVerifyMessageID,
	CorrectKeyRevision,
	DestinationDeviceIDRequired,
	DuplicateMessage,
	EncryptionNotConfigured,
	EncryptionRequired,
	IncorrectKey,
	InvalidKeyData,
	KeyUpdateInProgress,
	MalformedMessage,
	NotKeyServer,
	SecurityNotConfigured,
	SourceSecurityRequired,
	TooManyKeys,
	UnknownAuthenticationType,
	UnknownKey,
	UnknownKeyRevision,
	UnknownSourceMessage,
	NotRouterToDNET,
	RouterBusy,
	UnknownNetworkMessage,
	MessageTooLong,
	SecurityError,
	AddressingError,
	WriteBDTFailed,
	ReadBDTFailed,
	RegisterForeignDeviceFailed,
	ReadFDTFailed,
	DeleteFDTEntryFailed,
	DistributeBroadcastFailed,
	UnknownFileSize,
	Abort_APDUTooLong,
	Abort_ApplicationExceededReplyTime,
	Abort_OutOfResources,
	Abort_TSMTimeout,
	Abort_WindowSizeOutOfRange,
	FileFull,
	InconsistentConfiguration,
	InconsistentObjectType,
	InternalError,
	NotConfigured,
	OutOfMemory,
	ValueTooLong,
	Abort_InsufficientSecurity,
	Abort_SecurityError,
	DuplicateEntry,
	InvalidValueInThisState,
	Vendor_0 = 256,
	Vendor_Max = 0xFFFF,
};
