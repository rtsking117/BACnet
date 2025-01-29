#include "BACnetString.h"
#include "BACnetStringImpl.h"
#include <memory>

BACnetString::BACnetString(size_t size) :
	pImpl(new BACnetStringImpl(size))
{
}


BACnetString::BACnetString():
	pImpl(new BACnetStringImpl())
{
}

BACnetString::BACnetString(const char * pStringLiteral):
	pImpl(new BACnetStringImpl())
{
	CopyCharLiteral(pImpl, pStringLiteral);
}

BACnetString::BACnetString(const wchar_t * pWideStringLiteral):
	pImpl(new BACnetStringImpl())
{
	CopyUnicodeLiteral(pImpl, pWideStringLiteral);
}

BACnetString::BACnetString(const BACnetString & Other):
	pImpl(new BACnetStringImpl(*Other.pImpl))
{
}

BACnetString::BACnetString(BACnetString && Other):
	pImpl(std::move(Other.pImpl))
{
	Other.pImpl = nullptr;
}

BACnetString::~BACnetString()
{
	if(pImpl)
	{
		delete pImpl;
		pImpl = nullptr;
	}
}

size_t BACnetString::length() const
{
	return pImpl->length;
}

size_t BACnetString::size() const
{
	return pImpl->size;
}

size_t BACnetString::bytes() const
{
	return (pImpl->size << 1);
}

size_t BACnetString::capacity() const
{
	return pImpl->bytes;
}

void* BACnetString::buffer() const
{
	return pImpl->str;
}

void BACnetString::resize(size_t NewSize)
{
	if(NewSize < pImpl->bytes)
	{
		return;
	}
	pImpl->bytes = NewSize;
	U16* newstr = new U16[pImpl->bytes];
	memcpy(newstr, pImpl->str, (pImpl->size << 1));
	newstr[pImpl->size] = 0;
	delete[] pImpl->str;
	pImpl->str = newstr;
}

void BACnetString::clear()
{
	memset(pImpl->str, 0, (pImpl->bytes << 1));
	pImpl->size = pImpl->length = 0;
}

void ReverseString(BACnetStringImpl* pImpl)
{
	/*
	 23ab34firur34nn23mi12mmj
	 jmm21im32nn43rurif43ba32
	 mj2mi13mn24nr3rufi34ab23
	 reverse the bytes, then reverse the pairs.
	*/
	//if one of them is a low surrogate, do the second option
	bool secondpass = false;
	for(size_t i = 0, j = pImpl->size - 1; i < j; ++i, --j)
	{
		if(IsHighSurrogate(pImpl->str[i]) || IsHighSurrogate(pImpl->str[j]))
		{
			secondpass = true;
		}
		std::swap(pImpl->str[i], pImpl->str[j]);
	}
	if(secondpass)
	{
		for(size_t i = 0; i < pImpl->size; ++i)
		{
			if(IsLowSurrogate(pImpl->str[i]))
			{
				std::swap(pImpl->str[i], pImpl->str[i + 1]);
			}
		}
	}
}

void BACnetString::reverse()
{
	ReverseString(pImpl);
}

BACnetString::iterator BACnetString::begin() const
{
	iterator ret;
	ret.pDataPtr = pImpl->str;
	ret.uiOffset = 0;
	return ret;
}

BACnetString::iterator BACnetString::end() const
{
	iterator ret;
	ret.pDataPtr = pImpl->str;
	ret.uiOffset = pImpl->size;
	return ret;
}

BACnetString & BACnetString::operator=(const BACnetString & Other)
{
	if(pImpl->str)
	{
		delete[] pImpl->str;
	}
	pImpl->bytes = Other.pImpl->bytes;
	pImpl->size = Other.pImpl->size;
	pImpl->length = Other.pImpl->length;
	pImpl->str = new U16[pImpl->bytes];
	memcpy(pImpl->str, Other.pImpl->str, (pImpl->size << 1));
	return *this;
}

BACnetString & BACnetString::operator=(BACnetString && Other)
{
	std::swap(pImpl, Other.pImpl);
	return *this;
}

BACnetString & BACnetString::operator=(const char * Other)
{
	if(pImpl->str)
	{
		delete[] pImpl->str;
	}
	CopyCharLiteral(pImpl, Other);
	return *this;
}

BACnetString & BACnetString::operator=(const wchar_t * Other)
{
	if(pImpl->str)
	{
		delete[] pImpl->str;
	}
	CopyUnicodeLiteral(pImpl, Other);
	return *this;
}

