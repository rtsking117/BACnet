#pragma once
#include "BACnetTypes.h"

class BACNET_ENTRYPOINT BACnetByteString final
{
	struct BACnetByteStringImpl* pImpl;
public:
	BACnetByteString();
	explicit BACnetByteString(const void* pBuffer, size_t uiBufferLength);
	BACnetByteString(const BACnetByteString& Other);
	BACnetByteString(BACnetByteString&& Other);
	~BACnetByteString();

	size_t length() const;
	size_t size() const;
	size_t bytes() const;
	size_t capacity() const;
	void* buffer() const;
	void resize(size_t NewSize);
	void clear();

	U8 operator[](size_t ByteIndex);

	BACnetByteString& operator=(const BACnetByteString& Other);
	BACnetByteString& operator=(BACnetByteString&& Other);

	BACnetByteString operator+(const BACnetByteString& Other) const;
	BACnetByteString operator+(BACnetByteString&& Other) const;

	BACnetByteString& operator+=(const BACnetByteString& Other);
	BACnetByteString& operator+=(BACnetByteString&& Other);

};

