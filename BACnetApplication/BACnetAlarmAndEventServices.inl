#pragma once

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
					BACnetSequenceElement<0, BACnetObjectID, false>,
					BACnetSequenceElement<1, BACnetEnumeratedType, false>,
					BACnetSequenceElement<2, BACnetBitStringType, false>,
					BACnetSequenceElement<3, BACnetSequenceOf<BACnetTimeStamp>, false>,
					BACnetSequenceElement<4, BACnetEnumeratedType, false>,
					BACnetSequenceElement<5, BACnetBitStringType, false>,
					BACnetSequenceElement<6, BACnetSequenceOf<BACnetUnsignedType>, false>
				>
			>, false
		>,
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
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetObjectIDType, false>,
		BACnetSequenceElement<3, BACnetUnsignedType, false>,
		BACnetSequenceElement<4, BACnetSequenceOf<BACnetPropertyValue>, false>,
	>
{
public:

};

class UnconfirmedCOVNotificationMultipleRequest : public
	BACnetSequence <
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
								BACnetSequenceElement<0, BACnetPropertyIdentifierType, false>,
								BACnetSequenceElement<1, BACnetUnsignedType, true>,
								BACnetSequenceElement<2, BACnetAnyType, false>,
								BACnetSequenceElement<3, BACnetTimeType, true>,
							>
						>,
						false
					>,
				>
			>,
			false
		>,
	>
{
public:

};

class UnconfirmedEventNotificationRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetUnsigned32Type, false>,
		BACnetSequenceElement<1, BACnetObjectIDType, false>,
		BACnetSequenceElement<2, BACnetObjectIDType, false>,
		BACnetSequenceElement<3, BACnetTimeStamp, false>,
		BACnetSequenceElement<4, BACnetUnsignedType, false>,
		BACnetSequenceElement<5, BACnetUnsigned8Type, false>,
		BACnetSequenceElement<6, BACnetEventTypeType, false>,
		BACnetSequenceElement<7, BACnetCharacterStringType, true>,
		BACnetSequenceElement<8, BACnetNotifyTypeType, false>,
		BACnetSequenceElement<9, BACnetBooleanType, true>,
		BACnetSequenceElement<10, BACnetEventStateType, true>,
		BACnetSequenceElement<11, BACnetEventStateType, false>,
		BACnetSequenceElement<12, BACnetNotificationParameters, true>,
	>
{
public:

};
