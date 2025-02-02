#pragma once

class BACnetValue;

#include "BACnetApplication.h"

#define MAX_SUBVALUES 256

enum BACnetValueType : U8
{
	ValueType_Null,
	ValueType_Boolean,
	ValueType_Unsigned,
	ValueType_Signed,
	ValueType_Real,
	ValueType_Float = ValueType_Real,
	ValueType_Double,
	ValueType_OctetString,
	ValueType_CharacterString,
	ValueType_BitString,
	ValueType_Enumerated,
	ValueType_Date,
	ValueType_Time,
	ValueType_ObjectID,
	ValueType_ContextTagged = 16,
	ValueType_Constructed,
	ValueType_ParseRoot,

	ValueType_NotSet = 0xFF,
};

enum BACnetValueFlags
{
	ValueFlag_AllocateInPlace = 0x01,
};

class BACNETAPP_ENTRYPOINT BACnetValue final
{
	BACnetValueType Type;
	U8 Tag;
	U8 Flags;
	U8 Padding;
	union
	{
#pragma pack(push)
#pragma pack(1)
		struct PrimitiveValue
		{
			U32 DataLength;
			U8* pData;
		} pv;
		struct ConstructedValue
		{
			U32 NumElements;
			BACnetValue* pElements;
		} cv;
#pragma pack(pop)
	};
	U8 Extra[24 - sizeof(void*)];

public:
	BACnetValue(bool IsRoot = false);
	BACnetValue(const BACnetValue& Other);
	BACnetValue(BACnetValue&& Other);
	~BACnetValue();

	BACnetValue& operator=(const BACnetValue& rhs);
	BACnetValue& operator=(BACnetValue&& rhs);

	U8 GetTag() const { return Tag; }
	void SetTag(U8 NewTag);
	BACnetValueType GetType() const { return Type; }
	void SetType(BACnetValueType NewType);
	U8 GetFlags() const { return Flags; }
	bool IsValueValid() const;
	bool IsValueValidBACnet() const;
	bool IsValueTreeValid() const;
	bool IsUntaggedData() const { return Type < ValueType_ContextTagged; }
	bool IsContextTaggedData() const { return Type == ValueType_ContextTagged; }
	bool IsPrimitiveData() const { return Type < ValueType_Constructed; }
	bool IsConstructedData() const { return Type >= ValueType_Constructed && Type != ValueType_NotSet; }
	bool IsParserRootElement() const { return Type == ValueType_ParseRoot; }
	bool IsUninitialized() const { return Type == ValueType_NotSet; }
	bool IsAllocatedInPlace() const { return (Flags & ValueFlag_AllocateInPlace); }

	U32 GetDataLength() const { return IsPrimitiveData() ? pv.DataLength : 0; }
	I64 GetSignedValue(U32 MaxLength = sizeof(I64), U32 ValueOffset = 0) const;
	U64 GetUnsignedValue(U32 MaxLength = sizeof(U64), U32 ValueOffset = 0) const;
	const void* const GetBuffer(U32 BufferOffset = 0) const;

	void SetSignedValue(I64 Value, U32 MinLength = 0, U32 ValueOffset = 0);
	void SetUnsignedValue(U64 Value, U32 MinLength = 0, U32 ValueOffset = 0);
	BACnetResult ReserveBufferSpace(U32 ByteCount);
	BACnetResult WriteBuffer(const void* const Buffer, U32 BufferLength, U32 BufferOffset = 0);

	U32 GetNumElements() const { return IsConstructedData() ? cv.NumElements : 0; }
	const BACnetValue& GetElement(U32 ElementIndex) const;

	BACnetResult AddValue(const BACnetValue& val);
	BACnetResult ReserveValueSpace(U32 SubvalueCount);

	static BACnetResult CreateFromBuffer(CObjectPtr<IBACnetBuffer> pBuffer, BACnetValue& val);
	static BACnetResult WriteToBuffer(CObjectPtr<IBACnetBuffer> pBuffer, const BACnetValue& val);
};