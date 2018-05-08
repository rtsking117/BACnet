#include "ISO 8859-1.h"

//This table is actually Windows-1252. We interpret C1 control
//characters as their Windows-1252 counterparts, as they are rarely
//used in text, and more commonly text labeled as 8859-1 is actually
//Windows 1252 (enough such that HTML 5 mandates Windows 1252 instead 
//of ISO 8859-1, even when labeled as such).
//array starts at 0x80.
CodePoint C1Map[] = {
	0x20AC,
	129,
	0x201A,
	0x0192,
	0x201E,
	0x2026,
	0x2020,
	0x2021,
	0x02C6,
	0x2030,
	0x0160,
	0x2039,
	0x0152,
	141,
	0x017D,
	143,
	144,
	0x2018,
	0x2019,
	0x201C,
	0x201D,
	0x2022,
	0x2013,
	0x2014,
	0x02DC,
	0x2122,
	0x0161,
	0x203A,
	0x0153,
	157,
	0x017E,
	0x0178,
};

CodePoint ConvertISOCharToCodePoint(U8 ch)
{
	if(ch >= 0x80 && ch < 0xA0)
	{
		return C1Map[ch];
	}
	return (CodePoint)ch;
}
