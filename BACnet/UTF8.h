#pragma once

#include "Unicode.h"


bool IsValidByte(U8 c);
bool IsAsciiByte(U8 c);
bool IsLeadByte(U8 c);
bool IsContinuationByte(U8 c);

int GetNumContinuationBytes(U8 c);

int GetNumCodeUnits8(const U8* const str);

int GetNumCodeUnits8(CodePoint cp);

CodePoint DecodeCodePoint8(const U8* const str);

int EncodeCodePoint8(CodePoint cp, U8* str);
