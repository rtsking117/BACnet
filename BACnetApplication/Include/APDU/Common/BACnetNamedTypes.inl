#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//=============================================================================================
//							UNSIGNED INTEGERS
//=============================================================================================

typedef BACnetUnsignedType BACnetAccessThreatLevelType;

//=============================================================================================
//							   BIT STRINGS
//=============================================================================================

typedef BACnetBitStringType BACnetDaysOfWeekType;
typedef BACnetBitStringType BACnetEventTransitionBits;
typedef BACnetBitStringType BACnetLimitEnableType;
typedef BACnetBitStringType BACnetLogStatusType;
typedef BACnetBitStringType BACnetObjectTypesSupportedType;
typedef BACnetBitStringType BACnetResultFlagsType;
typedef BACnetBitStringType BACnetServicesSupportedType;
typedef BACnetBitStringType BACnetStatusFlagsType;

//=============================================================================================
//							 RAW BINARY DATA
//=============================================================================================

typedef BACnetOctetStringType BACnetWeekAndDayType;