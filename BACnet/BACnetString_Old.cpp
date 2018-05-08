#include "BACnetString.h"
#include <cstdlib>
#include <cstdio>
#include <memory>
using namespace std;


size_t ConvertIndexToByte(char* str, size_t Index)
{
	size_t i = 0;
	for(; i < Index; ++i)
	{
		if(IsLeadByte(str[i]))
		{ 
			i += GetNumContinuationBytes(str[i]);
		}
	}
	return i;
}

size_t ComputeLength(char* str, size_t size)
{
	size_t i = 0;
	for(; i < size; ++i)
	{
		if(!IsValidByte(str[i]))
		{
			return i;
		}
		if(IsLeadByte(str[i]))
		{
			//get the number of continuation byte needed
			int ncbytes = GetNumContinuationBytes(str[i]);
			int offset = 1;
			for(int offset = 1; offset <= ncbytes; ++offset)
			{
				if((!IsValidByte(str[i + offset])) ||
					(!IsContinuationByte(str[i + offset])))
				{
					return i;
				}
			}
			if(IsInvalidCharacter(str, i, ncbytes))
			{
				return i;
			}
			i += offset - 1;
		}
	}
	return i;
}

struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	int val;

	TreeNode(int* list, int len):
		left(nullptr),
		right(nullptr)
	{
		if(len == 0)
		{
			__debugbreak();
			val = 0;
		}
		else if(len == 1)
		{
			val = list[0];
		}
		else if(len == 2)
		{
			val = list[0];
			right = new TreeNode(&list[1], 1);
		}
		else
		{
			//get the midpoint of the list.
			int mid = len >> 1;
			val = list[mid];
			//and recurse.
			left = new TreeNode(list, mid);
			right = new TreeNode(&list[mid + 1], len - mid - 1);
		}

	}
	~TreeNode()
	{
		if(left) { delete left; }
		if(right) { delete right; }
		val = 0;
	}
};

#define DIGIT_RANGE(x) x