BACnetString BACnetString::operator+(const BACnetString & Other) const
{
	return BACnetString(*this) += Other;
}

BACnetString BACnetString::operator+(BACnetString && Other) const
{
	return BACnetString(*this) += Other;
}

BACnetString BACnetString::operator+(const char * Other) const
{
	return BACnetString(*this) += Other;
}

BACnetString BACnetString::operator+(const wchar_t * Other)
{
	return BACnetString(*this) += Other;
}

BACnetString & BACnetString::operator+=(const BACnetString & Other)
{
	resize(pImpl->size + Other.pImpl->size + 1);
	memcpy(pImpl->str + pImpl->size, Other.pImpl->str, (Other.pImpl->size << 1));
	pImpl->size += Other.pImpl->size;
	pImpl->length += Other.pImpl->length;
	pImpl->str[pImpl->size] = 0;
	return *this;
}

BACnetString & BACnetString::operator+=(BACnetString && Other)
{
	resize(pImpl->size + Other.pImpl->size + 1);
	memcpy(pImpl->str + pImpl->size, Other.pImpl->str, (Other.pImpl->size << 1));
	pImpl->size += Other.pImpl->size;
	pImpl->length += Other.pImpl->length;
	pImpl->str[pImpl->size] = 0;
	return *this;
}

BACnetString & BACnetString::operator+=(const char * Other)
{
	BACnetString str(Other);
	return *this += str;
}

BACnetString & BACnetString::operator+=(const wchar_t * Other)
{
	BACnetString str(Other);
	return *this += str;
}

size_t BACnetString::AsWideString(wchar_t* String, size_t Size) const
{
	return sizeof(wchar_t) == 2 ? AsUTF16((U16*)String, Size) : AsUTF32((U32*)String, Size);
}

size_t BACnetString::AsCString(char* String, size_t Size) const
{
	return AsUTF8((U8*)String, Size);
}

size_t BACnetString::AsUTF8(U8* String, size_t Size) const
{
	size_t RequiredSize = ComputeSizeAsUTF8(pImpl) + 1;
	if(String && Size >= RequiredSize)
	{
		size_t index = ConvertToUTF8(pImpl, String, Size);
		if(String[index] != 0)
		{
			//we broke something here - FIX IT.
			__debugbreak();
		}
	}
	return RequiredSize;
}

size_t BACnetString::AsUTF16(U16* String, size_t Size) const
{
	if(String && Size >= pImpl->size + 1)
	{
		memcpy(String, pImpl->str, pImpl->size * 2);
		String[pImpl->size] = 0;
	}
	return pImpl->size + 1;
}

size_t BACnetString::AsUTF32(U32* String, size_t Size) const
{
	if(String && Size >= pImpl->length + 1)
	{
		size_t index = ConvertToUTF32(pImpl, String, Size);
		if(String[index] != 0)
		{
			//we broke something here - FIX IT.
			__debugbreak();
		}
	}
	return pImpl->length + 1;
}

#pragma region String to integer conversion

template<typename T,
	typename UT = std::make_unsigned_t<T>>
	T ParseIntVal(BACnetString::iterator cp, BACnetString::iterator* end, U8 NumericBase)
{
	//initialize the ending index.
	if(end)*end = cp;
	if(cp.is_null())
	{
		return 0;
	}
	//Now strip off all whitespace characters from the start.
	while(!cp.is_null() && IsWhitespace(*cp))
	{
		++cp;
	}
	if(NumericBase == 0)
	{
		//Auto detect. is the first char a zero?
		if(*cp == '0')
		{
			++cp;
			//did we go past the length?
			if(cp.is_null())
			{
				//yes. Therefore the value is a zero.
				if(end)*end = cp;
				return 0;
			}
			//could be octal or hex. Check the next character.
			if(*cp == 'x' || *cp == 'X')
			{
				//parse as hex.
				++cp;
				NumericBase = 16;
			}
			else if(*cp == 'b' || *cp == 'B')
			{
				//parse as binary
				++cp;
				NumericBase = 2;
			}
			else
			{
				//parse it as octal.
				NumericBase = 8;
			}
		}
		else
		{
			//nope. assume decimal.
			NumericBase = 10;
		}
	}
	if(NumericBase == 10)
	{
		bool neg = false;
		//check first character for negative OR POSITIVE sign.
		switch(*cp)
		{
		case 0x002D:
		case 0x2212:
		case 0xFF0D:
			neg = true;
			++cp;
			break;
		case 0x002B:
		case 0xFB29:
		case 0xFF0B:
			neg = false;
			++cp;
			break;
		}
		//do parsing with unicode characters
		UT ret = 0;
		for(; !cp.is_null(); ++cp)
		{
			int value = ConvertCodePointToDigit(*cp);
			if(value == -1)
			{
				//end of the string. 
				break;
			}
			UT test = (ret * 10) + value;
			if(test < ret)
			{
				//overflow.
				break;
			}
			ret = test;
		}
		if(end) *end = cp;
		if(neg)
		{
			return (T)((~ret) + 1);
		}
		return ret;
	}
	else
	{
		//only ASCII for binary bases.
		UT ret = 0;
		for(; !cp.is_null(); ++cp)
		{
			int value = -1;
			CodePoint c = *cp;
			if(c >= '0' && c <= '9')
			{
				value = c - '0';
			}
			else if(c >= 'A' && c <= 'Z')
			{
				value = (c - 'A') + 10;
			}
			else if(c >= 'a' && c <= 'z')
			{
				value = (c - 'a') + 10;
			}
			if(value == -1 || value >= NumericBase)
			{
				//end of the string. 
				break;
			}
			UT test = (ret * NumericBase) + value;
			if(test < ret)
			{
				//overflow.
				break;
			}
			ret = test;
		}
		if(end) *end = cp;
		return ret;
	}
}

