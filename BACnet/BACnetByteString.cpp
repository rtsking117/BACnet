#include "BACnetByteString.h"
#include <memory>
#include <stdexcept>

struct BACnetByteStringImpl
{
	size_t size;
	size_t capacity;
	U8* buffer;

	BACnetByteStringImpl() :size(0), capacity(0), buffer(nullptr) {}
	explicit BACnetByteStringImpl(size_t newcap) : size(0), capacity(newcap), buffer(new U8[capacity])
	{
		memset(buffer, 0, capacity);
	}
	explicit BACnetByteStringImpl(size_t newcap, const void* data) : size(0), capacity(newcap), buffer(nullptr)
	{
		if(capacity)
		{
			buffer = new U8[capacity];
		}
		if(data)
		{
			memcpy(buffer, data, capacity);
			size = capacity;
		}
		else
		{
			memset(buffer, 0, capacity);
		}
	}
	~BACnetByteStringImpl() 
	{
		//if someone forgot to clean us up, do so now.
		if(buffer)
		{
			delete[] buffer;
			buffer = nullptr;
		}
		size = capacity = 0;
	}
};

BACnetByteString::BACnetByteString():
	pImpl(new BACnetByteStringImpl())
{
}

BACnetByteString::BACnetByteString(const void * pBuffer, size_t uiBufferLength):
	pImpl(nullptr)
{
	if(uiBufferLength < 0)
	{
		//throw now. do not initialize until we know we can do it safely.
		throw std::invalid_argument("uiBufferLength cannot be less than one byte.");
	}
	pImpl = new BACnetByteStringImpl(uiBufferLength, pBuffer);
}

BACnetByteString::BACnetByteString(const BACnetByteString & Other) : 
	pImpl(new BACnetByteStringImpl(Other.pImpl->capacity, Other.pImpl->buffer))
{
}


BACnetByteString::BACnetByteString(BACnetByteString && Other):
	pImpl(std::move(Other.pImpl))
{
	Other.pImpl = nullptr;
}

BACnetByteString::~BACnetByteString()
{
	if(pImpl)
	{
		delete pImpl;
		pImpl = nullptr;
	}
}

size_t BACnetByteString::length() const
{
	return pImpl->size;
}

size_t BACnetByteString::size() const
{
	return pImpl->size;
}

size_t BACnetByteString::bytes() const
{
	return pImpl->size;
}

size_t BACnetByteString::capacity() const
{
	return pImpl->capacity;
}

void * BACnetByteString::buffer() const
{
	return pImpl->buffer;
}

void BACnetByteString::resize(size_t NewSize)
{
	if(NewSize < capacity())
	{
		return;
	}
	U8* temp = pImpl->buffer;
	pImpl->buffer = new U8[NewSize];
	if(temp)
	{
		memcpy(pImpl->buffer, temp, pImpl->capacity);
		delete[] temp;
	}
	pImpl->capacity = NewSize;
}

void BACnetByteString::clear()
{
	pImpl->size = 0;
	if(pImpl->capacity)
	{
		memset(pImpl->buffer, 0, pImpl->capacity);
	}
}

U8 BACnetByteString::operator[](size_t ByteIndex)
{
	if(ByteIndex > pImpl->size)
	{
		return 0;
	}
	return pImpl->buffer[ByteIndex];
}

BACnetByteString & BACnetByteString::operator=(const BACnetByteString & Other)
{
	if(pImpl == Other.pImpl) return *this;
	resize(Other.capacity());
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

BACnetByteString & BACnetByteString::operator=(BACnetByteString && Other)
{
	std::swap(pImpl, Other.pImpl);
	return *this;
}

BACnetByteString BACnetByteString::operator+(const BACnetByteString & Other) const
{
	BACnetByteString ret(*this);
	return ret += Other;
}

BACnetByteString BACnetByteString::operator+(BACnetByteString && Other) const
{
	BACnetByteString ret(*this);
	return ret += Other;
}

BACnetByteString & BACnetByteString::operator+=(const BACnetByteString & Other)
{
	resize(pImpl->size + Other.pImpl->size);
	memcpy(pImpl->buffer + pImpl->size, Other.pImpl->buffer, (Other.pImpl->size));
	pImpl->size += Other.pImpl->size;
	return *this;
}

BACnetByteString & BACnetByteString::operator+=(BACnetByteString && Other)
{
	resize(pImpl->size + Other.pImpl->size);
	memcpy(pImpl->buffer + pImpl->size, Other.pImpl->buffer, (Other.pImpl->size));
	pImpl->size += Other.pImpl->size;
	return *this;
}
