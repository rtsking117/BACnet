#pragma once

#include <APDU/Common/BACnetBasicTypes.inl>

//Unconfirmed Text Message
class UnconfirmedTextMessageRequest : public
	BACnetSequence<
		BACnetSequenceElement<0, BACnetObjectIDType>,
		BACnetSequenceElement<1,
			BACnetChoice<NoDefault,
				BACnetChoiceElement<0, BACnetUnsignedType>,
				BACnetChoiceElement<1, BACnetCharacterStringType>
			>, true
		>,
		BACnetSequenceElement<2, BACnetEnumeratedType>,
		BACnetSequenceElement<3, BACnetCharacterStringType>
	>
{
public:

	bool IsValid()
	{
		return !is_present<1>() || get<1>().IsValid();
	}

	BACnetObjectID GetSourceDevice()
	{
		return get<0>().get();
	}

	bool HasMessageClass()
	{
		return is_present<1>();
	}

	bool IsMessageClassNumeric()
	{
		return HasMessageClass() && get<1>().is_selected(0);
	}

	bool IsMessageClassString()
	{
		return HasMessageClass() && get<1>().is_selected(1);
	}

	U32 GetMessageClassID()
	{
		if(!IsMessageClassNumeric())
		{
			return 0;
		}
		return get<1>().get<0>().get();
	}

	BACnetString GetMessageClassString()
	{
		if(!IsMessageClassString())
		{
			return BACnetString("");
		}
		return get<1>().get<1>().get();
	}

	U32 GetMessagePriority()
	{
		return get<2>().get();
	}

	BACnetString GetMessageText()
	{
		return get<3>().get();
	}

	void SetSourceDevice(BACnetObjectID SourceDevice)
	{
		get<0>().set(SourceDevice);
	}

	void SetMessageClassID(U32 MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(0);
		get<1>().get<0>().set(MessageClass);
	}

	void SetMessageClassString(BACnetString MessageClass)
	{
		make_present<1>(true);
		get<1>().make_selected(1);
		get<1>().get<1>().set(MessageClass);
	}

	void ClearMessageClass()
	{
		make_present<1>(false);
	}

	void SetMessagePriority(U32 Priority)
	{
		get<2>().set(Priority);
	}

	void SetMessageText(const BACnetString& MessageText)
	{
		get<3>().set(MessageText);
	}
};
