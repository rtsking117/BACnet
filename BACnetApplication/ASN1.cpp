#include "BasicASN1.h"

/*
Tagging rules:

Tag byte
Tag Extenstion
Length extension
Data

*/

BACnetResult ASN1::Decode(CObjectPtr<IBACnetBuffer> pData, BACnetValue& sp)
{
	sp.SetType(ValueType_ParseRoot);
	sp.SetTag(NoTag);
	while(pData->GetRemainingSize() > 0)
	{
		BACnetValue temp;
		BACnetResult r = BACnetValue::CreateFromBuffer(pData, temp);
		if(BCE_FAILED(r))
		{
			return r;
		}
		if(r >= BCS_CLOSING_TAG_0 && r <= BCS_CLOSING_TAG_255)
		{
			//unmatched end tag!
			return BCE_REJECT_INVALID_TAG;
		}
		sp.AddValue(temp);
	}
	return BC_OK;
}

BACnetResult ASN1::Encode(CObjectPtr<IBACnetBuffer> pData, const BACnetValue & Params)
{
	BACnetResult r = BC_OK;
	if(Params.IsParserRootElement())
	{
		//this element itself is not supposed to be in the data stream, just its children.
		//go over each and encode them in turn.
		for(U32 i = 0; i < Params.GetNumElements(); ++i)
		{
			BACnetValue v = Params.GetElement(i);
			r = BACnetValue::WriteToBuffer(pData,Params.GetElement(i));
			if(BCE_FAILED(r))
			{
				break;
			}
		}
	}
	else
	{
		//Encode the element directly.
		r = BACnetValue::WriteToBuffer(pData, Params);
	}
	return r;
}

