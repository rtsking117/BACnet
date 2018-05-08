#include "BACnetApplication.h"
#include "BACnetValue.h"

BACnetValue::BACnetValue(bool IsRoot) : 
	Type(IsRoot ? ValueType_ParseRoot : ValueType_Null),
	Tag(NoTag),
	Flags(0)
{
	pv.DataLength = 0;
	pv.pData = nullptr;
	static_assert(sizeof(BACnetValue) == 32, "BACnetValue is not 32 bytes in size!");
	memset(Extra, 0, sizeof(Extra));
}

BACnetValue::BACnetValue(const BACnetValue & Other) : 
	Type(Other.Type),
	Tag(Other.Tag),
	Flags(Other.Flags)
{
	if(IsConstructedData())
	{
		cv.NumElements = Other.cv.NumElements;
		cv.pElements = new BACnetValue[cv.NumElements];
		for(U32 i = 0; i < Other.cv.NumElements; ++i)
		{
			cv.pElements[i] = Other.cv.pElements[i];
		}
	}
	else
	{
		pv.DataLength = Other.pv.DataLength;
		if(IsAllocatedInPlace())
		{
			pv.pData = Extra;
		}
		else
		{
			pv.pData = new U8[pv.DataLength];
		}
		memcpy(pv.pData, Other.pv.pData, pv.DataLength);
	}
}

BACnetValue::BACnetValue(BACnetValue && Other) :
	Type(Other.Type),
	Tag(Other.Tag),
	Flags(Other.Flags)
{
	if(IsConstructedData())
	{
		cv.pElements = Other.cv.pElements;
		Other.cv.pElements = nullptr;
		cv.NumElements = Other.cv.NumElements;
	}
	else
	{
		pv.DataLength = Other.pv.DataLength;
		if(IsAllocatedInPlace())
		{
			//This is actually less efficient.... 
			pv.pData = Extra;
			memcpy(pv.pData, Other.pv.pData, pv.DataLength);
		}
		else
		{
			pv.pData = Other.pv.pData;
			Other.pv.pData = nullptr;
		}
	}
}

BACnetValue::~BACnetValue()
{
	if(IsConstructedData())
	{
		if(cv.pElements)
		{
			delete[] cv.pElements;
			cv.pElements = nullptr;
		}
		cv.NumElements = 0;
	}
	else
	{
		if(pv.pData)
		{
			if(!IsAllocatedInPlace())
			{
				delete[] pv.pData;
			}
			pv.pData = nullptr;
		}
		pv.DataLength = 0;
		memset(Extra, 0, sizeof(Extra));
	}
	Type = ValueType_Null;
	Tag = 0;
	Flags = 0;
}

BACnetValue & BACnetValue::operator=(const BACnetValue & rhs)
{
	if(IsConstructedData() && cv.pElements)
	{
		delete[] cv.pElements;
	}
	else
	{
		if(pv.pData && !IsAllocatedInPlace())
		{
			delete[] pv.pData;
		}
	}
	Type = rhs.Type;
	Tag = rhs.Tag;
	Flags = rhs.Flags;
	if(IsConstructedData())
	{
		cv.NumElements = rhs.cv.NumElements;
		cv.pElements = new BACnetValue[cv.NumElements];
		for(U32 i = 0; i < rhs.cv.NumElements; ++i)
		{
			cv.pElements[i] = rhs.cv.pElements[i];
		}
	}
	else
	{
		pv.DataLength = rhs.pv.DataLength;
		if(IsAllocatedInPlace())
		{
			pv.pData = Extra;
		}
		else
		{
			pv.pData = new U8[pv.DataLength];
		}
		memcpy(pv.pData, rhs.pv.pData, pv.DataLength);
	}
	return *this;
}

BACnetValue & BACnetValue::operator=(BACnetValue && rhs)
{
	if(IsConstructedData() && cv.pElements)
	{
		delete[] cv.pElements;
	}
	else
	{
		if(pv.pData && !IsAllocatedInPlace())
		{
			delete[] pv.pData;
		}
	}
	Type = rhs.Type;
	Tag = rhs.Tag;
	Flags = rhs.Flags;
	if(IsConstructedData())
	{
		cv.pElements = rhs.cv.pElements;
		rhs.cv.pElements = nullptr;
		cv.NumElements = rhs.cv.NumElements;
	}
	else
	{
		pv.DataLength = rhs.pv.DataLength;
		if(IsAllocatedInPlace())
		{
			//This is actually less efficient.... 
			pv.pData = Extra;
			memcpy(pv.pData, rhs.pv.pData, pv.DataLength);
		}
		else
		{
			pv.pData = rhs.pv.pData;
			rhs.pv.pData = nullptr;
		}
	}
	return *this;
}

