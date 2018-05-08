#pragma once

#include "BACnetTypes.h"

typedef int CodePoint;

bool IsValidCodePoint(CodePoint codepoint);
bool IsWhitespace(CodePoint codepoint);
bool IsNumeral(CodePoint codepoint);

int ConvertCodePointToDigit(CodePoint codepoint);
CodePoint ConvertDigitToCodePoint(int digit);

size_t GetStringLength32(const U32* const str);