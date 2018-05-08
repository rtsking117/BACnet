#pragma once

#include "BACnetTypes.h"

class BACNET_ENTRYPOINT BACnetBitString final
{
	struct BACnetBitStringImpl* pImpl;
public:
	BACnetBitString();
	explicit BACnetBitString(const void* pBuffer, size_t uiBitLength);
	BACnetBitString(const BACnetBitString& Other);
	BACnetBitString(BACnetBitString&& Other);
	~BACnetBitString();

	size_t length() const;
	size_t size() const;
	size_t bytes() const;
	size_t capacity() const;
	void* buffer() const;
	void resize(size_t NewSize);
	void clear();

	bool IsBitSet(U32 BitIndex);
	bool IsBitClear(U32 BitIndex);

	bool operator[](size_t BitIndex);

	BACnetBitString& operator=(const BACnetBitString& Other);
	BACnetBitString& operator=(BACnetBitString&& Other);
};

