#pragma once

#include "BACnetApplication.h"
#include <memory>

namespace ASN1
{
	BACnetResult BACNETAPP_ENTRYPOINT Decode(CObjectPtr<IBACnetBuffer> pData, BACnetValue& Params);
	BACnetResult BACNETAPP_ENTRYPOINT Encode(CObjectPtr<IBACnetBuffer> pData, const BACnetValue& Params);

#pragma region Value Encode/Decode Functions

	BACnetResult BACNETAPP_ENTRYPOINT DecodeBoolean(const BACnetValue &v, bool& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeUnsigned8(const BACnetValue& v, U8& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeUnsigned16(const BACnetValue &v, U16& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeUnsigned32(const BACnetValue &v, U32& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeUnsigned64(const BACnetValue &v, U64& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeSigned8(const BACnetValue& v, I8& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeSigned16(const BACnetValue &v, I16& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeSigned32(const BACnetValue &v, I32& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeSigned64(const BACnetValue &v, I64& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeReal(const BACnetValue &v, float& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeDouble(const BACnetValue &v, double& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeOctetString(const BACnetValue &v, BACnetByteString& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeCharacterString(const BACnetValue &v, BACnetString& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeBitString(const BACnetValue &v, BACnetBitString& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeEnumerated(const BACnetValue &v, U32& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeDate(const BACnetValue &v, U32& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeTime(const BACnetValue &v, U32& Value);
	BACnetResult BACNETAPP_ENTRYPOINT DecodeObjectID(const BACnetValue &v, BACnetObjectID& Value);

	BACnetResult BACNETAPP_ENTRYPOINT EncodeNull(BACnetValue& v);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeBoolean(BACnetValue& v, bool Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeUnsigned8(BACnetValue& v, U8 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeUnsigned16(BACnetValue &v, U16 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeUnsigned32(BACnetValue &v, U32 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeUnsigned64(BACnetValue &v, U64 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeSigned8(BACnetValue& v, I8 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeSigned16(BACnetValue &v, I16 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeSigned32(BACnetValue &v, I32 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeSigned64(BACnetValue &v, I64 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeReal(BACnetValue &v, float Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeDouble(BACnetValue &v, double Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeOctetString(BACnetValue &v, const BACnetByteString& Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeCharacterString(BACnetValue &v, const BACnetString& Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeBitString(BACnetValue &v, const BACnetBitString& Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeEnumerated(BACnetValue &v, U32 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeDate(BACnetValue &v, U32 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeTime(BACnetValue &v, U32 Value);
	BACnetResult BACNETAPP_ENTRYPOINT EncodeObjectID(BACnetValue &v, BACnetObjectID Value);

#pragma endregion

#pragma region Template Encoder/Decoders

	template<BACnetValueType VT, typename CT> struct Codec;

	template<>
	struct Codec<ValueType_Boolean, bool>
	{
		static BACnetResult Decode(const BACnetValue& value, bool &backing)
		{
			return DecodeBoolean(value, backing);
		}

		static BACnetResult Encode(BACnetValue& value, bool backing)
		{
			return EncodeBoolean(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Unsigned, U8>
	{
		static BACnetResult Decode(const BACnetValue& value, U8 &backing)
		{
			return DecodeUnsigned8(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, U8 backing)
		{
			return EncodeUnsigned8(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Unsigned, U16>
	{
		static BACnetResult Decode(const BACnetValue& value, U16 &backing)
		{
			return DecodeUnsigned16(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, U16 backing)
		{
			return EncodeUnsigned16(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Unsigned, U32>
	{
		static BACnetResult Decode(const BACnetValue& value, U32 &backing)
		{
			return DecodeUnsigned32(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, U32 backing)
		{
			return EncodeUnsigned32(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Unsigned, U64>
	{
		static BACnetResult Decode(const BACnetValue& value, U64 &backing)
		{
			return DecodeUnsigned64(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, U64 backing)
		{
			return EncodeUnsigned64(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Signed, I8>
	{
		static BACnetResult Decode(const BACnetValue& value, I8 &backing)
		{
			return DecodeSigned8(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, I8 backing)
		{
			return EncodeSigned8(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Signed, I16>
	{
		static BACnetResult Decode(const BACnetValue& value, I16 &backing)
		{
			return DecodeSigned16(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, I16 backing)
		{
			return EncodeSigned16(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Signed, I32>
	{
		static BACnetResult Decode(const BACnetValue& value, I32 &backing)
		{
			return DecodeSigned32(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, I32 backing)
		{
			return EncodeSigned32(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Signed, I64>
	{
		static BACnetResult Decode(const BACnetValue& value, I64 &backing)
		{
			return DecodeSigned64(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, I64 backing)
		{
			return EncodeSigned64(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Real, float>
	{
		static BACnetResult Decode(const BACnetValue& value, float &backing)
		{
			return DecodeReal(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, float backing)
		{
			return EncodeReal(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Double, double>
	{
		static BACnetResult Decode(const BACnetValue& value, double &backing)
		{
			return DecodeDouble(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, double backing)
		{
			return EncodeDouble(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_OctetString, BACnetByteString>
	{
		static BACnetResult Decode(const BACnetValue& value, BACnetByteString &backing)
		{
			return DecodeOctetString(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, const BACnetByteString& backing)
		{
			return EncodeOctetString(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_CharacterString, BACnetString>
	{
		static BACnetResult Decode(const BACnetValue& value, BACnetString &backing)
		{
			return DecodeCharacterString(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, const BACnetString& backing)
		{
			return EncodeCharacterString(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_BitString, BACnetBitString>
	{
		static BACnetResult Decode(const BACnetValue& value, BACnetBitString &backing)
		{
			return DecodeBitString(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, const BACnetBitString& backing)
		{
			return EncodeBitString(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Enumerated, U32>
	{
		static BACnetResult Decode(const BACnetValue& value, U32 &backing)
		{
			return DecodeEnumerated(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, U32 backing)
		{
			return EncodeEnumerated(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Date, U32>
	{
		static BACnetResult Decode(const BACnetValue& value, U32 &backing)
		{
			return DecodeDate(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, U32 backing)
		{
			return EncodeDate(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_Time, U32>
	{
		static BACnetResult Decode(const BACnetValue& value, U32 &backing)
		{
			return DecodeTime(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, bool backing)
		{
			return EncodeTime(value, backing);
		}
	};

	template<>
	struct Codec<ValueType_ObjectID, BACnetObjectID>
	{
		static BACnetResult Decode(const BACnetValue& value, BACnetObjectID &backing)
		{
			return DecodeObjectID(value, backing);
		}
		static BACnetResult Encode(BACnetValue& value, BACnetObjectID backing)
		{
			return EncodeObjectID(value, backing);
		}
	};

#pragma endregion

};