void BACnetValue::SetTag(U8 NewTag)
{
	if(IsPrimitiveData())
	{
		SetType(ValueType_ContextTagged);
	}
	Tag = NewTag;
}

void BACnetValue::SetType(BACnetValueType NewType)
{
	if(NewType == ValueType_Constructed && !IsConstructedData())
	{
		if(!IsAllocatedInPlace())
		{
			//need to delete the pointer.
			if(pv.pData)
			{
				delete[] pv.pData;
			}
		}
		else
		{
			memset(Extra, 0, sizeof(Extra));
		}
		pv.pData = nullptr;
		pv.DataLength = 0;
		Flags &= ~ValueFlag_AllocateInPlace;
	}
	else if(NewType != ValueType_Constructed && Type == ValueType_Constructed)
	{
		if(cv.pElements)
		{
			delete[] cv.pElements;
		}
		cv.pElements = nullptr;
		cv.NumElements = 0;
	}
	Type = NewType;
}

bool BACnetValue::IsValueValid() const
{
	if(IsConstructedData())
	{
		bool ret = ((Tag == NoTag) ^ (!IsParserRootElement()));
		ret &= !IsAllocatedInPlace();
		ret &= cv.NumElements >= 1;
		ret &= cv.pElements != nullptr;
		ret &= (U8*)cv.pElements != Extra;
		return ret;
	}
	else
	{
		bool ret = ((Tag == NoTag) ^ (!IsUntaggedData()));
		if(IsAllocatedInPlace())
		{
			ret &= pv.DataLength <= sizeof(Extra);
			ret &= pv.pData == Extra;
			return ret;
		}
		else
		{
			if(Type == ValueType_Null)
			{
				ret &= pv.DataLength == 0;
				ret &= pv.pData == nullptr;
				return ret;
			}
			else
			{
				ret &= pv.DataLength > sizeof(Extra);
				ret &= pv.pData != nullptr;
				ret &= pv.pData != Extra;
				return ret;
			}
		}
	}
}

bool BACnetValue::IsValueValidBACnet() const
{
	return IsValueValid() && !IsParserRootElement();
}

bool BACnetValue::IsValueTreeValid() const
{
	bool ret = IsValueValid();
	if(IsConstructedData())
	{
		for(U32 i = 0; i < GetNumElements(); ++i)
		{
			ret &= GetElement(i).IsValueTreeValid();
		}
	}
	return ret;
}

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

I64 BACnetValue::GetSignedValue(U32 Length, U32 ValueOffset) const
{
	if(IsConstructedData() || ValueOffset >= pv.DataLength) return 0;
	I64 Value;
	if(pv.pData[ValueOffset] & 0x80)
	{
		Value = -1;
	}
	else
	{
		Value = 0;
	}
	U32 maxlen = min(pv.DataLength, ValueOffset + Length);
	for(U32 i = ValueOffset; i < maxlen; ++i)
	{
		Value <<= 8;
		Value |= pv.pData[i];
	}
	return Value;
}

U64 BACnetValue::GetUnsignedValue(U32 Length, U32 ValueOffset) const
{
	if(IsConstructedData() || ValueOffset >= pv.DataLength) return 0;
	//start from ValueOffset and continue to NumBytes.
	U64 Value = 0;
	U32 maxlen = min(pv.DataLength, ValueOffset + Length);
	for(U32 i = ValueOffset; i < maxlen; ++i)
	{
		Value <<= 8;
		Value |= pv.pData[i];
	}
	return Value;
}

const void * const BACnetValue::GetBuffer(U32 BufferOffset) const
{
	if(BufferOffset >= pv.DataLength)
	{
		return nullptr;
	}
	return &pv.pData[BufferOffset];
}

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

