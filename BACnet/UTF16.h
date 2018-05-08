#pragma once

#include "Unicode.h"

bool IsHighSurrogate(U16 c);
bool IsLowSurrogate(U16 c);

int GetNumCodeUnits16(U16* str);
int GetNumCodeUnits16(CodePoint cp);

size_t GetStringLength16(const U16* const str);

int EncodeCodePoint16(CodePoint cp, U16* str);

CodePoint DecodeCodePoint16(U16* str);