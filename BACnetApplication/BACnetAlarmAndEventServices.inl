#pragma once

//Acknowledge Alarm
class AcknowledgeAlarmRequest;
class ConfirmedCOVNotificationRequest;
class ConfirmedCOVNotificationMultipleRequest;
class ConfirmedEventNotificationRequest;
class GetAlarmSummaryResponse;
class GetEnrollmentSummaryRequest;
class GetEnrollmentSummaryResponse;
class GetEventInformationRequest;
class GetEventInformationResponse;
class LifeSafetyOperationRequest;
class SubscribeCOVRequest;
class SubscribeCOVPropertyRequest;
class SubscribeCOVPropertyMultipleRequest;
class UnconfirmedCOVNotificationRequest;
class UnconfirmedCOVNotificationMultipleRequest;
class UnconfirmedEventNotificationRequest;


#include "BACnetBasicTypes.inl"
#include "BACnetComplexTypes.inl"
#include "BACnetAlarmAndEventTypes.inl"
#include "BACnetPropertyTypes.inl" 

//=============================================================================================
//							CONFIRMED ALARM AND EVENT SERVICES
//=============================================================================================

//Acknowledge Alarm
class AcknowledgeAlarmRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetCharacterStringType>
	>
{
public:

};

//Confirmed COV Notification
class ConfirmedCOVNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetPropertyValue>, false>
	>
{
public:

};

//Confirmed COV Notification Multiple
class ConfirmedCOVNotificationMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetDateTimeType, true>,
		BACnetSequenceElement<4,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType>,
					BACnetSequenceElement<1,
						BACnetSequenceOf<
							BACnetSequence<
								BACnetSequenceElement<0, BACnetEnumeratedType>,
								BACnetSequenceElement<1, BACnetUnsignedType, true>,
								BACnetSequenceElement<2, BACnetAnyType>,
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
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetUnsignedType>,
		BACnetSequenceElement<5, BACnetUnsigned8Type>,
		BACnetSequenceElement<6, BACnetEnumeratedType>,
		BACnetSequenceElement<7, BACnetCharacterStringType, true>,
		BACnetSequenceElement<8, BACnetEnumeratedType>,
		BACnetSequenceElement<9, BACnetBooleanType, true>,
		BACnetSequenceElement<10, BACnetEnumeratedType, true>,
		BACnetSequenceElement<11, BACnetEnumeratedType>,
		BACnetSequenceElement<12, BACnetNotificationParameters, true>
	>
{
public:


	bool HasMessageText()
	{
		return is_present<7>();
	}

	bool IsACKRequired()
	{
		return is_present<9>() && get<9>().get();
	}

	bool HasFromState()
	{
		return is_present<10>();
	}

	bool HasEventValues()
	{
		return is_present<12>();
	}

	BACnetNotificationParameters GetEventValues()
	{
		if(!HasEventValues())
		{
			__debugbreak();
		}
		return get<12>();
	}
};

//Event Log Record
class EventLogRecord : public
	BACnetSequence<
	BACnetSequenceElement<0, BACnetDateTimeType>,
		BACnetSequenceElement<1,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetLogStatusType>,
				BACnetChoiceElement<1, ConfirmedEventNotificationRequest>,
				BACnetChoiceElement<2, BACnetRealValueType>
			>, false
		>
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
		BACnetSequenceElement<0, BACnetEnumeratedType>,
		BACnetSequenceElement<1, BACnetRecipientProcess, true>,
		BACnetSequenceElement<2, BACnetEnumeratedType, true>,
		BACnetSequenceElement<3, BACnetEnumeratedType, true>,
		BACnetSequenceElement<4,
			BACnetSequence<
				BACnetSequenceElement<0, BACnetUnsigned8Type>,
				BACnetSequenceElement<1, BACnetUnsigned8Type>
			>, true
		>,
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
					BACnetSequenceElement<0, BACnetObjectID>,
					BACnetSequenceElement<1, BACnetEnumeratedType>,
					BACnetSequenceElement<2, BACnetBitStringType>,
					BACnetSequenceElement<3, BACnetSequenceOf<BACnetTimeStamp>, false>,
					BACnetSequenceElement<4, BACnetEnumeratedType>,
					BACnetSequenceElement<5, BACnetBitStringType>,
					BACnetSequenceElement<6, BACnetSequenceOf<BACnetUnsignedType>, false>
				>
			>, false
		>,
		BACnetSequenceElement<1, BACnetBooleanType>
	>
{
public:

};

//Life Safety Operation
class LifeSafetyOperationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetCharacterStringType>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetObjectIDType, true>
	>
{

};

//Subscribe COV
class SubscribeCOVRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetBooleanType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>
	>
{
public:

};

//Subscribe COV Property
class SubscribeCOVPropertyRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetBooleanType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
		BACnetSequenceElement<4, BACnetPropertyReference>,
		BACnetSequenceElement<5, BACnetRealValueType, true>
	>
{
public:

};

//Subscribe COV Property Multiple
class SubscribeCOVPropertyMultipleRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetBooleanType, true>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<3, BACnetUnsignedType, true>,
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

//=============================================================================================
//							UNCONFIRMED ALARM AND EVENT SERVICES
//=============================================================================================

class UnconfirmedCOVNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetUnsignedType>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetPropertyValue>, false>
	>
{
public:

};

class UnconfirmedCOVNotificationMultipleRequest : public
	BACnetSequence <
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetUnsignedType>,
		BACnetSequenceElement<3, BACnetDateTimeType, true>,
		BACnetSequenceElement<4,
			BACnetSequenceOf<
				BACnetSequence<
					BACnetSequenceElement<0, BACnetObjectIDType>,
					BACnetSequenceElement<1,
						BACnetSequenceOf<
							BACnetSequence<
								BACnetSequenceElement<0, BACnetPropertyIdentifierType>,
								BACnetSequenceElement<1, BACnetUnsignedType, true>,
								BACnetSequenceElement<2, BACnetAnyType>,
								BACnetSequenceElement<3, BACnetTimeType, true>
							>
						>,
						false
					>
				>
			>,
			false
		>
	>
{
public:

};

class UnconfirmedEventNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type>,
		BACnetSequenceElement<1, BACnetObjectIDType>,
		BACnetSequenceElement<2, BACnetObjectIDType>,
		BACnetSequenceElement<3, BACnetTimeStamp>,
		BACnetSequenceElement<4, BACnetUnsignedType>,
		BACnetSequenceElement<5, BACnetUnsigned8Type>,
		BACnetSequenceElement<6, BACnetEventTypeType>,
		BACnetSequenceElement<7, BACnetCharacterStringType, true>,
		BACnetSequenceElement<8, BACnetNotifyTypeType>,
		BACnetSequenceElement<9, BACnetBooleanType, true>,
		BACnetSequenceElement<10, BACnetEventStateType, true>,
		BACnetSequenceElement<11, BACnetEventStateType>,
		BACnetSequenceElement<12, BACnetNotificationParameters, true>
	>
{
public:

};