void BACnetValue::SetSignedValue(I64 Value, U32 MinLength, U32 ValueOffset)
{
	//extract the minimum number of bytes needed to represent this number,
	//then compute the max between it and the MinLength.
	MinLength = max(MinLength, 1);
	U32 ComputedLength = sizeof(Value);
	U8 MatchVal = 0;
	U8 SignMatch = 0;
	if(Value < 0)
	{
		MatchVal = 0xFF;
		SignMatch = 0x80;
	}
	while(ComputedLength > MinLength)
	{
		U8 byte = (Value >> (8 * (ComputedLength - 1)) & 0xFF);
		if(byte == MatchVal)
		{
			--ComputedLength;
		}
		else
		{
			//detect an edge case of a number whos sign bit ends up separated from the numeric bits.
			// e.g 9 bit value 0b010001101 (0x08D) should be encoded in 2 bytes, but will be encoded as 1 byte 
			//signed value without this check, since the byte preceding the data is all zeros. This gets lopped 
			//off as a sign extension, but the resulting value is interpeted as negative, because the high bit 
			//of the encoded byte is 1. In order to preserve the sign, the value has to keep the zero bits in front.
			// above example is where the following happens:
			//
			//			Byte				
			//		-------------------------------------
			//		8	|	7	6	5	4	3	2	1	0
			//		0	|	1	0	0	0	1	1	0	1	
			//
			// Because the high two bits go from low to high, or inversely, if they go from high to low, 
			// the sign ends up separated from the numeric data. 
			if((Value & 0x80) != SignMatch)
			{
				++ComputedLength;
			}
			break;
		}
	}
	BACnetResult ret = ReserveBufferSpace(ValueOffset + ComputedLength); // ensure we have enough space to build stuff.
	if(BCE_SUCCEEDED(ret))
	{
		for(U32 i = 0; i < ComputedLength; ++i)
		{
			U8 byte = (Value >> (8 * (ComputedLength - (i + 1)))) & 0xFF;
			pv.pData[ValueOffset + i] = byte;
		}
	}
}

void BACnetValue::SetUnsignedValue(U64 Value, U32 MinLength, U32 ValueOffset)
{
	MinLength = max(MinLength, 1);
	U32 ComputedLength = sizeof(Value);
	while(ComputedLength > MinLength)
	{
		U8 byte = (Value >> (8 * (ComputedLength - 1)) & 0xFF);
		if(byte == 0)
		{
			--ComputedLength;
		}
		else
		{
			break;
		}
	}
	BACnetResult ret = ReserveBufferSpace(ValueOffset + ComputedLength); // ensure we have enough space to build stuff.
	if(BCE_SUCCEEDED(ret))
	{
		for(U32 i = 0; i < ComputedLength; ++i)
		{
			U8 byte = (Value >> (8 * (ComputedLength - (i + 1)))) & 0xFF;
			pv.pData[ValueOffset + i] = byte;
		}
	}
}

BACnetResult BACnetValue::ReserveBufferSpace(U32 ByteCount)
{
	if(ByteCount > pv.DataLength)
	{
		if(ByteCount > sizeof(Extra))
		{
			//move out of line.
			if(pv.DataLength)
			{
				U8* temp = new U8[ByteCount];
				memcpy(temp, pv.pData, pv.DataLength);
				if(!IsAllocatedInPlace())
				{
					delete[] pv.pData;
				}
				else
				{
					memset(Extra, 0, sizeof(Extra));
					//turn off allocate in place.
					Flags &= ~ValueFlag_AllocateInPlace;
				}
				pv.pData = temp;
			}
		}
		else
		{
			//keep inline.
			pv.DataLength = ByteCount;
			if(pv.pData == nullptr)
			{
				pv.pData = Extra;
				Flags |= ValueFlag_AllocateInPlace;
			}
		}
	}
	return BC_OK;
}

BACnetResult BACnetValue::WriteBuffer(const void * const Buffer, U32 BufferLength, U32 BufferOffset)
{
	BACnetResult ret = ReserveBufferSpace(BufferOffset + BufferLength);
	if(BCE_SUCCEEDED(ret))
	{
		memcpy(&pv.pData[BufferOffset], Buffer, BufferLength);
	}
	return ret;
}

const BACnetValue & BACnetValue::GetElement(U32 ElementIndex) const
{
	if(!IsConstructedData() || ElementIndex >= cv.NumElements)
	{
		return *this;
	}
	return cv.pElements[ElementIndex];
}

BACnetResult BACnetValue::AddValue(BACnetValue & val)
{
	if(cv.NumElements == 0)
	{
		cv.pElements = new BACnetValue[16];
	}
	else
	{
		U32 maxcount = (cv.NumElements & ~0x0F) + 16;
		if(pv.DataLength + 1 == maxcount)
		{
			//reallocate the buffer.
			if(maxcount > MAX_SUBVALUES)
			{
				return BCE_REJECT_BUFFER_OVERFLOW;
			}
			U32 newcount = maxcount + 16;
			BACnetValue* tbuf = cv.pElements;
			cv.pElements = new BACnetValue[newcount];
			//regions could be overlapping - use memmove, not memcpy.
			if(tbuf)
			{
				memmove(cv.pElements, tbuf, (cv.NumElements * sizeof(BACnetValue)));
			}
		}
	}
	cv.pElements[cv.NumElements] = val;
	++cv.NumElements;
	return BC_OK;
}

