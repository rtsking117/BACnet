#include "BACnetStringImpl.h"

void CopyCharLiteral(BACnetStringImpl* const s, const char * const l, bool isISO)
{
	//UTF8, ASCII, or ISO 8859-1 literal.
	//first, try a UTF8 parse.
	//if we get an invalid sequence, switch to ISO 8859-1.
	//match the size of the char pointer.
	if(s->str)
	{
		delete[] s->str;
	}
	s->bytes = strlen(l) + 1;
	s->str = new U16[s->bytes];
	//go over each character in turn, and encode it into UTF-16.
	int charsize = 0;
	for(size_t i = 0; i < s->bytes; i += charsize, ++s->length)
	{
		if(l[i] == 0)
		{
			break;
		}
		CodePoint cp = 0;
		if(isISO)
		{
			cp = ConvertISOCharToCodePoint(l[i]);
		}
		else
		{
			cp = DecodeCodePoint8((U8*)&l[i]);
			charsize = GetNumCodeUnits8(cp);
		}
		if(cp == 0)
		{
			isISO = true;
			cp = ConvertISOCharToCodePoint(l[i]);
			charsize = 1;
		}
		int size = EncodeCodePoint16(cp, &s->str[s->size]);
		s->size += size;
	}
	EncodeCodePoint16(0, &s->str[s->size]);
}

void CopyUnicodeLiteral16(BACnetStringImpl* const s, const U16 * const l)
{
	//allocate a buffer the same size as the string.
	if(s->str)
	{
		delete[] s->str;
	}
	s->bytes = (GetStringLength16(l) + 1);
	s->str = new U16[s->bytes];
	//copy and verify the string literal.
	for(s->size = 0, s->length = 0; s->size < s->bytes; ++s->length)
	{
		if(l[s->size] == 0)
		{
			break;
		}
		if(IsHighSurrogate(l[s->size]))
		{
			if(!IsLowSurrogate(l[s->size + 1]))
			{
				//invalid.
				break;
			}
			//copy both values.
			s->str[s->size] = l[s->size];
			s->str[s->size + 1] = l[s->size + 1];
			s->size += 2;
		}
		else if(IsLowSurrogate(l[s->size]))
		{
			//also invalid.
			break;
		}
		else
		{
			s->str[s->size] = l[s->size];
			++s->size;
		}
	}
	s->str[s->size] = 0;
}

void CopyUnicodeLiteral32(BACnetStringImpl* const s, const U32 * const l)
{
	//need to reallocate the internal string.
	//initial estimate at 125% of the original string.
	//reallocate from there in 25% increments.
	if(s->str)
	{
		delete[] s->str;
	}
	size_t sz = GetStringLength32(l) + 1;
	size_t increment = sz >> 2; 
	s->bytes = (sz) + (increment);
	s->str = new U16[s->bytes];
	for(s->size = 0, s->length = 0; s->size < s->bytes; ++s->length)
	{
		if(l[s->length] == 0)
		{
			if(s->size + 1 > s->bytes)
			{
				s->bytes = (sz)+(increment);
				U16* tptr = s->str;
				s->str = new U16[s->bytes];
				memcpy(s->str, tptr, s->size);
				delete[] tptr;
			}
			break;
		}
		int nc = GetNumCodeUnits16(l[s->length]);
		if(s->size + nc > s->bytes)
		{
			//reallocate.
			s->bytes = (sz)+(increment);
			U16* tptr = s->str;
			s->str = new U16[s->bytes];
			memcpy(s->str, tptr, s->size);
			delete[] tptr;
		}
		s->size += EncodeCodePoint16(l[s->length], s->str);
	}
}

void CopyUnicodeLiteral(BACnetStringImpl* const s, const wchar_t * const l)
{
	static_assert((sizeof(wchar_t) != 2 || sizeof(wchar_t) != 4), "sizeof(wchar_t) is not 2 or 4 bytes.");
	if(sizeof(wchar_t) == 2)
	{
		CopyUnicodeLiteral16(s, (U16*)l);
	}
	else if(sizeof(wchar_t) == 4)
	{
		CopyUnicodeLiteral32(s, (U32*)l);
	}
}

size_t ComputeSizeAsUTF8(const BACnetStringImpl * const s)
{
	//Go over each code point in the UTF-16 string,
	// and total up the code units needed to represent them.
	size_t ret = 0;
	for(size_t i = 0; i < s->size; ++i)
	{
		CodePoint c = DecodeCodePoint16(&s->str[i]);
		if(GetNumCodeUnits16(c) == 2)
		{
			++i;
		}
		ret += GetNumCodeUnits8(c);
	}
	return ret;
}

size_t ConvertToUTF8(const BACnetStringImpl * const s, U8 * const str, size_t slen)
{
	//Do a UTF-8 encode
	size_t index = 0;
	//go over each character in turn, and encode it into UTF-8.
	int charsize = 0;
	for(size_t i = 0; i < s->size; i+=GetNumCodeUnits16(&s->str[i]))
	{
		CodePoint cp = DecodeCodePoint16(&s->str[i]);
		if(index + GetNumCodeUnits8(cp) > slen)
		{
			return index;
		} 
		index += EncodeCodePoint8(cp, &(str)[index]);
	}
	if(index + 1 > slen)
	{
		return index;
	}
	EncodeCodePoint8(0, &(str)[index]);
	return slen;
}

size_t ConvertToUTF32(const BACnetStringImpl * const s, U32 * const str, size_t slen)
{
	if(slen < s->length + 1)
	{
		return (s->length + 1);
	}
	//This should be safe. If we throw an exception here, we've fucked up, and need to fix it.
	// length == num codepoints == countof equivalent UTF-32 string.
	// iterating over code unit "pairs" up to length will be safe unless we messed up the length calculation.
	size_t index = 0;
	for(int i = 0; i < slen; ++i)
	{
		str[i] = DecodeCodePoint16(&s->str[index]);
		index += GetNumCodeUnits16(str[i]);
	}
	return slen;
}