I32 BACnetString::ParseInt(size_t Start, iterator * End, U8 NumericBase) const
{
	return ParseInt(begin() + Start, End, NumericBase);
}

I32 BACnetString::ParseInt(iterator start, iterator* end, U8 NumericBase) const
{
	return ParseIntVal<I32>(start, end, NumericBase);
}

U32 BACnetString::ParseUInt(size_t Start, iterator * End, U8 NumericBase) const
{
	return ParseUInt(begin() + Start, End, NumericBase);
}

U32 BACnetString::ParseUInt(iterator start, iterator* end, U8 NumericBase) const
{
	return ParseIntVal<U32>(start, end, NumericBase);
}

I64 BACnetString::ParseInt64(size_t Start, iterator * End, U8 NumericBase) const
{
	return ParseInt64(begin() + Start, End, NumericBase);
}

I64 BACnetString::ParseInt64(iterator start, iterator* end, U8 NumericBase) const
{
	return ParseIntVal<I64>(start, end, NumericBase);
}

U64 BACnetString::ParseUInt64(size_t Start, iterator * End, U8 NumericBase) const
{
	return ParseUInt64(begin() + Start, End, NumericBase);
}

U64 BACnetString::ParseUInt64(iterator start, iterator* end, U8 NumericBase) const
{
	return ParseIntVal<U64>(start, end, NumericBase);
}

#pragma endregion

#pragma region String to float conversion

//TODO: String to floating point
template<typename T>
T AssembleZero(bool isneg)
{
}

#define MAX_FLOAT_DIGITS 8
#define MAX_DOUBLE_DIGITS 17

template< typename T>
T ParseFloatVal(BACnetString::iterator cp, BACnetString::iterator* end)
{
	//Go to the true beginning.
	if(end)*end = cp;
	if(cp.is_null())
	{
		return 0;
	}
	//skip through the whitespace.
	while(!cp.is_null() && IsWhitespace(*cp))
	{
		++cp;
	}
	//now assemble the digit string.
	bool isneg = false;
	bool ishex = false;
	int exponent = 0;
	constexpr int digitmax = std::is_same_v<float, T> ? MAX_FLOAT_DIGITS : MAX_DOUBLE_DIGITS;
	U8 mantissa[digitmax] = { 0 };
	//pull in the sign, if it exists.
	switch(*cp)
	{
	case 0x002D:
	case 0x2212:
	case 0xFF0D:
		isneg = true;
		++cp;
		break;
	case 0x002B:
	case 0xFB29:
	case 0xFF0B:
		isneg = false;
		++cp;
		break;
	}
	//now check for the hex prefix.
	if(*cp == '0')
	{
		++cp;
		//did we go past the length?
		if(cp.is_null())
		{
			//yes. Therefore the value is a zero.
			return AssembleZero(isneg);
		}
		//could be octal or hex. Check the next character.
		if(*cp == 'x' || *cp == 'X')
		{
			//parse as hex.
			++cp;
		}
	}
}

float BACnetString::ParseFloat(size_t Start, iterator * End) const
{
	return ParseFloat(begin() + Start, End);
}

