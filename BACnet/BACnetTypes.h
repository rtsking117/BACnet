#pragma once

#include <stdint.h>
#include "BACnetCommon.h"

typedef int8_t I8;
typedef uint8_t U8;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;
typedef int64_t I64;
typedef uint64_t U64;

U16 BACNET_ENTRYPOINT ToNet16(U16 uiHost);
U32 BACNET_ENTRYPOINT ToNet32(U32 uiHost);
U64 BACNET_ENTRYPOINT ToNet64(U64 uiHost);

U16 BACNET_ENTRYPOINT ToHost16(U16 uiNet);
U32 BACNET_ENTRYPOINT ToHost32(U32 uiNet);
U64 BACNET_ENTRYPOINT ToHost64(U64 uiNet);

U32 BACNET_ENTRYPOINT FindFirstSet(U32 Value);

U32 BACNET_ENTRYPOINT Log2(U32 Value);

#include "BACnetByteString.h"
#include "BACnetString.h"
#include "BACnetBitString.h"
