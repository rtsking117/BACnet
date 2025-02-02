#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Read File
class ReadFileRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType>
					>
				>,
				BACnetChoiceElement<1,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType>
					>
				>
			>
		>
	>
{
public:

	BACnetObjectID GetObject()
	{
		return get<0>().get();
	}

	bool IsStreamBased()
	{
		return get<1>().is_selected(0);
	}

	bool IsRecordBased()
	{
		return get<1>().is_selected(1);
	}

	I32 GetByteOffset()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<0>().get();
	}

	U32 GetByteCount()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<1>().get();
	}

	I32 GetStartingRecord()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<0>().get();
	}

	U32 GetRecordCount()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get<1>().get<1>().get();
	}

	void SetObject(BACnetObjectID Object)
	{
		get<0>().set(Object);
	}

	void SetOffsetAndSize(I32 ByteOffset, U32 ByteSize)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().get<0>().set(ByteOffset);
		get<1>().get<0>().get<1>().set(ByteSize);
	}

	void SetRecordAndCount(I32 StartingRecord, U32 RecordCount)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().get<0>().set(StartingRecord);
		get<1>().get<1>().get<1>().set(RecordCount);
	}
};
