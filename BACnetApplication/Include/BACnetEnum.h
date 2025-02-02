#pragma once

enum class BACnetSegmentation
{
	Both = 0,
	TXOnly = 1,
	RXOnly = 2,
	None = 3
};

enum class BACnetEventType
{
	ChangeOfBitstring = 0,
	ChangeOfState = 1,
	ChangeOfValue = 2,
	CommandFailure = 3,
	FloatingLimit = 4,
	OutOfRange = 5,
	__ComplexEventType = 6,
	Deprecated7 = 7,
	ChangeOfLifeSafety = 8,
	Extended = 9,
	BufferReady = 10,
	UnsignedRange = 11,
	Reserved12 = 12,
	AccessEvent = 13,
	DoubleOutOfRange = 14,
	SignedOutOfRange = 15,
	UnsignedOutOfRange = 16,
	ChangeOfCharacterString = 17,
	ChangeOfStatusFlags = 18,
	ChangeOfReliability = 19,
	None = 20,
	ChangeOfDiscreteValue = 21,
	ChangeOfTimer = 22,

	VendorBegin = 64,
	VendorEnd = 65535,
};