int ElementList[] = {
	0x00030,	// 00030;DIGIT ZERO
	0x00660,	// 00660;ARABIC-INDIC DIGIT ZERO
	0x006F0,	// 006F0;EXTENDED ARABIC-INDIC DIGIT ZERO
	0x007C0,	// 007C0;NKO DIGIT ZERO
	0x00966,	// 00966;DEVANAGARI DIGIT ZERO
	0x009E6,	// 009E6;BENGALI DIGIT ZERO
	0x00A66,	// 00A66;GURMUKHI DIGIT ZERO
	0x00AE6,	// 00AE6;GUJARATI DIGIT ZERO
	0x00B66,	// 00B66;ORIYA DIGIT ZERO
	0x00BE6,	// 00BE6;TAMIL DIGIT ZERO
	0x00C66,	// 00C66;TELUGU DIGIT ZERO
	0x00CE6,	// 00CE6;KANNADA DIGIT ZERO
	0x00D66,	// 00D66;MALAYALAM DIGIT ZERO
	0x006F0,	// 00DE6;SINHALA LITH DIGIT ZERO
	0x00E50,	// 00E50;THAI DIGIT ZERO
	0x00ED0,	// 00ED0;LAO DIGIT ZERO
	0x00F20,	// 00F20;TIBETAN DIGIT ZERO
	0x01040,	// 01040;MYANMAR DIGIT ZERO
	0x006F0,	// 01090;MYANMAR SHAN DIGIT ZERO
	0x017E0,	// 017E0;KHMER DIGIT ZERO
	0x01810,	// 01810;MONGOLIAN DIGIT ZERO
	0x01946,	// 01946;LIMBU DIGIT ZERO
	0x019D0,	// 019D0;NEW TAI LUE DIGIT ZERO
	0x01A80,	// 01A80;TAI THAM HORA DIGIT ZERO
	0x01A90,	// 01A90;TAI THAM THAM DIGIT ZERO
	0x01B50,	// 01B50;BALINESE DIGIT ZERO
	0x01BB0,	// 01BB0;SUNDANESE DIGIT ZERO
	0x01C40,	// 01C40;LEPCHA DIGIT ZERO
	0x01C50,	// 01C50;OL CHIKI DIGIT ZERO
	0x0A620,	// 0A620;VAI DIGIT ZERO
	0x0A8D0,	// 0A8D0;SAURASHTRA DIGIT ZERO
	0x0A900,	// 0A900;KAYAH LI DIGIT ZERO
	0x0A9D0,	// 0A9D0;JAVANESE DIGIT ZERO
	0x0A9F0,	// 0A9F0;MYANMAR TAI LAING DIGIT ZERO
	0x0AA50,	// 0AA50;CHAM DIGIT ZERO
	0x0ABF0,	// 0ABF0;MEETEI MAYEK DIGIT ZERO
	0x0FF10,	// 0FF10;FULLWIDTH DIGIT ZERO
	0x104A0,	// 104A0;OSMANYA DIGIT ZERO
	0x11066,	// 11066;BRAHMI DIGIT ZERO
	0x110F0,	// 110F0;SORA SOMPENG DIGIT ZERO
	0x11136,	// 11136;CHAKMA DIGIT ZERO
	0x111D0,	// 111D0;SHARADA DIGIT ZERO
	0x112F0,	// 112F0;KHUDAWADI DIGIT ZERO
	0x11450,	// 11450;NEWA DIGIT ZERO
	0x114D0,	// 114D0;TIRHUTA DIGIT ZERO
	0x11650,	// 11650;MODI DIGIT ZERO
	0x116C0,	// 116C0;TAKRI DIGIT ZERO
	0x11730,	// 11730;AHOM DIGIT ZERO
	0x118E0,	// 118E0;WARANG CITI DIGIT ZERO
	0x11C50,	// 11C50;BHAIKSUKI DIGIT ZERO
	0x16A60,	// 16A60;MRO DIGIT ZERO
	0x16B50,	// 16B50;PAHAWH HMONG DIGIT ZERO
	0x1D7CE,	// 1D7CE;MATHEMATICAL BOLD DIGIT ZERO
	0x1D7D8,	// 1D7D8;MATHEMATICAL DOUBLE-STRUCK DIGIT ZERO
	0x1D7E2,	// 1D7E2;MATHEMATICAL SANS-SERIF DIGIT ZERO
	0x1D7EC,	// 1D7EC;MATHEMATICAL SANS-SERIF BOLD DIGIT ZERO
	0x1D7F6,	// 1D7F6;MATHEMATICAL MONOSPACE DIGIT ZERO
	0x1E950,	// 1E950;ADLAM DIGIT ZERO
};

static TreeNode* TreeRoot = new TreeNode(ElementList, sizeof(ElementList)/sizeof(ElementList[0]));

int ParseCharacterAsNumeral(char* str, size_t index)
{
	int c = GetCharacter(str, index);
	//Check most common sets.
	if(c < 0x0030)
	{
		return -1;
	}
	if(c < 0x0030 + 10)
	{
		return c - 0x0030;
	}
	if(c >= 0xFF10 && c < 0xFF10 + 10)
	{
		return c - 0xFF10;
	}
	//ok, its not one of these. Find it in the tree.
	TreeNode* node = TreeRoot;
	while(node != nullptr)
	{
		if(c < node->val)
		{
			node = node->left;
		}
		else if(c < node->val + 10)
		{
			return c - node->val;
		}
		else
		{
			node = node->right;
		}
	}
	return -1;
}

size_t GetCharacterSize(char* str, size_t index)
{
	return GetNumContinuationBytes(str[index]) + 1;
}

