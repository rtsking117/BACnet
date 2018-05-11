#pragma once

#include "BACnetBasicTypes.inl"

//=============================================================================================
//								FILE SERVICES
//=============================================================================================

//Read File
class ReadFileRequest : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>
					>
				>,
				BACnetChoiceElement<1,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>
					>
				>
			>, false
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

//Read File Ack
class ReadFileResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetBooleanType, false>,
			BACnetSequenceElement<NoTag,
				BACnetChoice<NoDefault,
					BACnetChoiceElement<0,
						BACnetSequence<
							BACnetSequenceElement<NoTag, BACnetSignedType, false>,
							BACnetSequenceElement<NoTag, BACnetOctetStringType, false>
						>
					>,
					BACnetChoiceElement<1,
						BACnetSequence<
							BACnetSequenceElement<NoTag, BACnetSignedType, false>,
							BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
							BACnetSequenceElement<NoTag,
								BACnetSequenceOf<BACnetOctetStringType>, false
							>
						>
					>
			>, false
		>
	>
{

public:

	bool IsValid()
	{
		if(IsRecordBased())
		{
			if(GetRecordCount() != GetRecordData().size())
			{
				return false;
			}
		}
		return true;
	}

	bool IsEndOfFile()
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

	I32 GetStartPosition()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<0>().get();
	}

	BACnetByteString GetFileData()
	{
		if(!IsStreamBased())
		{
			return BACnetByteString(nullptr, 0);
		}
		return get<1>().get<0>().get<1>().get();
	}

	I32 GetStartRecord()
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

	std::vector<BACnetByteString> GetRecordData()
	{
		if(!IsRecordBased())
		{
			return {};
		}
		std::vector<BACnetByteString> ret;
		auto v = get<1>().get<1>().get<2>().get_list();
		for each(auto i in v)
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	void SetEndOfFile()
	{
		get<0>().set(true);
	}

	void ClearEndOfFile()
	{
		get<0>().set(false);
	}

	void SetStreamOffsetAndData(I32 Offset, BACnetByteString Data)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().get<0>().set(Offset);
		get<1>().get<0>().get<1>().set(Data);
	}

	void SetStartRecordAndData(I32 StartRecord, std::vector<BACnetByteString> Data)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().get<0>().set(StartRecord);
		get<1>().get<1>().get<1>().set((U32)Data.size());
		for(U32 i = 0; i < (U32)Data.size(); ++i)
		{
			get<1>().get<1>().get<2>().get(i).set(Data.at(i));
		}
	}
};

//Write File
class WriteFileRequest : public
	BACnetSequence <
		BACnetSequenceElement<NoTag, BACnetObjectIDType, false>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetOctetStringType, false>
					>
				>,
				BACnetChoiceElement<1,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetSignedType, false>,
						BACnetSequenceElement<NoTag, BACnetUnsignedType, false>,
						BACnetSequenceElement<NoTag,
							BACnetSequenceOf<BACnetOctetStringType>,
						false>
					>
				>
			>, false
		>
	>
{

public:

	bool IsValid()
	{
		if(IsRecordBased())
		{
			if(GetRecordCount() != GetRecordData().size())
			{
				return false;
			}
		}
		return true;
	}

	BACnetObjectID GetObjectID()
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

	I32 GetStartPosition()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<1>().get<0>().get<0>().get();
	}

	BACnetByteString GetFileData()
	{
		if(!IsStreamBased())
		{
			return BACnetByteString(nullptr, 0);
		}
		return get<1>().get<0>().get<1>().get();
	}

	I32 GetStartRecord()
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

	std::vector<BACnetByteString> GetRecordData()
	{
		if(!IsRecordBased())
		{
			return {};
		}
		std::vector<BACnetByteString> ret;
		auto v = get<1>().get<1>().get<2>().get_list();
		for each(auto i in v)
		{
			ret.push_back(i.get());
		}
		return ret;
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetStreamOffsetAndData(I32 Offset, BACnetByteString Data)
	{
		get<1>().make_selected(0);
		get<1>().get<0>().get<0>().set(Offset);
		get<1>().get<0>().get<1>().set(Data);
	}

	void SetStartRecordAndData(I32 StartRecord, std::vector<BACnetByteString> Data)
	{
		get<1>().make_selected(1);
		get<1>().get<1>().get<0>().set(StartRecord);
		get<1>().get<1>().get<1>().set((U32)Data.size());
		for(U32 i = 0; i < (U32)Data.size(); ++i)
		{
			get<1>().get<1>().get<2>().get(i).set(Data.at(i));
		}
	}

};

//Write File Ack
class WriteFileResponse : public
	BACnetChoice<NoDefault,
		BACnetChoiceElement<0, BACnetSignedType>,
		BACnetChoiceElement<1, BACnetSignedType>
	>
{
public:

	bool IsStreamBased()
	{
		return is_selected(0);
	}

	bool IsRecordBased()
	{
		return is_selected(1);
	}

	I32 GetNewStreamPosition()
	{
		if(!IsStreamBased())
		{
			return 0;
		}
		return get<0>().get();
	}

	I32 GetNewRecordNumber()
	{
		if(!IsRecordBased())
		{
			return 0;
		}
		return get<1>().get();
	}

	void SetNewStreamPosition(I32 NewPosition)
	{
		make_selected(0);
		get<0>().set(NewPosition);
	}

	void SetNewRecordNumber(I32 NewRecordNumber)
	{
		make_selected(1);
		get<1>().set(NewRecordNumber);
	}
};
