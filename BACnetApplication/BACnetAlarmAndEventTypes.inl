#pragma once

class BACnetClientCOV;
class BACnetCOVMultipleSubscription;
class BACnetCOVSubscription;
class EventLogRecord;
class BACnetEventNotificationSubscription;
class BACnetLogData;
class BACnetLogMultipleRecord;
class BACnetLogRecord;
class BACnetNotificationParameters;
class BACnetRecipient;
class BACnetRecipientProcess;
class BACnetTimeStamp;

#include "BACnetBasicTypes.inl"
#include "BACnetPropertyTypes.inl"
#include "BACnetAlarmAndEventServices.inl"


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
	BACnetSequenceElement<0, BACnetRecipient>,
	BACnetSequenceElement<1, BACnetUnsigned32Type>
	>
{
public:

};

//Client COV
class BACnetClientCOV : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<NoTag, BACnetRealValueType>,
		BACnetChoiceElement<NoTag, BACnetNullType>
	>
{
public:

	bool UsesDefaultIncrement()
	{
		return is_selected(1);
	}

	bool UsesRealValueIncrement()
	{
		return is_selected(0);
	}

	float GetRealValueIncrement()
	{
		if(!UsesRealValueIncrement())
		{
			return 0.0f;
		}
		return get<0>().get();
	}

	void SetDefaultIncrement()
	{
		make_selected(1);
		get<1>().set();
	}

	void SetRealValueIncrement(float IncrementValue)
	{
		make_selected(0);
		get<0>().set(IncrementValue);
	}
};

//COV Multiple Subscription
class BACnetCOVMultipleSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipientProcess>,
		BACnetSequenceElement<1, BACnetBooleanType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, 
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType>,
					BACnetSequenceElement<1,
						BACnetSequenceOf<
							BACnetSequence<
								BACnetSequenceElement<0, BACnetPropertyReference>,
								BACnetSequenceElement<1, BACnetRealValueType, true>,
								BACnetSequenceElement<2, BACnetBooleanType>
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

//COV Subscription
class BACnetCOVSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipientProcess>,
		BACnetSequenceElement<1, BACnetObjectPropertyReference>,
		BACnetSequenceElement<2, BACnetBooleanType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, BACnetRealValueType, true>
	>
{
public:

};

//Event Notification Subscription
class BACnetEventNotificationSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipient>,
		BACnetSequenceElement<1, BACnetUnsigned32Type>,
		BACnetSequenceElement<2, BACnetBooleanType>,
		BACnetSequenceElement<3, BACnetUnsignedType>
	>
{
public:

};

//Event Parameter
class BACnetEventParameter : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetBitStringType>,
				BACnetSequenceElement<2, BACnetSequenceOf<BACnetBitStringType>, false>
			>
		>,
		BACnetChoiceElement<1,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetPropertyStates>, false>
			>
		>,
		BACnetChoiceElement<2, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, 
					BACnetChoice<NoDefault,
						BACnetChoiceElement<0, BACnetBitStringType>,
						BACnetChoiceElement<1, BACnetRealValueType>
					>, false
				>
			>
		>,
		BACnetChoiceElement<3,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<4,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>,
				BACnetSequenceElement<2, BACnetRealValueType>,
				BACnetSequenceElement<3, BACnetRealValueType>,
				BACnetSequenceElement<4, BACnetRealValueType>
			>
		>,
		BACnetChoiceElement<5,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetRealValueType>,
				BACnetSequenceElement<2, BACnetRealValueType>,
				BACnetSequenceElement<3, BACnetRealValueType>
			>
		>,
		BACnetChoiceElement<8,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetLifeSafetyStateType>, false>,
				BACnetSequenceElement<2, BACnetSequenceOf<BACnetLifeSafetyStateType>, false>,
				BACnetSequenceElement<3, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<9, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsigned16Type>,
				BACnetSequenceElement<1, BACnetUnsignedType>,
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
							BACnetChoiceElement<0, BACnetDeviceObjectPropertyReference>
						>
					>, false
				>
			>
		>,
		BACnetChoiceElement<10,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsigned32Type>
			>
		>,
		BACnetChoiceElement<11,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsignedType>,
				BACnetSequenceElement<2, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<13, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetAccessEventType>, false>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference>
			>
		>,
		BACnetChoiceElement<14, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetDoubleType>,
				BACnetSequenceElement<2, BACnetDoubleType>,
				BACnetSequenceElement<3, BACnetDoubleType>
			>
		>,
		BACnetChoiceElement<15,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSignedType>,
				BACnetSequenceElement<2, BACnetSignedType>,
				BACnetSequenceElement<3, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<16,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetUnsignedType>,
				BACnetSequenceElement<2, BACnetUnsignedType>,
				BACnetSequenceElement<3, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<17,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetCharacterStringType>>
			>
		>,
		BACnetChoiceElement<18,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetStatusFlagsType>
			>
		>,
		BACnetChoiceElement<20, BACnetNullType>,
		BACnetChoiceElement<21, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>
			>
		>,
		BACnetChoiceElement<22,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsignedType>,
				BACnetSequenceElement<1, BACnetSequenceOf<BACnetTimerStateType>>,
				BACnetSequenceElement<2, BACnetDeviceObjectPropertyReference>
			>
		>
	>
{
public:

};

