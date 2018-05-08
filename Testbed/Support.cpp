
#include "Testbed.h"
#include "Support.h"

void PrintTabs(int ntabs)
{
	for(int i = 0; i < ntabs; ++i)
	{
		cout << '\t';
	}
}

void PrintData(U8* pData, U32 nData)
{
	for(U32 i = 0; i < nData; ++i)
	{
		cout << hex << setfill('0') << setw(2) << (int)pData[i] << " ";
	}
}

const char* valtbl[] = {
	"Null",
	"Boolean",
	"Unsigned Integer",
	"Signed Integer",
	"Single Precision Floating Point",
	"Double Precision Floating Point",
	"Octet String",
	"Character String",
	"Bit String",
	"Enumeration",
	"Date",
	"Time",
	"BACnet Object Identifier",
	"Reserved",
	"Reserved",
	"Reserved",
	"Context-Tagged Value",
	"Constructed Value",
	"Parser Root Element",
};

const char* ConvertValueTypeToString(U8 Type)
{
	if(Type > ARRAYSIZE(valtbl))
	{
		return "Unknown";
	}
	return valtbl[Type];
}

const char* months[] = {
	"None",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
};

const char* weekdays[] = {
	"None",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday",
};

const char* enctbl[] = {
	"UTF-8",
	"Microsoft DBCS",
	"JIS X 0208",
	"UCS-4",
	"UCS-2",
	"ISO 8859-1"
};

const char* ConvertEncodingToString(U8 Encoding)
{
	if(Encoding > ARRAYSIZE(enctbl))
	{
		return "Unknown Encoding";
	}
	return enctbl[Encoding];
}

const char* typetbl[] = {
	"Analog Input",
	"Analog Output",
	"Analog Value",
	"Binary Input",
	"Binary Output",
	"Binary Value",
	"Calendar",
	"Command",
	"Device",
	"Event Enrollment",
	"File",
	"Group",
	"Loop",
	"Multi-State Input",
	"Multi-State Output",
	"Notification Class",
	"Program",
	"Schedule",
	"Averaging",
	"Multi-State Value",
	"Trend Log",
	"Life Safety Point",
	"Life Safety Zone",
	"Accumulator",
	"Pulse Converter",
	"Event Log",
	"Global Group",
	"Trend Log - Multiple",
	"Load Control",
	"Structured View",
	"Access Door",
	"Unassigned",
	"Access Credential",
	"Access Point",
	"Access Rights",
	"Access User",
	"Access Zone",
	"Credential Data Input",
	"Network Security",
	"Bitstring Value",
	"Character String Value",
	"Date Pattern Value",
	"Date Value",
	"Date-Time Pattern Value",
	"Date-Time Value",
	"Integer Value",
	"Large Analog Value",
	"Octet String Value",
	"Positive Integer Value",
	"Time Pattern Value",
	"Time Value",
	"Notification Forwarder",
	"Alert Enrollment",
	"Channel",
	"Lighting Output",
};

const char* ConvertObjectTypeToString(U32 type)
{
	if(type > ARRAYSIZE(typetbl))
	{
		if(type < 128)
		{
			return "Reserved By ASHRAE";
		}
		else
		{
			return "Private Object Type";
		}
	}
	return typetbl[type];
}