bool IsWhitespace(char* str, size_t index)
{
	int c = GetCharacter(str, index);
	switch(c)
	{
	case 0x09:
	case 0x0A:
	case 0x0B:
	case 0x0C:
	case 0x0D:
	case 0x20:
	case 0x85:
	case 0xA0:
	case 0xB7:
	case 0x1680:
	case 0x180E:
	case 0x2000:
	case 0x2001:
	case 0x2002:
	case 0x2003:
	case 0x2004:
	case 0x2005:
	case 0x2006:
	case 0x2007:
	case 0x2008:
	case 0x2009:
	case 0x200A:
	case 0x200B:
	case 0x200C:
	case 0x200D:
	case 0x2028:
	case 0x2029:
	case 0x202F:
	case 0x205F:
	case 0x2060:
	case 0x237D:
	case 0x2420:
	case 0x2422:
	case 0x2423:
	case 0x3000:
	case 0xFEFF:
		return true;
	default:
		return false;
	}
}

int GetNumBytesNeeded(int c)
{

}

void EncodeCharacter(int c, char* m_str, size_t index)
{

}

struct BACnetStringInternal
{
	size_t m_bytes;
	size_t m_size;
	U16* m_str;
	size_t m_length;

	BACnetStringInternal() :m_bytes(0), m_size(0), m_str(nullptr), m_length(0) {}
	BACnetStringInternal(size_t strsize) :m_bytes((strsize + 1) << 1), m_size(0), m_str(new U16[m_bytes]), m_length(0) {}
};

BACnetString::BACnetString():
	pImpl(new BACnetStringInternal())
{
}

BACnetString::BACnetString(const char * pStringLiteral) :
	pImpl(new BACnetStringInternal(strlen(pStringLiteral)))
{
	pImpl->m_size = pImpl->m_bytes - 1;
	memcpy(pImpl->m_str, pStringLiteral, pImpl->m_size);
	m_length = ComputeLength(pImpl->m_str, m_size);
}

BACnetString::BACnetString(const BACnetString & Other):
	m_bytes(Other.m_bytes),
	m_size(Other.m_size),
	m_str(new char[m_bytes]),
	m_length(Other.m_length)
{
	memcpy(pImpl->m_str, Other.pImpl->m_str, m_size);
	pImpl->m_str[m_size] = 0;
}

BACnetString::BACnetString(BACnetString && Other) :
	pImpl(Other.pImpl)
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
	return pImpl->m_length;
}

size_t BACnetString::size() const
{
	return pImpl->m_size;
}

size_t BACnetString::capacity() const
{
	return pImpl->m_bytes;
}

char * BACnetString::string() const
{
	return ConvertToUTF8(pImpl);
}

void BACnetString::resize(size_t NewSize)
{
	if(NewSize <= pImpl->m_bytes)
	{
		return;
	}
	m_bytes = NewSize;
	char* newstr = new U16[m_bytes];
	memcpy(newstr, pImpl->m_str, m_size);
	newstr[m_size] = 0;
	delete[] pImpl->m_str;
	pImpl->m_str = newstr;
}

void BACnetString::clear()
{
	memset(pImpl->m_str, 0, m_bytes);
	m_size = 0;
	m_length = 0;
}

int BACnetString::operator[](size_t Index) const
{
	if(Index < 0 || Index > m_length)
	{
		return 0;
	}
	if(m_length == m_size)
	{
		return pImpl->m_str[Index];
	}
	else
	{
		//parse for the character.
		size_t startidx = ConvertIndexToByte(pImpl->m_str, Index);
		return GetCharacter(pImpl->m_str, startidx);
	}
}

BACnetString & BACnetString::operator=(const BACnetString & Other)
{
	if(this == &Other) return *this;
	m_bytes = Other.m_bytes;
	m_size = Other.m_size;
	m_length = Other.m_length;
	pImpl->m_str = new char[m_bytes];
	memcpy(pImpl->m_str, Other.pImpl->m_str, m_size);
	pImpl->m_str[m_size] = 0;
	return *this;
}

