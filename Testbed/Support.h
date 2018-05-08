#pragma once

const char* ConvertServiceToString(U8 ServiceChoice, bool IsConfirmed);

void PrintBACnetValue(const BACnetValue &v, int ntabs);