BACnetResult BACnetValue::ReserveValueSpace(U32 SubvalueCount)
{
	U32 maxcount = (cv.NumElements & ~0x0F) + 16;
	if(SubvalueCount > maxcount)
	{
		//reallocate the buffer.
		if(maxcount > MAX_SUBVALUES)
		{
			return BCE_REJECT_BUFFER_OVERFLOW;
		}
		U32 newcount = maxcount + 16;
		BACnetValue* tbuf = cv.pElements;
		cv.pElements = new BACnetValue[newcount];
		//regions could be overlapping - use memmove, not memcpy.
		if(tbuf)
		{
			memmove(cv.pElements, tbuf, (cv.NumElements * sizeof(BACnetValue)));
		}
	}
	return BC_OK;
}

BACNET_FORCEINLINE U8 ExtractTagFromTag(U8 tag) { return ((tag & 0xF0) >> 4); }
BACNET_FORCEINLINE U8 ExtractLVTFromTag(U8 tag) { return (tag & 0x07); }
BACNET_FORCEINLINE bool IsTagContextSpecific(U8 tag) { return (tag & 0x08) == 0x08; }

BACNET_FORCEINLINE void SetTagContextualBit(U8& tag, U8 BitValue) 
{ 
	tag &= 0xF7; 
	tag |= ((BitValue & 0x01) << 3); 
}

BACNET_FORCEINLINE void SetTagValueTag(U8& tag, U8 tagval) 
{ 
	tag &= 0x0F; 
	tag |= (tagval & 0x0F) << 4; 
}

BACNET_FORCEINLINE void SetTagLVT(U8& tag, U8 LVT) 
{ 
	tag &= 0xF8; 
	tag |= (LVT & 0x07); 
}

#define HR(x) do{ BACnetResult _r = (x); if(BCE_FAILED(_r)) { return _r;} }while(0)

BACnetResult BACnetValue::CreateFromBuffer(CObjectPtr<IBACnetBuffer> pBuffer, BACnetValue& val)
{
	//Read in the tag.
	U8 tag, lvt;
	pBuffer->ReadByte(tag);
	if(IsTagContextSpecific(tag))
	{
		//Context specific tag.
		//does the tag number have an extension?
		U8 RealTag = ExtractTagFromTag(tag);
		if(RealTag == 0b1111)
		{
			//tag is extended. 
			pBuffer->ReadByte(RealTag);
		}
		if(RealTag == 0xFF)
		{
			//invalid tag.
			return BCE_REJECT_INVALID_TAG;
		}
		val.Tag = RealTag;
		lvt = ExtractLVTFromTag(tag);
		if(lvt == 0b110)
		{
			//Opening tag, Constructed Data.
			val.Type = ValueType_Constructed;
			//init some data
			val.cv.NumElements= 0;
			val.cv.pElements = nullptr;
			BACnetValue subval;
			BACnetResult r = BC_OK;
			while(1)
			{
				HR(r = CreateFromBuffer(pBuffer, subval));
				if(r >= BCS_CLOSING_TAG_0 && r <= BCS_CLOSING_TAG_255)
				{
					//end tag.
					//check it.
					if((r - BCS_CLOSING_TAG_0) != RealTag)
					{
						//Tag is mismatched - open and close tags should have matching tag numbers.
						return BCE_REJECT_INVALID_TAG;
					}
					break;
				}
				//we got a value. add it.
				HR(val.AddValue(subval));
			}
			return BC_OK;
		}
		else if(lvt == 0b111)
		{
			//closing tag. 
			return BCS_CLOSING_TAG_0 + RealTag;
		}
		else
		{
			//its a length.
			val.Type = ValueType_ContextTagged;
		}
	}
	else
	{
		//application tag.
		val.Type = (BACnetValueType)ExtractTagFromTag(tag);
		if(val.Type > ValueType_ObjectID)
		{
			return BCE_REJECT_INVALID_TAG;
		}
		lvt = ExtractLVTFromTag(tag);
	}
	if(val.Type == ValueType_Boolean)
	{
		//lvt is a value!
		val.Flags |= ValueFlag_AllocateInPlace;
		val.pv.DataLength = 1;
		val.pv.pData = val.Extra;
		if(lvt == 0b001)
		{
			val.pv.pData[0] = 1;
		}
		else
		{
			val.pv.pData[0] = 0;
		}
	}
	else
	{
		if(lvt == 0b101)
		{
			//length extension.
			U8 LenExt;
			pBuffer->ReadByte(LenExt);
			if(LenExt == 0xFE)
			{
				U16 len;
				pBuffer->ReadShort(len, true);
				val.pv.DataLength = len;
			}
			else if(LenExt == 0xFF)
			{
				pBuffer->ReadInt(val.pv.DataLength, true);
			}
			else
			{
				val.pv.DataLength = LenExt;
			}
		}
		else
		{
			val.pv.DataLength = lvt;
		}
		if(val.pv.DataLength)
		{
			if(val.pv.DataLength <= sizeof(val.Extra))
			{
				val.Flags |= ValueFlag_AllocateInPlace;
				val.pv.pData = val.Extra;
			}
			else
			{
				val.pv.pData = new U8[val.pv.DataLength];
			}
			pBuffer->Read(val.pv.DataLength, val.pv.pData);
		}
	}
	return BC_OK;
}