float BACnetString::ParseFloat(iterator start, iterator* end) const
{
	//return ParseFloatVal<float>(begin(), end(), StartIndex, EndingIndex);
	return 0.0f;
}

double BACnetString::ParseDouble(size_t Start, iterator * End) const
{
	return ParseDouble(begin() + Start, End);
}

double BACnetString::ParseDouble(iterator start, iterator* end) const
{
	//return ParseFloatVal<double>(begin(), end(), StartIndex, EndingIndex);
	return 0.0;
}

#pragma endregion

#pragma region Integer to string conversion

#define MAX_U32_CHARS 34
#define MAX_U64_CHARS 66

template<typename T>
void ConvertIntegerToString(BACnetStringImpl* pstr, T value, I32 Base)
{
	if(value == 0)
	{
		pstr->size += EncodeCodePoint16('0', pstr->str);
		++pstr->length;
	}
	else if(std::is_signed_v<T> && Base == 10)
	{
		if(value < 0)
		{
			pstr->size += EncodeCodePoint16('-', pstr->str);
			++pstr->length;
		}
	}
	//go through each digit in the value until the value is zero.
	while(value != 0)
	{
		int digit = value % Base;
		CodePoint cp = ConvertDigitToCodePoint(digit);
		pstr->size += EncodeCodePoint16(cp, &pstr->str[pstr->size]);
		++pstr->length;
		value /= Base;
	}
	//Reverse the string.
	ReverseString(pstr);
	EncodeCodePoint16(0, &pstr->str[pstr->size]);
}

BACnetString BACnetString::ToString(I32 iValue, I32 Base)
{
	if(Base < 2 || Base > 36)
	{
		return BACnetString();
	}
	BACnetString str = BACnetString(MAX_U32_CHARS);
	ConvertIntegerToString(str.pImpl, iValue, Base);
	return str;
}

BACnetString BACnetString::ToString(U32 uiValue, I32 Base)
{
	if(Base < 2 || Base > 36)
	{
		return BACnetString();
	}
	BACnetString str = BACnetString(MAX_U32_CHARS);
	ConvertIntegerToString(str.pImpl, uiValue, Base);
	return str;
}

BACnetString BACnetString::ToString(I64 llValue, I32 Base)
{
	if(Base < 2 || Base > 36)
	{
		return BACnetString();
	}
	BACnetString str = BACnetString(MAX_U64_CHARS);
	ConvertIntegerToString(str.pImpl, llValue, Base);
	return str;
}

BACnetString BACnetString::ToString(U64 ullValue, I32 Base)
{
	if(Base < 2 || Base > 36)
	{
		return BACnetString();
	}
	BACnetString str = BACnetString(MAX_U64_CHARS);
	ConvertIntegerToString(str.pImpl, ullValue, Base);
	return str;
}

#pragma endregion

#pragma region Float to string conversion
//TODO: Floating point to String

BACnetString BACnetString::ToString(float fValue)
{
	return BACnetString();
}

BACnetString BACnetString::ToString(double dValue)
{
	return BACnetString();
}

#pragma endregion

BACnetString BACnetString::FromUTF8(const U8 * source)
{
	BACnetString str;
	CopyCharLiteral(str.pImpl, (const char*)source, false);
	return str;
}

BACnetString BACnetString::FromUTF16(const U16 * source)
{
	BACnetString str;
	CopyUnicodeLiteral16(str.pImpl, source);
	return str;
}

BACnetString BACnetString::FromUTF32(const U32 * source)
{
	BACnetString str;
	CopyUnicodeLiteral32(str.pImpl, source);
	return str;
}

BACnetString BACnetString::FromWindows1252(const U8 * source)
{
	BACnetString str;
	CopyCharLiteral(str.pImpl, (char*)source, true);
	return str;
}

BACnetString BACnetString::FromISO8859(const U8 * source)
{
	BACnetString str;
	CopyCharLiteral(str.pImpl, (char*)source, true);
	return str;
}

BACnetString BACnetString::FromUCS2(const U16 * source)
{
	BACnetString str;
	CopyUnicodeLiteral16(str.pImpl, source);
	return str;
}

BACnetString BACnetString::FromUCS4(const U32 * source)
{
	BACnetString str;
	CopyUnicodeLiteral32(str.pImpl, source);
	return str;
}

BACnetString::iterator::iterator() :
	pDataPtr(nullptr),
	uiOffset(0)
{
}

BACnetString::iterator::iterator(const iterator & Other) :
	pDataPtr(Other.pDataPtr),
	uiOffset(Other.uiOffset)
{
}