BACnetResult ASN1::DecodeBoolean(const BACnetValue &v, bool & Value)
{
	if((v.GetType() == ValueType_Boolean) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() != 1)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (v.GetUnsignedValue() != 0);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult BACNETAPP_ENTRYPOINT ASN1::DecodeUnsigned8(const BACnetValue & v, U8 & Value)
{
	if ((v.GetType() == ValueType_Unsigned) || (v.GetType() == ValueType_ContextTagged))
	{
		if (!(v.GetDataLength() <= 1))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (U8)v.GetUnsignedValue(1);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeUnsigned16(const BACnetValue &v, U16 & Value)
{
	if((v.GetType() == ValueType_Unsigned) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 2))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (U16)v.GetUnsignedValue(2);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeUnsigned32(const BACnetValue &v, U32 & Value)
{
	if((v.GetType() == ValueType_Unsigned) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 4))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (U32)v.GetUnsignedValue(4);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeUnsigned64(const BACnetValue &v, U64 & Value)
{
	if((v.GetType() == ValueType_Unsigned) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 8))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = v.GetUnsignedValue();
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult BACNETAPP_ENTRYPOINT ASN1::DecodeSigned8(const BACnetValue & v, I8 & Value)
{
	if ((v.GetType() == ValueType_Signed) || (v.GetType() == ValueType_ContextTagged))
	{
		if (!(v.GetDataLength() <= 1))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (I8)v.GetSignedValue(1);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeSigned16(const BACnetValue &v, I16 & Value)
{
	if((v.GetType() == ValueType_Signed) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 2))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (I16)v.GetSignedValue(2);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeSigned32(const BACnetValue &v, I32 & Value)
{
	if((v.GetType() == ValueType_Signed) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 4))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (I32)v.GetSignedValue(4);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeSigned64(const BACnetValue &v, I64 & Value)
{
	if((v.GetType() == ValueType_Signed) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 8))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = v.GetSignedValue();
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeReal(const BACnetValue &v, float & Value)
{
	if((v.GetType() == ValueType_Real) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() != 4)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		struct floatstr
		{
			float f;
			U32 u;
		} fv = { 0 };
		fv.u = (U32)v.GetUnsignedValue(4);
		Value = fv.f;
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeDouble(const BACnetValue &v, double & Value)
{
	if((v.GetType() == ValueType_Double) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() != 8)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		struct floatstr
		{
			double f;
			U64 u;
		} fv = { 0 };
		fv.u = v.GetUnsignedValue(4);
		Value = fv.f;
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeOctetString(const BACnetValue &v, BACnetByteString& Value)
{
	if((v.GetType() == ValueType_OctetString) || (v.GetType() == ValueType_ContextTagged))
	{
		Value = BACnetByteString(v.GetBuffer(), v.GetDataLength());
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeCharacterString(const BACnetValue &v, BACnetString& Value)
{
	if((v.GetType() == ValueType_CharacterString) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() < 1)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		//pull first byte
		U8 encoding = (U8)v.GetUnsignedValue(1);
		switch(encoding)
		{
		case 0:
			//UTF-8
			Value = BACnetString::FromUTF8((U8*)v.GetBuffer(1));
			break;
			//rest of these need conversion!
		case 1:
			//DBCS
		case 2:
			//JIS X 0208
			break;
		case 5:
			//ISO 8859-1
			Value = BACnetString::FromISO8859((U8*)v.GetBuffer(1));
			break;
		case 3:
			//UCS-4
			Value = BACnetString::FromUCS4((U32*)v.GetBuffer(1));
			break;
		case 4:
			//UCS-2
			Value = BACnetString::FromUCS2((U16*)v.GetBuffer(1));
			break;
		}
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeBitString(const BACnetValue &v, BACnetBitString &Value)
{
	if((v.GetType() == ValueType_BitString) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() < 1)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		//pull first byte
		U32 BitLength = ((v.GetDataLength() - 1) * 8) - ((U8)v.GetUnsignedValue(1));
		if(BitLength)
		{
			Value = BACnetBitString(v.GetBuffer(1), BitLength);
		}
		else
		{
			Value = BACnetBitString(nullptr, 0);
		}
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeEnumerated(const BACnetValue &v, U32 & Value)
{
	if((v.GetType() == ValueType_Enumerated) || (v.GetType() == ValueType_ContextTagged))
	{
		if(!(v.GetDataLength() <= 4))
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (U32)v.GetUnsignedValue(4);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeDate(const BACnetValue &v, U32 & Value)
{
	if((v.GetType() == ValueType_Date) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() != 4)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (U32)v.GetUnsignedValue(4);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeTime(const BACnetValue &v, U32 & Value)
{
	if((v.GetType() == ValueType_Time) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() != 4)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (U32)v.GetUnsignedValue(4);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::DecodeObjectID(const BACnetValue &v, BACnetObjectID & Value)
{
	if((v.GetType() == ValueType_ObjectID) || (v.GetType() == ValueType_ContextTagged))
	{
		if(v.GetDataLength() != 4)
		{
			return BCE_REJECT_PARAMETER_OUT_OF_RANGE;
		}
		Value = (BACnetObjectID)v.GetUnsignedValue(4);
		return BC_OK;
	}
	else
	{
		return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
	}
}

BACnetResult ASN1::EncodeNull(BACnetValue & v)
{
	v.SetType(ValueType_Null);
	return BC_OK;
}

BACnetResult ASN1::EncodeBoolean(BACnetValue & v, bool Value)
{
	v.SetType(ValueType_Boolean);
	v.SetUnsignedValue(Value == true ? 0x01 : 0x00);
	return BC_OK;
}

BACnetResult BACNETAPP_ENTRYPOINT ASN1::EncodeUnsigned8(BACnetValue & v, U8 Value)
{
	v.SetType(ValueType_Unsigned);
	v.SetUnsignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeUnsigned16(BACnetValue & v, U16 Value)
{
	v.SetType(ValueType_Unsigned);
	v.SetUnsignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeUnsigned32(BACnetValue & v, U32 Value)
{
	v.SetType(ValueType_Unsigned);
	v.SetUnsignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeUnsigned64(BACnetValue & v, U64 Value)
{
	v.SetType(ValueType_Unsigned);
	v.SetUnsignedValue(Value);
	return BC_OK;
}

BACnetResult BACNETAPP_ENTRYPOINT ASN1::EncodeSigned8(BACnetValue & v, I8 Value)
{
	v.SetType(ValueType_Signed);
	v.SetSignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeSigned16(BACnetValue & v, I16 Value)
{
	v.SetType(ValueType_Signed);
	v.SetSignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeSigned32(BACnetValue & v, I32 Value)
{
	v.SetType(ValueType_Signed);
	v.SetSignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeSigned64(BACnetValue & v, I64 Value)
{
	v.SetType(ValueType_Signed);
	v.SetSignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeReal(BACnetValue & v, float Value)
{
	v.SetType(ValueType_Real);
	union floatstruct
	{
		float f;
		U32 u;
	} f;
	static_assert(sizeof(float) == sizeof(U32), "float is not the IEEE 754 binary32 type");
	//copy the bit pattern.
	f.f = Value;
	v.SetUnsignedValue(f.u, sizeof(U32));
	return BC_OK;
}

BACnetResult ASN1::EncodeDouble(BACnetValue & v, double Value)
{
	v.SetType(ValueType_Double);
	union floatstruct
	{
		double f;
		U64 u;
	} f;
	static_assert(sizeof(double) == sizeof(U64), "double is not the IEEE 754 binary64 type");
	//copy the bit pattern.
	f.f = Value;
	v.SetUnsignedValue(f.u, sizeof(U64));
	return BC_OK;
}

BACnetResult ASN1::EncodeOctetString(BACnetValue & v, const BACnetByteString & Value)
{
	v.SetType(ValueType_OctetString);
	BACnetResult r = v.ReserveBufferSpace((U32)Value.size());
	if(BCE_SUCCEEDED(r))
	{
		r = v.WriteBuffer(Value.buffer(), (U32)Value.size());
	}
	return r;
}

BACnetResult ASN1::EncodeCharacterString(BACnetValue & v, const BACnetString & Value)
{
	v.SetType(ValueType_OctetString);
	BACnetResult r = v.ReserveBufferSpace((U32)Value.bytes() + 1); //Encoding byte
	if(BCE_SUCCEEDED(r))
	{
		v.SetUnsignedValue(0x00);
		size_t len = Value.AsUTF8(nullptr, 0);
		U8* string = new U8[len];
		Value.AsUTF8(string, len);
		r = v.WriteBuffer(string, (U32)len, 1);
		delete[] string;
	}
	return r;
}

BACnetResult ASN1::EncodeBitString(BACnetValue & v, const BACnetBitString & Value)
{
	v.SetType(ValueType_OctetString);
	BACnetResult r = v.ReserveBufferSpace((U32)Value.size() + 1);
	if(BCE_SUCCEEDED(r))
	{
		//compute the number of bits not used at the end.
		U8 NumBitsExtra = (U8)((Value.bytes() * 8) - Value.length());
		v.SetUnsignedValue(NumBitsExtra);
		if(Value.size() != 0)
		{
			r = v.WriteBuffer(Value.buffer(), (U32)Value.size(), 1);
		}
	}
	return r;
}

BACnetResult ASN1::EncodeEnumerated(BACnetValue & v, U32 Value)
{
	v.SetType(ValueType_Enumerated);
	v.SetUnsignedValue(Value);
	return BC_OK;
}

BACnetResult ASN1::EncodeDate(BACnetValue & v, U32 Value)
{
	v.SetType(ValueType_Date);
	v.SetUnsignedValue(Value, sizeof(U32));
	return BC_OK;
}

BACnetResult ASN1::EncodeTime(BACnetValue & v, U32 Value)
{
	v.SetType(ValueType_Time);
	v.SetUnsignedValue(Value, sizeof(U32));
	return BC_OK;
}

BACnetResult ASN1::EncodeObjectID(BACnetValue & v, BACnetObjectID Value)
{
	v.SetType(ValueType_ObjectID);
	v.SetUnsignedValue(Value, sizeof(U32));
	return BC_OK;
}