BACnetResult BACnetValue::WriteToBuffer(CObjectPtr<IBACnetBuffer> pBuffer, const BACnetValue & val)
{
	//Build the ASN.1 Tag.
	U8 Tag = 0;
	//4 bits Tag, 1 bit context, 3 bits LVT
	//is the value application data?
	if(val.IsPrimitiveData())
	{
		if(val.IsContextTaggedData())
		{
			if(val.Tag == NoTag)
			{
				//umm....
				return BCE_REJECT_INVALID_TAG;
			}
			SetTagContextualBit(Tag, 1);
			if(val.Tag < 15)
			{
				//push into the tag field.
				SetTagValueTag(Tag, val.Tag);
			}
			else
			{
				//needs extension.
				SetTagValueTag(Tag, 0b1111);
			}
		}
		else
		{
			SetTagContextualBit(Tag, 0);
			SetTagValueTag(Tag, val.Type);
			if(val.Type == ValueType_Boolean)
			{
				//Encode the value into the LVT.
				SetTagLVT(Tag, val.pv.pData[0]);
				//now write the tag and return.
				return pBuffer->WriteByte(Tag);
			}
		}
		U32 sz = val.GetDataLength();
		if((sz < 5))
		{
			//standard.
			SetTagLVT(Tag, (U8)sz);
		}
		else
		{
			//extended.
			SetTagLVT(Tag, 0b101);
		}
		HR(pBuffer->WriteByte(Tag));
		if(IsTagContextSpecific(Tag) && val.Tag >= 15)
		{
			//Tag extension.
			HR(pBuffer->WriteByte(val.Tag)); 
		}
		if(sz >= 5)
		{
			//extended length.
			if(sz < 0xFE)
			{
				//1 byte.
				HR(pBuffer->WriteByte((U8)sz));
			}
			else if(sz < 0xFFFF)
			{
				//2 bytes.
				HR(pBuffer->WriteByte(0xFE));
				HR(pBuffer->WriteShort((U16)sz, true));
			}
			else
			{
				//4 bytes.
				HR(pBuffer->WriteByte(0xFF));
				HR(pBuffer->WriteInt(sz, true));
			}
		}
		//now the data.
		return pBuffer->Write(val.pv.DataLength, val.pv.pData);
	}
	else
	{
		if(val.Tag == NoTag)
		{
			//umm....
			return BCE_REJECT_INVALID_TAG;
		}
		SetTagContextualBit(Tag, 1);
		if(val.Tag < 15)
		{
			//push into the tag field.
			SetTagValueTag(Tag, val.Tag);
		}
		else
		{
			//needs extension.
			SetTagValueTag(Tag, 0b1111);
		}
		//Open tag.
		SetTagLVT(Tag, 0b110);
		HR(pBuffer->WriteByte(Tag));
		if(val.Tag >= 15)
		{
			//Tag extension.
			HR(pBuffer->WriteByte(val.Tag));
		}
		//Now output each subvalue in turn.
		for(U32 i = 0; i < val.GetNumElements(); ++i)
		{
			HR(WriteToBuffer(pBuffer, val.GetElement(i)));
		}
		SetTagLVT(Tag, 0b111);
		HR(pBuffer->WriteByte(Tag));
		if(val.Tag >= 15)
		{
			//Tag extension.
			HR(pBuffer->WriteByte(val.Tag));
		}
	}
	return BC_OK;
}