BACnetString::iterator::iterator(iterator && Other) :
	pDataPtr(Other.pDataPtr),
	uiOffset(Other.uiOffset)
{
}

BACnetString::iterator::~iterator()
{
	pDataPtr = nullptr;
	uiOffset = 0;
}

BACnetString::iterator & BACnetString::iterator::operator=(const iterator & Other)
{
	if(pDataPtr != Other.pDataPtr)
	{
		return *this;
	}
	uiOffset = Other.uiOffset;
	return *this;
}

BACnetString::iterator & BACnetString::iterator::operator=(iterator && Other)
{
	if(pDataPtr != Other.pDataPtr)
	{
		return *this;
	}
	uiOffset = Other.uiOffset;
	return *this;
}

int BACnetString::iterator::operator*()
{
	return DecodeCodePoint16(&((U16*)pDataPtr)[uiOffset]);
}

BACnetString::iterator & BACnetString::iterator::operator++()
{
	//increment by one character.
	U16* p = &((U16*)pDataPtr)[uiOffset];
	if(*p == 0)
	{
		return *this;
	}
	if(IsHighSurrogate(*p))
	{
		++uiOffset;
	}
	++uiOffset;
	return *this;
}

BACnetString::iterator BACnetString::iterator::operator++(int)
{
	//increment by one character.
	iterator ret = *this;
	U16* p = &((U16*)pDataPtr)[uiOffset];
	if(*p == 0)
	{
		return ret;
	}
	if(IsHighSurrogate(*p))
	{
		++uiOffset;
	}
	++uiOffset;
	return ret;
}

BACnetString::iterator& BACnetString::iterator::operator--()
{
	if(uiOffset == 0)
	{
		return *this;
	}
	--uiOffset;
	U16* p = &((U16*)pDataPtr)[uiOffset];
	if(IsLowSurrogate(*p))
	{
		--uiOffset;
	}
	return *this;
}

BACnetString::iterator BACnetString::iterator::operator--(int)
{
	//back up by one character.
	iterator ret = *this;
	if(uiOffset == 0)
	{
		return ret;
	}
	--uiOffset;
	U16* p = &((U16*)pDataPtr)[uiOffset];
	if(IsLowSurrogate(*p))
	{
		--uiOffset;
	}
	return ret;
}

BACnetString::iterator & BACnetString::iterator::operator+=(size_t Offset)
{
	while(Offset)
	{
		U16* p = &((U16*)pDataPtr)[uiOffset];
		if(*p == 0)
		{
			break;
		}
		if(IsHighSurrogate(*p))
		{
			++uiOffset;
		}
		++uiOffset;
		--Offset;
	}
	return *this;
}

BACnetString::iterator BACnetString::iterator::operator+(size_t Offset)
{
	iterator ret = *this;
	return ret += Offset;
}

BACnetString::iterator & BACnetString::iterator::operator-=(size_t Offset)
{
	while(Offset)
	{
		if(uiOffset == 0)
		{
			break;
		}
		--uiOffset;
		U16* p = &((U16*)pDataPtr)[uiOffset];
		if(IsLowSurrogate(*p))
		{
			--uiOffset;
		}
		--Offset;
	}
	return *this;
}

BACnetString::iterator BACnetString::iterator::operator-(size_t Offset)
{
	iterator ret = *this;
	return ret -= Offset;
}

bool BACnetString::iterator::is_null() const
{
	return (!pDataPtr) || (((U16*)pDataPtr)[uiOffset] == 0);
}

bool BACnetString::iterator::operator==(iterator Other)
{
	return (Other.pDataPtr == pDataPtr) && (Other.uiOffset == uiOffset);
}

bool BACnetString::iterator::operator!=(iterator Other)
{
	return !(*this == Other);
}

//Note - All iterators from different strings are considered incomparable.
// This means all comparison operations except not equal will return false.
bool BACnetString::iterator::operator<(iterator Other)
{
	return (Other.pDataPtr == pDataPtr) && (uiOffset < Other.uiOffset);
}

bool BACnetString::iterator::operator>(iterator Other)
{
	return (Other.pDataPtr == pDataPtr) && (uiOffset > Other.uiOffset);
}

bool BACnetString::iterator::operator>=(iterator Other)
{
	return (Other.pDataPtr == pDataPtr) && (uiOffset >= Other.uiOffset);
}

bool BACnetString::iterator::operator<=(iterator Other)
{
	return (Other.pDataPtr == pDataPtr) && (uiOffset <= Other.uiOffset);
}