//Fault Parameter
class BACnetFaultParameter : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetNullType>,
		BACnetChoiceElement<1, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetCharacterStringType>, false>
			>
		>,
		BACnetChoiceElement<2,
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
							BACnetChoiceElement<0, BACnetDeviceObjectPropertyReference>
						>
					>,
					false
				>
			>
		>,
		BACnetChoiceElement<3, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetLifeSafetyStateType>, false>,
				BACnetSequenceElement<1, BACnetDeviceObjectPropertyReference, false>
			>
		>,
		BACnetChoiceElement<4, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetSequenceOf<BACnetPropertyStates>, false>
			>
		>,
		BACnetChoiceElement<5, 
			BACnetSequence<
				BACnetSequenceElement<0, BACnetDeviceObjectPropertyReference, false>,
			>
		>,
		BACnetChoiceElement<6,
			BACnetSequence<
				BACnetSequenceElement<0,
					BACnetChoice<NoDefault,
						BACnetChoiceElement<NoTag, BACnetRealValueType>,
						BACnetChoiceElement<NoTag, BACnetUnsignedType>,
						BACnetChoiceElement<NoTag, BACnetDoubleType>,
						BACnetChoiceElement<NoTag, BACnetSignedType>
					>,
					false
				>,
				BACnetSequenceElement<1,
					BACnetChoice<NoDefault,
						BACnetChoiceElement<NoTag, BACnetRealValueType>,
						BACnetChoiceElement<NoTag, BACnetUnsignedType>,
						BACnetChoiceElement<NoTag, BACnetDoubleType>,
						BACnetChoiceElement<NoTag, BACnetSignedType>
					>,
					false
				>
			>
		>,
		BACnetChoiceElement<7,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetDeviceObjectPropertyReference, false>
			>
		>
	>
{
public:

};

//Log Data
class BACnetLogData : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetLogStatusType>,
		BACnetChoiceElement<1, 
			BACnetSequenceOf<
				BACnetChoice<NoDefault,
					BACnetChoiceElement<0, BACnetBooleanType>,
					BACnetChoiceElement<1, BACnetRealValueType>,
					BACnetChoiceElement<2, BACnetEnumeratedType>,
					BACnetChoiceElement<3, BACnetUnsignedType>,
					BACnetChoiceElement<4, BACnetSignedType>,
					BACnetChoiceElement<5, BACnetBitStringType>,
					BACnetChoiceElement<6, BACnetNullType>,
					BACnetChoiceElement<7, BACnetError>,
					BACnetChoiceElement<8, BACnetAnyType>
				>
			>
		>
	>
{
public:

};

//Log Multiple Record
class BACnetLogMultipleRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1, BACnetLogData>
	>
{
public:

};

