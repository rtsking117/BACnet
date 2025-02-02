#pragma once

#include <BasicASN1.h>
#include <ComplexASN1.h>

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