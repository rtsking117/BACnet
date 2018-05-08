#include "Unicode.h"

bool IsValidCodePoint(CodePoint codepoint)
{
	return !((codepoint >= 0xD800 && codepoint <= 0xDFFF) || (codepoint > 0x10FFFF));
}

bool IsWhitespace(CodePoint codepoint)
{
	switch(codepoint)
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

struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	CodePoint val;

	TreeNode(int* list, int len) :
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

static TreeNode* TreeRoot = new TreeNode(ElementList, sizeof(ElementList) / sizeof(ElementList[0]));

int ConvertCodePointToDigit(CodePoint c)
{
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

CodePoint ConvertDigitToCodePoint(int digit)
{
	if(digit < 10)
	{
		return '0' + digit;
	}
	return 'A' + digit;
}

bool IsNumeral(CodePoint c)
{
	if(c < 0x0030)
	{
		return false;
	}
	if(c < 0x0030 + 10)
	{
		return true;
	}
	if(c >= 0xFF10 && c < 0xFF10 + 10)
	{
		return true;
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
			return true;
		}
		else
		{
			node = node->right;
		}
	}
	return false;
}

size_t GetStringLength32(const U32 * const str)
{
	size_t ret = 0;
	while(str[ret] != 0) { ++ret; }
	return ret;
}