BACnetString & BACnetString::operator=(BACnetString && Other)
{
	if(this == &Other) return *this;
	swap(m_bytes, Other.m_bytes);
	swap(m_size, Other.m_size);
	swap(m_length, Other.m_length);
	swap(pImpl->m_str, Other.pImpl->m_str);
	return *this;
}

BACnetString & BACnetString::operator=(const char * Other)
{
	m_bytes = strlen(Other) + 1;
	m_size = m_bytes - 1;
	pImpl->m_str = new char[m_bytes];
	memcpy(pImpl->m_str, Other, m_size);
	pImpl->m_str[m_size] = 0;
	m_length = ComputeLength(pImpl->m_str, m_size);
	return *this;
}

BACnetString BACnetString::operator+(const BACnetString & Other) const
{
	BACnetString ret(*this);
	return (ret += Other);
}

BACnetString BACnetString::operator+(BACnetString && Other) const
{
	BACnetString ret(*this);
	return (ret += Other);
}

BACnetString BACnetString::operator+(const char * Other) const
{
	BACnetString ret(*this);
	return (ret += Other);
}

BACnetString & BACnetString::operator+=(const BACnetString & Other)
{
	resize(m_size + Other.m_size + 1);
	memcpy(pImpl->m_str + m_size, Other.pImpl->m_str, Other.m_size);
	m_size += Other.m_size;
	m_length += Other.m_length;
	pImpl->m_str[m_size] = 0;
	return *this;
}

BACnetString & BACnetString::operator+=(BACnetString && Other)
{
	resize(m_size + Other.m_size + 1);
	memcpy(pImpl->m_str + m_size, Other.pImpl->m_str, Other.m_size);
	m_size += Other.m_size;
	m_length += Other.m_length;
	pImpl->m_str[m_size] = 0;
	return *this;
}

BACnetString & BACnetString::operator+=(const char * Other)
{
	resize(m_size + strlen(Other) + 1);
	memcpy(pImpl->m_str + m_size, Other, strlen(Other));
	m_length += ComputeLength(pImpl->m_str + m_size, strlen(Other)); //just compute the length of the new portion.
	m_size += strlen(Other);
	pImpl->m_str[m_size] = 0;
	return *this;
}