//Log Record
class BACnetLogRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1, 
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetLogStatusType>,
				BACnetChoiceElement<1, BACnetBooleanType>,
				BACnetChoiceElement<2, BACnetRealValueType>,
				BACnetChoiceElement<3, BACnetEnumeratedType>,
				BACnetChoiceElement<4, BACnetUnsignedType>,
				BACnetChoiceElement<5, BACnetSignedType>,
				BACnetChoiceElement<6, BACnetBitStringType>,
				BACnetChoiceElement<7, BACnetNullType>,
				BACnetChoiceElement<8, BACnetError>,
				BACnetChoiceElement<9, BACnetRealValueType>,
				BACnetChoiceElement<10, BACnetAnyType>
			>, false
		>,
		BACnetSequenceElement<2, BACnetStatusFlagsType, true>
	>
{
public:

};


//Time Stamp
class BACnetTimeStamp : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetTimeType>,
		BACnetSequenceElement<1, BACnetUnsigned16Type>,
		BACnetSequenceElement<2, BACnetDateTimeType>
	>
{
public:

};

//Notification Parameters
class BACnetChangeOfBitstringNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetBitStringType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>
	>
{

};

class BACnetChangeOfStateNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetPropertyStates>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>
	>
{

};

class BACnetChangeOfValueNotification : public
	BACnetSequence<
		BACnetSequenceElement<0,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetBitStringType>,
				BACnetChoiceElement<1, BACnetRealValueType>
			>
		>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>
	>
{

};

class BACnetCommandFailureNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAnyType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetAnyType>
	>
{

};

class BACnetFloatingLimitNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRealValueType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetRealValueType>,
		BACnetSequenceElement<3, BACnetRealValueType>
	>
{

};

class BACnetOutOfRangeNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRealValueType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetRealValueType>,
		BACnetSequenceElement<3, BACnetRealValueType>
	>
{

};

class BACnetComplexEventNotification : public
	BACnetSequenceOf<BACnetPropertyValue>
{

};

class BACnetChangeOfLifeSafetyNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetLifeSafetyStateType>,
		BACnetSequenceElement<1, BACnetLifeSafetyModeType>,
		BACnetSequenceElement<2, BACnetStatusFlagsType>,
		BACnetSequenceElement<3, BACnetLifeSafetyOperationType>
	>
{

};

class BACnetExtendedNotificationParameter : public
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
{

};

class BACnetExtendedNotification : public
	BACnetSequence <
		BACnetSequenceElement<0, BACnetUnsigned16Type>,
		BACnetSequenceElement<1, BACnetUnsignedType>,
		BACnetSequenceElement<2, BACnetSequenceOf<BACnetExtendedNotificationParameter>>
	>
{

};

class BACnetBufferReadyNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDeviceObjectPropertyValue>,
		BACnetSequenceElement<1, BACnetUnsigned32Type>,
		BACnetSequenceElement<2, BACnetUnsigned32Type>
	>
{

};

class BACnetUnsignedRangeNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsignedType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetUnsignedType>
	>
{

};

class BACnetAccessEventNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAccessEventType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetDeviceObjectReference>,
		BACnetSequenceElement<5, BACnetAuthenticationFactorTypeType, true>
	>
{

};

class BACnetDoubleOutOfRangeNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDoubleType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetDoubleType>,
		BACnetSequenceElement<3, BACnetDoubleType>
	>
{

};

class BACnetSignedOutOfRangeNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetSignedType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetSignedType>
	>
{
	
};
	
class BACnetUnsignedOutOfRangeNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsignedType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetUnsignedType>
	>
{
	
};
	
class BACnetChangeOfCharacterStringNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetCharacterStringType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetCharacterStringType>
	>
{
	
};

class BACnetChangeOfStatusFlagsNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetAnyType, true>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>
	>
{

};

class BACnetChangeOfReliabilityNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetReliabilityType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetSequenceOf<BACnetPropertyValue>>
	>
{

};

class BACnetChangeOfDiscreteValueNotification : public
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
			>
		>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>
	>
{

};

