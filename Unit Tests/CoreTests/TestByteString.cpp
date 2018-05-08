#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTests
{
	/*
	cout << "-----------------TESTING BACnetByteString CLASS-----------------" << endl;
	U8 buf[16];
	CryptGenRandom(prov, sizeof(buf), buf);
	BACnetByteString os(buf, sizeof(buf));
	cout << "size: " << os.size() << ", length: " << os.length() << ", capacity: " << os.capacity() << endl;
	cout << "buffer ptr: " << os.buffer() << endl;
	cout << "Buffer data: " << endl;
	PrintBytes((U8*)os.buffer(), os.size());
	cout << "Byte at 8: " << hex << (U32)((U8*)os.buffer())[8] << " vs " << (U32)os[8] << endl;
	cout << "----------------------------------------------------------------" << endl;
	*/
	TEST_CLASS(ByteStringTests)
	{
	public:
		TEST_METHOD(ByteStringAssignment)
		{

		}
	};
};