void PrintValue(U8 Type, U32 DataLength, U8* data, int ntabs)
{
	switch(Type)
	{
	case ValueType_Null:
		PrintTabs(ntabs);
		if(DataLength != 0)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			cout << "None" << endl;
		}
		return;
	case ValueType_Boolean:
		PrintTabs(ntabs);
		if(DataLength != 1)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			if(data[0] == 1)
			{
				cout << "True" << endl;
			}
			else
			{
				cout << "False" << endl;
			}
		}
		return;
	case ValueType_Unsigned:
		PrintTabs(ntabs);
		if(DataLength < 1 || DataLength > 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			U32 tval = 0;
			for(U32 i = 0; i < DataLength; ++i)
			{
				tval <<= 8;
				tval |= data[i];
			}
			cout << dec << tval << endl;
		}
		return;
	case ValueType_Signed:
		PrintTabs(ntabs);
		if(DataLength < 1 || DataLength > 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			U32 tval = 0;
			if(data[0] & 0x80)
			{
				tval = -1;
			}
			for(U32 i = 0; i < DataLength; ++i)
			{
				tval <<= 8;
				tval |= data[i];
			}
			cout << dec << (I32)tval << endl;
		}
		return;
	case ValueType_Real:
		PrintTabs(ntabs);
		if(DataLength != 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			union fstr
			{
				float f;
				U32 u;
			} tval;
			tval.u = 0;
			for(U32 i = 0; i < DataLength; ++i)
			{
				tval.u <<= 8;
				tval.u |= data[i];
			}
			cout <<dec << tval.f << endl;
		}
		return;
	case ValueType_Double:
		PrintTabs(ntabs);
		if(DataLength != 8)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			union dstr
			{
				double f;
				U64 u;
			} tval;
			tval.u = 0;
			for(U32 i = 0; i < DataLength; ++i)
			{
				tval.u <<= 8;
				tval.u |= data[i];
			}
			cout << dec << tval.f << endl;
		}
		return;
	case ValueType_OctetString:
		PrintTabs(ntabs);
		PrintData(data, DataLength);
		cout << endl;
		return;
	case ValueType_CharacterString:
		PrintTabs(ntabs);
		if(DataLength < 1)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			cout << "Encoding: " << ConvertEncodingToString(data[0]) << endl;
			PrintTabs(ntabs);
			if(DataLength - 1)
			{
				cout << "String: ";
				cout.write((char*)&data[1], DataLength - 1) << endl;
			}
			else
			{
				cout << "No String Data" << endl;
			}
		}
		return;
	case ValueType_BitString:
		PrintTabs(ntabs);
		if(DataLength < 1)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			cout << "Unused Bits: " << dec << (int)data[0] << endl;
			PrintTabs(ntabs);
			if(DataLength - 1)
			{
				cout << "Bits: ";
				PrintData(&data[1], DataLength - 1);
				cout << endl;
			}
			else
			{
				cout << "No Bit String Data" << endl;
			}
		}
		return;
	case ValueType_Enumerated:
		PrintTabs(ntabs);
		if(DataLength < 1 || DataLength > 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			U32 tval = 0;
			for(U32 i = 0; i < DataLength; ++i)
			{
				tval <<= 8;
				tval |= data[i];
			}
			cout << dec << tval << endl;
		}
		return;
	case ValueType_Date:
		PrintTabs(ntabs);
		if(DataLength != 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			cout << ((data[3] == 0xFF) ? "Any" : weekdays[(data[3])]) << ", ";
			cout << ((data[1] == 0xFF) ? "Any" : months[(data[1])]) << " ";
			if(data[2] == 0xFF)
			{
				cout << "Any";
			}
			else
			{
				cout << dec << (data[2]);
			}
			cout << ", ";
			if(data[0] == 0xFF)
			{
				cout << "Any";
			}
			else
			{
				cout << dec << (data[0] + 1900);
			}
			cout << endl;
		}
		return;
	case ValueType_Time:
		PrintTabs(ntabs);
		if(DataLength != 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			if(data[0] == 0xFF)
			{
				cout << "Any";
			}
			else
			{
				cout << (data[0]);
			}
			cout << ":";
			if(data[1] == 0xFF)
			{
				cout << "Any";
			}
			else
			{
				cout << (data[1]);
			}
			cout << ":";
			if(data[2] == 0xFF)
			{
				cout << "Any";
			}
			else
			{
				cout << (data[2]);
			}
			cout << ":";
			if(data[3] == 0xFF)
			{
				cout << "Any";
			}
			else
			{
				cout << (data[3]);
			}
			cout << endl;
		}
		return;
	case ValueType_ObjectID:
		PrintTabs(ntabs);
		if(DataLength != 4)
		{
			cout << "Invalid Encoding" << endl;
		}
		else
		{
			U32 tval = 0;
			for(U32 i = 0; i < DataLength; ++i)
			{
				tval <<= 8;
				tval |= data[i];
			}
			cout << "(" << ConvertObjectTypeToString(((tval & 0xFFC00000) >> 22)) << ", " << dec << (int)(tval & 0x003FFFFF) << ")" << endl;
		}
		return;
	default:
		PrintTabs(ntabs);
		cout << "Value type undefined" << endl;
	}
}

const char* CRTable[] = {
	"Acknowledge Alarm",
	"Confirmed COV Notification",
	"Confirmed Event Notification",
	"Get Alarm Summary",
	"Get Enrollment Summary",
	"Subscribe COV",
	"Atomic Read File",
	"Atomic Write File",
	"Add List Element",
	"Remove List Element",
	"Create Object",
	"Delete Object",
	"Read Property",
	"Read Property Conditional (Obsolete)"
	"Read Property Multiple",
	"Write Property",
	"Write Property Multiple",
	"Device Communication Control",
	"ConfirmedPrivate Transfer",
	"ConfirmedText Message",
	"Reinitialize Device",
	"VT Open",
	"VT Close",
	"VT Data",
	"Authenticate (Obsolete)",
	"Request Key (Obsolete)",
	"Read Range",
	"Life Safety Operation",
	"Subscribe COV Property",
	"Get Event Information",
};

const char* URTable[] = {
	"I Am",
	"I Have",
	"Unconfirmed COV Notification",
	"Unconfirmed Event Notification",
	"Unconfirmed Private Transfer",
	"Unconfirmed Text Message",
	"Time Synchronization",
	"Who Has",
	"Who Is",
	"UTC Time Synchronization",
	"Write Group",
};

const char * ConvertServiceToString(U8 ServiceChoice, bool IsConfirmed)
{
	if(IsConfirmed)
	{
		if(ServiceChoice > ARRAYSIZE(CRTable))
		{
			return "Invalid Confirmed Choice";
		}
		return CRTable[ServiceChoice];
	}
	else
	{
		if(ServiceChoice > ARRAYSIZE(URTable))
		{
			return "Invalid Unconfirmed Choice";
		}
		return URTable[ServiceChoice];
	}
}

void PrintBACnetValue(const BACnetValue &v, int ntabs)
{
	PrintTabs(ntabs);
	cout << "Type: " << ConvertValueTypeToString(v.GetType()) << endl;
	if(v.IsUntaggedData())
	{
		PrintTabs(ntabs);
		cout << "Value: " << endl;
		PrintValue(v.GetType(), v.GetDataLength(), (U8*)v.GetBuffer(), ntabs + 1);
	}
	else
	{
		PrintTabs(ntabs);
		cout << "Tag: " << dec << (int)v.GetTag() << endl;
		if(v.IsConstructedData())
		{
			for(U32 i = 0; i < v.GetNumElements(); ++i)
			{
				PrintBACnetValue(v.GetElement(i), ntabs + 1);
			}
		}
		else
		{
			PrintTabs(ntabs + 1);
			cout << "Data Length: " << v.GetDataLength() << endl;
			PrintTabs(ntabs + 1);
			cout << "Data: ";
			PrintData((U8*)v.GetBuffer(), v.GetDataLength());
			cout << endl;
		}
	}
}