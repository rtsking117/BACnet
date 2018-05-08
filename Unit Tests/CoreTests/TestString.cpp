#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTests
{
	/*
	cout << "-----------------TESTING BACnetString CLASS---------------------" << endl;
	BACnetString str = BACnetString("Hello");
	BACnetString str2 = BACnetString("World");
	cout << str << " (" << str.length() << ")" << endl;
	cout << str2 << " (" << str2.length() << ")" << endl;
	BACnetString str3 = (str + " " + str2);
	cout << str3 << " (" << str3.length() << ")" << endl;
	cout << f("function") << endl;
	char * test = u8"Hello\uFE45 World!";
	cout << "0x2012: " << hex << BACnetString("8210").ParseInt() << endl;
	cout << "2234: " << dec << BACnetString("04272").ParseInt() << endl;
	cout << "07667: " << oct << BACnetString("0xFB7").ParseInt() << endl;
	cout << "5A: " << hex << BACnetString("0b01011010").ParseInt() << endl;
	cout << u8"Unicode - 48597: " << dec << BACnetString(u8"\u07C4\u0A6E\u19D5\u1C49\uFF17").ParseInt() << endl;
	cout << "Parse number from string pos 5 (hello|245world): " << dec << BACnetString("hello245world").ParseInt(5) << endl;
	cout << "Parse number with simple whitespace (  3345test): " << dec << BACnetString("  3345test").ParseInt() << endl;
	cout << "Parse number with complex whitespace (\\t\\n\\r\\u00A0\\u200D 234): " << dec << BACnetString(u8"\t\n\r\u00A0\u200D 234").ParseInt() << endl;
	cout << "Parse negative number (-35): " << dec << BACnetString("-35").ParseInt() << endl;
	cout << "Parse positive number (+73): " << dec << BACnetString("+73").ParseInt() << endl;
	cout << "ToString (binary): " << BACnetString::ToString(0x88045775, 2) << endl;
	cout << "ToString (hex): " << BACnetString::ToString(0x88045775, 16) << endl;
	cout << "ToString (octal): " <<  BACnetString::ToString(0x88045775, 8) << endl;
	cout << "ToString (dec): " << BACnetString::ToString(0x88045775) << endl;
	cout << "----------------------------------------------------------------" << endl;
	
	*/

	TEST_CLASS(TestUTF8Conversions)
	{
	public:
		
		TEST_METHOD(ConvertFromUTF8)
		{
			BACnetString str;
			const char* lit = "source";
			str.FromUTF8((const U8*)lit);
		}

	};
}