class BACnetChangeOfTimerNotification : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetTimerStateType>,
		BACnetSequenceElement<1, BACnetStatusFlagsType>,
		BACnetSequenceElement<2, BACnetDateTimeType>,
		BACnetSequenceElement<3, BACnetTimerTransitionType, true>,
		BACnetSequenceElement<4, BACnetUnsignedType, true>,
		BACnetSequenceElement<5, BACnetDateTimeType, true>
	>
{

};

class BACnetNotificationParameters : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetChangeOfBitstringNotification>,
		BACnetChoiceElement<1, BACnetChangeOfStateNotification>,
		BACnetChoiceElement<2, BACnetChangeOfValueNotification>,
		BACnetChoiceElement<3, BACnetCommandFailureNotification>,
		BACnetChoiceElement<4, BACnetFloatingLimitNotification>,
		BACnetChoiceElement<5, BACnetOutOfRangeNotification>,
		BACnetChoiceElement<6, BACnetComplexEventNotification>,
		BACnetChoiceElement<8, BACnetChangeOfLifeSafetyNotification>,
		BACnetChoiceElement<9, BACnetExtendedNotification>,
		BACnetChoiceElement<10, BACnetBufferReadyNotification>,
		BACnetChoiceElement<11, BACnetUnsignedRangeNotification>,
		BACnetChoiceElement<13, BACnetAccessEventNotification>,
		BACnetChoiceElement<14, BACnetDoubleOutOfRangeNotification>,
		BACnetChoiceElement<15, BACnetSignedOutOfRangeNotification>,
		BACnetChoiceElement<16, BACnetUnsignedOutOfRangeNotification>,
		BACnetChoiceElement<17, BACnetChangeOfCharacterStringNotification>,
		BACnetChoiceElement<18, BACnetChangeOfStatusFlagsNotification>,
		BACnetChoiceElement<19, BACnetChangeOfReliabilityNotification>,
		BACnetChoiceElement<21, BACnetChangeOfDiscreteValueNotification>,
		BACnetChoiceElement<22, BACnetChangeOfTimerNotification>
	>
{
	constexpr static U32 GetIndexFromEventType(BACnetEventType EventType)
	{
		switch(EventType)
		{
		case BACnetEventType::ChangeOfBitstring: return 0;
		case BACnetEventType::ChangeOfState: return 1;
		case BACnetEventType::ChangeOfValue: return 2;
		case BACnetEventType::CommandFailure: return 3;
		case BACnetEventType::FloatingLimit: return 4;
		case BACnetEventType::OutOfRange: return 5;
			// Event Type 6 is a special case.
			// Event Type 7 skipped
		case BACnetEventType::ChangeOfLifeSafety: return 7;
		case BACnetEventType::Extended: return 8;
		case BACnetEventType::BufferReady: return 9;
		case BACnetEventType::UnsignedRange: return 10;
			// Event Type 12 skipped
		case BACnetEventType::AccessEvent: return 11;
		case BACnetEventType::DoubleOutOfRange: return 12;
		case BACnetEventType::SignedOutOfRange: return 13;
		case BACnetEventType::UnsignedOutOfRange: return 14;
		case BACnetEventType::ChangeOfCharacterString: return 15;
		case BACnetEventType::ChangeOfStatusFlags: return 16;
		case BACnetEventType::ChangeOfReliability: return 17;
			// Event Type 20 skipped
		case BACnetEventType::ChangeOfDiscreteValue: return 18;
		case BACnetEventType::ChangeOfTimer: return 19;
		default:
			if(EventType > BACnetEventType::VendorBegin && EventType <= BACnetEventType::VendorEnd)
			{
				return 6;
			}
			return InvalidIndex;
		}
	}

public:
	bool IsEventTypeSelected(BACnetEventType EventType)
	{
		U32 Index = GetIndexFromEventType(EventType);
		if(Index == InvalidIndex)
		{
			return false;
		}
		return is_selected(Index);
	}

	template<BACnetEventType EventType>
	auto& GetEventType()
	{
		constexpr U32 Index = GetIndexFromEventType(EventType);
		if(!is_selected(Index))
		{
			__debugbreak();
		}
		return get<Index>();
	}
};
