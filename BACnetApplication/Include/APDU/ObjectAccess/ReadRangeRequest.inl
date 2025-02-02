#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>
#include <APDU/Common/BACnetDateTime.inl>

//Read Range
class ReadRangeRequest : public
	BACnetSequence <
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1, BACnetEnumeratedType>,
		BACnetSequenceElement<2, BACnetUnsignedType, true>,
		BACnetSequenceElement<NoTag,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<3,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetUnsignedType>,
						BACnetSequenceElement<NoTag, BACnetSigned16Type>
					>
				>,
				BACnetChoiceElement<6,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetUnsignedType>,
						BACnetSequenceElement<NoTag, BACnetSigned16Type>
					>
				>,
				BACnetChoiceElement<7,
					BACnetSequence<
						BACnetSequenceElement<NoTag, BACnetDateTimeType>,
						BACnetSequenceElement<NoTag, BACnetSigned16Type>
					>
				>
			>, true
		>
	>
{
public:
	BACnetObjectID GetObjectID()
	{
		return get<0>().get();
	}

	U32 GetProperty()
	{
		return get<1>().get();
	}

	bool HasArrayIndex()
	{
		return is_present<2>();
	}

	U32 GetArrayIndex()
	{
		if (HasArrayIndex())
		{
			return InvalidIndex;
		}
		return get<2>().get();
	}

	bool HasRange()
	{
		return is_present<3>();
	}

	bool IsRangePosition()
	{
		return HasRange() && get<3>().is_selected(0);
	}

	U32 GetReferenceIndex()
	{
		if (!IsRangePosition())
		{
			return 0;
		}
		return get<3>().get<0>().get<0>().get();
	}

	bool IsRangeSequenceNumber()
	{
		return HasRange() && get<3>().is_selected(1);
	}

	U32 GetReferenceSequenceNumber()
	{
		if (!IsRangeSequenceNumber())
		{
			return 0;
		}
		return get<3>().get<1>().get<0>().get();
	}

	bool IsRangeTime()
	{
		return HasRange() && get<3>().is_selected(2);
	}

	BACnetDateTimeType GetReferenceTime()
	{
		if (!IsRangeTime())
		{
			return BACnetDateTimeType();
		}
		return get<3>().get<2>().get<0>();
	}

	I16 GetCount()
	{
		if (IsRangePosition())
		{
			return get<3>().get<0>().get<1>().get();
		}
		else if (IsRangeSequenceNumber())
		{
			return get<3>().get<1>().get<1>().get();
		}
		else if (IsRangeTime())
		{
			return get<3>().get<2>().get<1>().get();
		}
		else
		{
			return 0;
		}
	}

	void SetObjectID(BACnetObjectID ObjectID)
	{
		get<0>().set(ObjectID);
	}

	void SetProperty(U32 PropertyID)
	{
		get<1>().set(PropertyID);
	}

	void SetArrayIndex(U32 ArrayIndex)
	{
		make_present<2>(true);
		get<2>().set(ArrayIndex);
	}

	void ClearArrayIndex()
	{
		make_present<2>(false);
	}

	void SetPositionRange(U32 StartIndex, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(0);
		get<3>().get<0>().get<0>().set(StartIndex);
		get<3>().get<0>().get<1>().set(Count);
	}

	void SetSequenceNumberRange(U32 StartSequenceNumber, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(1);
		get<3>().get<1>().get<0>().set(StartSequenceNumber);
		get<3>().get<1>().get<1>().set(Count);
	}

	void SetTimeRange(BACnetDateTimeType StartTime, I16 Count)
	{
		make_present<3>(true);
		get<3>().make_selected(2);
		get<3>().get<2>().get<0>() = StartTime;
		get<3>().get<2>().get<1>().set(Count);
	}

	void ClearRange()
	{
		make_present<3>(false);
	}
};
