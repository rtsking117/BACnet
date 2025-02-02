#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Read File Ack
class ReadFileResponse : public
	BACnetSequence<
		BACnetSequenceElement<NoTag, BACnetBooleanType>,
			BACnetSequenceElement<NoTag,
				BACnetChoice<NoDefault,
					BACnetChoiceElement<0,
						BACnetSequence<
							BACnetSequenceElement<NoTag, BACnetSignedType>,
							BACnetSequenceElement<NoTag, BACnetOctetStringType>
						>
					>,
					BACnetChoiceElement<1,
						BACnetSequence<
							BACnetSequenceElement<NoTag, BACnetSignedType>,
							BACnetSequenceElement<NoTag, BACnetUnsignedType>,
							BACnetSequenceElement<NoTag, BACnetSequenceOf<BACnetOctetStringType>>
						>
					>
			>
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
