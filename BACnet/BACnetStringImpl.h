#pragma once

#include "BACnetString.h"
#include "Unicode.h"
#include "UTF8.h"
#include "UTF16.h"
#include "ISO 8859-1.h"
#include <memory>

struct BACnetStringImpl
{
	//CODEUNIT array.
	U16* str;
	//number of CODEUNIT allocated in str.
	size_t bytes;
	//number of CODEUNIT used for CODEPOINTS in str.
	size_t size;
	//number of CODEPOINTS present in str.
	size_t length;

	BACnetStringImpl() : str(nullptr), bytes(0), size(0), length(0) {}
	BACnetStringImpl(size_t LiteralSize) : str(new U16[LiteralSize + 1]), bytes(LiteralSize + 1), size(0), length(0)
	{
		memset(str, 0, (bytes << 1));
	}
	BACnetStringImpl(const BACnetStringImpl& rhs) : str(new U16[rhs.bytes]), bytes(rhs.bytes), size(rhs.size), length(rhs.length)
	{
		memset(str, 0, (bytes << 1));
		memcpy(str, rhs.str, (size << 1));
	}
	BACnetStringImpl(BACnetStringImpl&& rhs) : str(rhs.str), bytes(rhs.bytes), size(rhs.size), length(rhs.length) { rhs.str = nullptr; }
	~BACnetStringImpl()
	{
		if(str)
		{
			delete[] str;
		}
		str = nullptr;
		bytes = length = size = 0;
	}
};



void CopyUnicodeLiteral16(BACnetStringImpl* const s, const U16 * const l);

void CopyUnicodeLiteral32(BACnetStringImpl* const s, const U32 * const l);

void CopyCharLiteral(BACnetStringImpl* const s, const char* const l, bool isISO = false);

void CopyUnicodeLiteral(BACnetStringImpl* const s, const wchar_t* const l);

size_t ComputeSizeAsUTF8(const BACnetStringImpl* const s);

size_t ConvertToUTF8(const BACnetStringImpl * const s, U8* const str, size_t slen);

size_t ConvertToUTF32(const BACnetStringImpl* const s, U32* const str, size_t slen);