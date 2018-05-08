#pragma once

#include "BACnetTypes.h"

class BACNET_ENTRYPOINT BACnetString final
{
	struct BACnetStringImpl* pImpl;

	BACnetString(size_t);

public:
	BACnetString();
	explicit BACnetString(const char* pStringLiteral);
	explicit BACnetString(const wchar_t* pWideStringLiteral);
	BACnetString(const BACnetString& Other);
	BACnetString(BACnetString&& Other);
	~BACnetString();

	size_t length() const;
	size_t size() const;
	size_t bytes() const;
	size_t capacity() const;
	void* buffer() const;
	void resize(size_t NewSize);
	void clear();

	void reverse();

	class BACNET_EXPORT iterator final
	{
		friend class BACnetString;
	private:
		void* pDataPtr;
		size_t uiOffset;
	public:
		iterator();
		iterator(const iterator& Other);
		iterator(iterator&& Other);
		~iterator();

		iterator& operator=(const iterator& Other);
		iterator& operator=(iterator&& Other);
		int operator*();
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		iterator& operator+=(size_t Offset);
		iterator operator+(size_t Offset);
		iterator& operator-=(size_t Offset);
		iterator operator-(size_t Offset);
		bool is_null() const;
		bool operator==(iterator Other);
		bool operator!=(iterator Other);
		bool operator<(iterator Other);
		bool operator>(iterator Other);
		bool operator>=(iterator Other);
		bool operator<=(iterator Other);
	};

	iterator begin() const;
	iterator end() const;

	BACnetString& operator=(const BACnetString& Other);
	BACnetString& operator=(BACnetString&& Other);
	BACnetString& operator=(const char* Other);
	BACnetString& operator=(const wchar_t* Other);

	BACnetString operator+(const BACnetString& Other) const;
	BACnetString operator+(BACnetString&& Other) const;
	BACnetString operator+(const char* Other) const;
	BACnetString operator+(const wchar_t* Other);

	BACnetString& operator+=(const BACnetString& Other);
	BACnetString& operator+=(BACnetString&& Other);
	BACnetString& operator+=(const char* Other);
	BACnetString& operator+=(const wchar_t* Other);

	size_t AsWideString(wchar_t* String, size_t Size) const;	
	size_t AsCString(char* String, size_t Size) const;
	size_t AsUTF8(U8* String, size_t Size) const;
	size_t AsUTF16(U16* String, size_t Size) const;
	size_t AsUTF32(U32* String, size_t Size) const;

	I32 ParseInt(size_t Start = 0, iterator* End = nullptr, U8 NumericBase = 0) const;
	I32 ParseInt(iterator Start, iterator* End = nullptr, U8 NumericBase = 0) const;
	U32 ParseUInt(size_t Start = 0, iterator* End = nullptr, U8 NumericBase = 0) const;
	U32 ParseUInt(iterator Start, iterator* End = nullptr, U8 NumericBase = 0) const;
	I64 ParseInt64(size_t Start = 0, iterator* End = nullptr, U8 NumericBase = 0) const;
	I64 ParseInt64(iterator Start, iterator* End = nullptr, U8 NumericBase = 0) const;
	U64 ParseUInt64(size_t Start = 0, iterator* End = nullptr, U8 NumericBase = 0) const;
	U64 ParseUInt64(iterator Start, iterator* End = nullptr, U8 NumericBase = 0) const;
	float ParseFloat(size_t Start = 0, iterator* End = nullptr) const;
	float ParseFloat(iterator Start, iterator* End = nullptr) const;
	double ParseDouble(size_t Start = 0, iterator* End = nullptr) const;
	double ParseDouble(iterator Start, iterator* End = nullptr) const;

	static BACnetString ToString(I32 iValue, I32 Base = 10);
	static BACnetString ToString(U32 uiValue, I32 Base = 10);
	static BACnetString ToString(I64 llValue, I32 Base = 10);
	static BACnetString ToString(U64 ullValue, I32 Base = 10);
	static BACnetString ToString(float fValue);
	static BACnetString ToString(double dValue);

	static BACnetString FromUTF8(const U8* source);
	static BACnetString FromUTF16(const U16* source);
	static BACnetString FromUTF32(const U32* source);
	static BACnetString FromWindows1252(const U8* source);
	static BACnetString FromISO8859(const U8* source);
	static BACnetString FromUCS2(const U16* source);
	static BACnetString FromUCS4(const U32* source);

};


