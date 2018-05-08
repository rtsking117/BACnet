#include "BACnetBitString.h"
#include <memory>
#include <stdexcept>

size_t CalculateByteOffset(size_t BitOffset)
{
	return (BitOffset >> 3);
}

size_t CalculateByteSize(size_t BitLength)
{
	//number of bits / 8 + 1
	return CalculateByteOffset(BitLength) + 1;
}

U8 CalculateBitMask(size_t BitOffset)
{
	return 0x80 >> (BitOffset & 0x07);
}

struct BACnetBitStringImpl
{
	size_t length;
	size_t size;
	size_t capacity;
	U8* buffer;
	BACnetBitStringImpl() :length(0), size(0), capacity(0), buffer(nullptr) {}
	explicit BACnetBitStringImpl(size_t bitlen) : length(0), size(0), capacity(CalculateByteSize(bitlen)), buffer(new U8[capacity])
	{
		memset(buffer, 0, capacity);
	}
	explicit BACnetBitStringImpl(size_t bitlen, const void* data) : length(0), size(0), capacity(CalculateByteSize(bitlen)), buffer(new U8[capacity])
	{
		if(data)
		{
			memcpy(buffer, data, capacity);
			size = capacity;
			length = bitlen;
		}
		else
		{
			memset(buffer, 0, capacity);
		}
	}
	~BACnetBitStringImpl()
	{
		//if someone forgot to clean us up, do so now.
		if(buffer)
		{
			delete[] buffer;
			buffer = nullptr;
		}
		size = capacity = length = 0;
	}
};


BACnetBitString::BACnetBitString() : 
	pImpl(new BACnetBitStringImpl())
{
}

BACnetBitString::BACnetBitString(const void * pBuffer, size_t uiBitLength) :
	pImpl(nullptr)
{
	if(uiBitLength < 0)
	{
		//throw now. do not initialize until we know we can do it safely.
		throw std::invalid_argument("uiBitLength cannot be negative.");
	}
	pImpl = new BACnetBitStringImpl(uiBitLength, pBuffer);
}

BACnetBitString::BACnetBitString(const BACnetBitString & Other) : 
	pImpl(new BACnetBitStringImpl(Other.pImpl->length, Other.pImpl->buffer))
{
}

BACnetBitString::BACnetBitString(BACnetBitString && Other):
	pImpl(std::move(Other.pImpl))
{
	Other.pImpl = nullptr;
}

BACnetBitString::~BACnetBitString()
{
	if(pImpl)
	{
		delete pImpl;
		pImpl = nullptr;
	}
}

size_t BACnetBitString::length() const
{
	return pImpl->length;
}

size_t BACnetBitString::size() const
{
	return pImpl->size;
}

size_t BACnetBitString::bytes() const
{
	return pImpl->size;
}

size_t BACnetBitString::capacity() const
{
	return pImpl->capacity;
}

void * BACnetBitString::buffer() const
{
	return pImpl->buffer;
}

void BACnetBitString::resize(size_t NewSize)
{
	size_t ns = CalculateByteSize(NewSize);
	if(ns < capacity())
	{
		return;
	}
	U8* temp = pImpl->buffer;
	pImpl->buffer = new U8[ns];
	if(temp)
	{
		memcpy(pImpl->buffer, temp, pImpl->capacity);
		delete[] temp;
	}
	pImpl->capacity = ns;
}

void BACnetBitString::clear()
{
	pImpl->size = pImpl->length = 0;
	if(pImpl->capacity)
	{
		memset(pImpl->buffer, 0, pImpl->capacity);
	}
}

bool BACnetBitString::IsBitSet(U32 BitIndex)
{
	return (*this)[BitIndex];
}

bool GetBitValue(BACnetBitStringImpl* p, size_t BitIndex)
{
	size_t Byte = CalculateByteOffset(BitIndex);
	U8 Mask = CalculateBitMask(BitIndex);
	U8 target = p->buffer[Byte];
	return (target & Mask) == Mask;
}

bool BACnetBitString::IsBitClear(U32 BitIndex)
{
	if(BitIndex >= pImpl->length)
	{
		return false;
	}
	return GetBitValue(pImpl, BitIndex) == false;
}

bool BACnetBitString::operator[](size_t BitIndex)
{
	if(BitIndex >= pImpl->length)
	{
		return false;
	}
	return GetBitValue(pImpl, BitIndex);
}

BACnetBitString & BACnetBitString::operator=(const BACnetBitString & Other)
{
	if(pImpl == Other.pImpl) return *this;
	resize(Other.capacity());
	pImpl->length = Other.pImpl->length;
	pImpl->size = Other.pImpl->size;
	if(pImpl->size)
	{
		memcpy(pImpl->buffer, Other.pImpl->buffer, pImpl->size);
	}
	else
	{
		memset(pImpl->buffer, 0, pImpl->capacity);
	}
	return *this;
}

BACnetBitString & BACnetBitString::operator=(BACnetBitString && Other)
{
	std::swap(pImpl, Other.pImpl);
	return *this;
}