template<typename T,
bool type_is_signed = is_signed<T>::value>
T ParseIntVal(char* m_str, size_t m_length, size_t m_size, size_t StartIndex, size_t * EndingIndex, U8 NumericBase)
{
	//initialize the ending index.
	if(EndingIndex)*EndingIndex = StartIndex;
	//check the length and the start index.
	if(StartIndex > m_length)
	{
		return 0;
	}
	size_t start = ConvertIndexToByte(m_str, StartIndex);
	//Now strip off all whitespace characters from the start.
	for( ; start < m_size && IsWhitespace(m_str, start); ++StartIndex, start += (GetCharacterSize(m_str, start)));
	if(NumericBase == 0)
	{
		//Auto detect. is the first char a zero?
		if(m_str[start] == '0')
		{
			++StartIndex; ++start;
			//did we go past the length?
			if(StartIndex > m_length)
			{
				//yes. Therefore the value is a zero.
				if(EndingIndex)*EndingIndex = StartIndex;
				return 0;
			}
			//could be octal or hex. Check the next character.
			if(m_str[start] == 'x' || m_str[start] == 'X')
			{
				//parse as hex.
				++StartIndex; ++start;
				NumericBase = 16;
			}
			else if(m_str[start] == 'b' || m_str[start] == 'B')
			{
				//parse as binary
				++StartIndex;  ++start;
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
		if(type_is_signed)
		{
			//check first character for negative OR POSITIVE sign.
			switch(GetCharacter(m_str, start))
			{
			case 0x002D:
			case 0x2212:
			case 0xFF0D:
				neg = true;
				start += GetCharacterSize(m_str, start);
				++StartIndex;
			case 0x002B:
			case 0xFB29:
			case 0xFF0B:
				neg = false;
				start += GetCharacterSize(m_str, start);
				++StartIndex;
			}
		}
		//do parsing with unicode characters
		T ret = 0;
		for(size_t i = start; i < m_size; ++StartIndex, i += (GetCharacterSize(m_str, i)))
		{
			int value = ParseCharacterAsNumeral(m_str, i);
			if(value == -1)
			{
				//end of the string. 
				break;
			}
			T test = (ret * 10) + value;
			if(test < ret)
			{
				//overflow.
				break;
			}
			ret = test;
		}
		if(EndingIndex) *EndingIndex = StartIndex;
		if(type_is_signed && neg)
		{
			//avoid C4146 on unsigned types, as cl is not smart enough to notice the dead code here.
			return ((~ret) + 1); 
		}
		return ret;
	}
	else
	{
		//only ASCII for binary bases.
		T ret = 0;
		for(size_t i = start; i < m_size; ++StartIndex, i += (GetCharacterSize(m_str, i)))
		{
			int value = -1;
			int c = m_str[i];
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
			T test = (ret * NumericBase) + value;
			if(test < ret)
			{
				//overflow.
				break;
			}
			ret = test;
		}
		if(EndingIndex) *EndingIndex = StartIndex;
		return ret;
	}
}

I32 BACnetString::ParseInt(size_t StartIndex, size_t * EndingIndex, U8 NumericBase) const
{
	return ParseIntVal<I32>(m_str, m_length, m_size, StartIndex, EndingIndex, NumericBase);
}

U32 BACnetString::ParseUInt(size_t StartIndex, size_t * EndingIndex, U8 NumericBase) const
{
	return ParseIntVal<U32>(m_str, m_length, m_size, StartIndex, EndingIndex, NumericBase);
}

LARGEINT BACnetString::ParseLargeInt(size_t StartIndex, size_t * EndingIndex, U8 NumericBase) const
{
	LARGEINT ret;
	ret.QuadPart = ParseIntVal<int64_t>(m_str, m_length, m_size, StartIndex, EndingIndex, NumericBase);
	return ret;
}

LARGEUINT BACnetString::ParseLargeUInt(size_t StartIndex, size_t * EndingIndex, U8 NumericBase) const
{
	LARGEUINT ret;
	ret.QuadPart = ParseIntVal<uint64_t>(m_str, m_length, m_size, StartIndex, EndingIndex, NumericBase);
	return ret;
}

float BACnetString::ParseFloat(size_t StartIndex, size_t * EndingIndex, U8 NumericBase) const
{
	return 0.0f;
}

double BACnetString::ParseDouble(size_t StartIndex, size_t * EndingIndex, U8 NumericBase) const
{
	return 0.0;
}


/*
BACnetString BACnetString::ToString(I32 iValue)
{
	// TODO: insert return statement here
	return;
}

BACnetString BACnetString::ToString(U32 uiValue)
{
	// TODO: insert return statement here
}

BACnetString BACnetString::ToString(float fValue)
{
	// TODO: insert return statement here
}

BACnetString BACnetString::ToString(double dValue)
{
	// TODO: insert return statement here
}

BACnetString BACnetString::ToString(LARGEINT llValue)
{
	// TODO: insert return statement here
}

BACnetString BACnetString::ToString(LARGEUINT ullValue)
{
	// TODO: insert return statement here
}
*/

BACnetString BACnetString::FromISO8859(char * source)
{
	return BACnetString();
}

BACnetString BACnetString::FromUCS2(U16 * source)
{
	BACnetString ret;
	size_t srcsize = 0;
	while(source[srcsize] != 0x0000)
	{
		++srcsize;
	}
	ret.resize(srcsize);
}

BACnetString BACnetString::FromUCS4(U32 * source)
{
	return BACnetString();
}
