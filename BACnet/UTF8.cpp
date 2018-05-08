#include "UTF8.h"
#include <type_traits>
using namespace std;

bool IsValidByte(U8 c)
{
	if((c == 0xC0) || (c == 0xC1) || (c >= 0xF5))
	{
		return false;
	}
	return true;
}

bool IsAsciiByte(U8 c)
{
	return (c < 0x80);
}

bool IsLeadByte(U8 c)
{
	if(((c & 0xE0) == 0xC0) ||
		((c & 0xF0) == 0xE0) ||
	   ((c & 0xF8) == 0xF0))
	{
		return true;
	}
	return false;
}

int GetNumContinuationBytes(U8 c)
{
	if((c & 0x80) == 0x00)
	{
		return 0;
	}
	if((c & 0xE0) == 0xC0)
	{
		return 1;
	}
	if((c & 0xF0) == 0xE0)
	{
		return 2;
	}
	if((c & 0xF8) == 0xF0)
	{
		return 3;
	}
	return 0;
}

int GetNumCodeUnits8(const U8 * const str)
{
	U8 c = str[0];
	if((c & 0x80) == 0x00)
	{
		return 1;
	}
	if((c & 0xE0) == 0xC0)
	{
		return 2;
	}
	if((c & 0xF0) == 0xE0)
	{
		return 3;
	}
	if((c & 0xF8) == 0xF0)
	{
		return 4;
	}
	return 0;
}

int GetNumCodeUnits8(CodePoint cp)
{
	if(!IsValidCodePoint(cp)) return 0;
	if(cp < 0x7F)
	{
		return 1;
	}
	if(cp < 0x7FF)
	{
		return 2;
	}
	if(cp < 0xFFFF)
	{
		return 3;
	}
	return 4;
}

bool IsContinuationByte(U8 c)
{
	if(c >= 0x80 && c < 0xC0)
	{
		return true;
	}
	return false;
}

CodePoint DecodeCodePoint8(const U8* const str)
{
	switch(GetNumContinuationBytes(str[0]))
	{
	case 0:
		return (str[0] & 0x7F);
	case 1:
		return (((str[0] & 0x1F) << 6) | (str[1] & 0x3F));
	case 2:
		return (((str[0] & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F));
	case 3:
		return (((str[0] & 0x07) << 18) | ((str[1] & 0x3F) << 12) | ((str[2] & 0x3F) << 6) | (str[3] & 0x3F));
	default:
		return 0xFFFD; //replacement character. Shouldn't happen.
	}
}

int EncodeCodePoint8(CodePoint cp, U8 * str)
{
	int nc = GetNumCodeUnits8(cp);
	switch(nc)
	{
	case 0:
		break;
	case 1:
		str[0] = cp & 0x7F;
		break;
	case 2:
		str[0] = 0xC0 | ((cp & 0x07C0) >> 6);
		str[1] = 0x80 | ((cp & 0x003F));
		break;
	case 3:
		str[0] = 0xE0 | ((cp & 0xF000) >> 12);
		str[1] = 0x80 | ((cp & 0x0FC0) >> 6);
		str[2] = 0x80 | ((cp & 0x00FC));
		break;
	case 4:
		str[0] = 0xF0 | ((cp & 0x1C0000) >> 18);
		str[1] = 0x80 | ((cp & 0x03F000) >> 12);
		str[2] = 0x80 | ((cp & 0x000FC0) >> 6);
		str[3] = 0x80 | ((cp & 0x00003F));
		break;
		BACNET_UNREACHABLECASE;
	}
	return nc;
}

