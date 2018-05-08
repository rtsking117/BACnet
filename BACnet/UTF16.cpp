#include "UTF16.h"

#define SURROGATE_MASK	0xFC00
#define HIGH_MARK	0xD800
#define LOW_MARK	0xDC00

bool IsHighSurrogate(U16 c)
{
	return (c & SURROGATE_MASK) == HIGH_MARK;
}

bool IsLowSurrogate(U16 c)
{
	return (c & SURROGATE_MASK) == LOW_MARK;
}

int GetNumCodeUnits16(U16 * str)
{
	if(IsHighSurrogate(str[0]))
	{
		return 2;
	}
	return 1;
}

int GetNumCodeUnits16(CodePoint codepoint)
{
	if(!IsValidCodePoint(codepoint)) return 0;
	if(codepoint < 0xFFFF)
	{
		return 1;
	}
	return 2;
}

size_t GetStringLength16(const U16 * const str)
{
	size_t ret = 0;
	while(str[ret] != 0x0000) { ++ret; }
	return ret;
}

int EncodeCodePoint16(CodePoint codepoint, U16 * str)
{
	if(!IsValidCodePoint(codepoint)) return 0;
	if(codepoint > 0xFFFF)
	{
		int mcp = codepoint - 0x10000;
		U16 HighSurrogate = HIGH_MARK | ((mcp & 0xFFC00) >> 10);
		U16 LowSurrogate = LOW_MARK | ((mcp & 0x003FF) >> 0);
		str[0] = HighSurrogate;
		str[1] = LowSurrogate;
		return 2;
	}
	str[0] = codepoint & 0xFFFF;
	return 1;
}

CodePoint DecodeCodePoint16(U16 * str)
{
	if(IsHighSurrogate(str[0]))
	{
		if(IsLowSurrogate(str[1]))
		{
			U16 HighSurrogate = str[0];
			U16 LowSurrogate = str[1];
			int mcp = (((HighSurrogate & 0x3FF) << 10) | (LowSurrogate & 0x3FF));
			return mcp + 0x10000;
		}
		return 0;
	}
	else if(IsLowSurrogate(str[0]))
	{
		return 0;
	}
	return str[0];
}
