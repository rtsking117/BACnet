#pragma once

#include "BACnetBasicTypes.inl"
#include "BACnetPropertyTypes.inl"
#include "BACnetAlarmAndEventServices.inl"

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
		BACnetSequenceElement<0, BACnetRecipientProcess, false>,
		BACnetSequenceElement<1, BACnetBooleanType, false>,
		BACnetSequenceElement<2, BACnetUnsignedType, false>,
		BACnetSequenceElement<3, BACnetUnsignedType, false>,
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
		BACnetSequenceElement<0, BACnetRecipientProcess, false>,
		BACnetSequenceElement<1, BACnetObjectPropertyReference, false>,
		BACnetSequenceElement<2, BACnetBooleanType, false>,
		BACnetSequenceElement<3, BACnetUnsignedType, false>,
		BACnetSequenceElement<4, BACnetRealValueType, true>
	>
{
public:

};

class BACnetConfirmedEventNotificationRequest;

//Event Log Record
class EventLogRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType, false>,
		BACnetSequenceElement<1,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetLogStatusType>,
				BACnetChoiceElement<1, BACnetConfirmedEventNotificationRequest>,
				BACnetChoiceElement<2, BACnetRealValueType>
			>, false
		>
	>
{
public:

};

//Event Notification Subscription
class BACnetEventNotificationSubscription : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetRecipient, false>,
		BACnetSequenceElement<1, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<2, BACnetBooleanType, false>,
		BACnetSequenceElement<3, BACnetUnsignedType, false>,
	>
{
public:

};

//Event Parameter

//Fault Parameter

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
		BACnetSequenceElement<0, BACnetDateTimeType, false>,
		BACnetSequenceElement<1, BACnetLogData, false>
	>
{
public:

};

//Log Record
class BACnetLogRecord : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetDateTimeType, false>,
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

//Notification Parameters
class BACnetNotificationParameters : public
	BACnetChoice < NoDefault,
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
					false
				>,
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
		BACnetChoiceElement < 9,
			BACnetSequence <
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
					false
				>
			>
		> ,
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
				BACnetSequenceElement<5, BACnetAuthenticationFactorTypeType, true>
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
					false
				>,
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