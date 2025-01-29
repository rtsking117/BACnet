#pragma once

#include <cassert>
#include "ASN1.h"
#include "BACnetApplication.h"

template<typename...>
struct is_bacnet_template : public std::false_type { };

template<typename T>
constexpr bool is_bacnet_template_v = is_bacnet_template<T>::value;

template<typename...> 
struct is_application : public std::false_type { };

template<typename T>
constexpr bool is_application_v = is_application<T>::value;

template<typename...>
struct is_choice : public std::false_type { };

template<typename T>
constexpr bool is_choice_v = is_choice<T>::value;

template<typename...>
struct is_choice_element : public std::false_type { };

template<typename T>
constexpr bool is_choice_element_v = is_choice_element<T>::value;

template<typename...>
struct is_sequence : public std::false_type { };

template<typename T>
constexpr bool is_sequence_v = is_sequence<T>::value;

template<typename...>
struct is_sequence_element : public std::false_type { };

template<typename T>
constexpr bool is_sequence_element_v = is_sequence_element<T>::value;

static const U8 NoTag = 0xFF;

/*
Application value.
Used for Enumerated, Date, Time, ObjectID, Unsigned, etc.
Values here can be tagged or untagged, but are always primitive data.
*/
template<BACnetValueType ValueType, typename CPPType>
class BACnetApplicationValue
{
	CPPType v;
public:

	BACnetApplicationValue() = default;
	explicit BACnetApplicationValue(const CPPType& InitialValue) : v(InitialValue) {}

	CPPType get()
	{
		return v;
	}

	bool set(CPPType val)
	{
		v = val;
		return true;
	}

	bool IsValid()
	{
		return true;
	}

	BACnetResult Decode(const BACnetValue &value)
	{	
		return ASN1::Codec<ValueType, CPPType>::Decode(value, v);
	}
	BACnetResult Decode(const BACnetValue& value, U32& index)
	{
		return Decode(value.GetElement(index++));
	}

	BACnetResult Encode(BACnetValue &value)
	{
		return ASN1::Codec<ValueType, CPPType>::Encode(value, v);
	}

};

template<BACnetValueType VT, typename T>
struct is_bacnet_template<BACnetApplicationValue<VT, T>> : public std::true_type {};

static_assert(is_bacnet_template_v<BACnetApplicationValue<ValueType_Unsigned, U16>> == true, "is_bacnet_template does not return true on BACnetApplicationValue");

template<BACnetValueType VT, typename T>
struct is_application<BACnetApplicationValue<VT,T>> : public std::true_type {};

static_assert(is_application_v<BACnetApplicationValue<ValueType_Boolean, bool>> == true, "is_application does not return true on BACnetApplicationValue");

//specialization of the above for NULL
template<>
class BACnetApplicationValue<ValueType_Null, void>
{
public:

	int get()
	{
		return 0;
	}

	bool set()
	{
		//(void)val;
		return true;
	}

	bool IsValid()
	{
		return true;
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		if(value.GetType() != ValueType_Null)
		{
			return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
		}
		return BC_OK;
	}
	BACnetResult Decode(const BACnetValue& value, U32& index)
	{
		return Decode(value.GetElement(index++));
	}

	BACnetResult Encode(BACnetValue &value)
	{
		value.SetType(ValueType_Null);
		return BC_OK;
	}
};

static_assert(is_bacnet_template_v<BACnetApplicationValue<ValueType_Null, void>> == true, "is_bacnet_template does not return true on BACnetApplicationValue<Null>");
static_assert(is_application_v<BACnetApplicationValue<ValueType_Null, void>> == true, "is_application does not return true on BACnetApplicationValue<Null>");

/*
ANY type
Used for all <<<CONTEXT TAGGED>>> ABSTRACT_SYNTAX&Type in chapter 21
There are two places where ANY is specified with no associated tag - these
 cannot use this class as it will cause compile time errors.
*/
class BACnetAnyType
{
	BACnetValue v;
public:

	BACnetAnyType() = default;
	explicit BACnetAnyType(const BACnetValue& InitialValue) : v(InitialValue) {}

	BACnetValue get()
	{
		return v;
	}

	bool set(const BACnetValue &val)
	{
		v = val;
		return true;
	}
	
	bool IsValid()
	{
		return v.IsValueValid();
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		v = value;
		return BC_OK;
	}

	BACnetResult Decode(const BACnetValue& value, U32& index)
	{
		return Decode(value.GetElement(index++));
	}

	BACnetResult Encode(BACnetValue &value)
	{
		value = v;
		return BC_OK;
	}
};

template<>
struct is_bacnet_template<BACnetAnyType> : public std::true_type {};

static_assert(is_bacnet_template_v<BACnetAnyType> == true, "is_bacnet_template does not return true on BACnetAnyType");

static_assert(is_application_v<BACnetAnyType> == false, "is_application does not return false on BACnetAnyType");

/*
"Specialization" of BACnetAnyType specifically for use in BACnetTimeValue.
This is only used in schedules. 
*/
class BACnetApplicationAnyType
{
	BACnetValue v;
public:

	BACnetApplicationAnyType() = default;
	explicit BACnetApplicationAnyType(const BACnetValue& InitialValue) : v(InitialValue) {}

	BACnetValue get()
	{
		return v;
	}

	bool set(BACnetValue &val)
	{
		if(!val.IsPrimitiveData())
		{
			return false;
		}
		v = val;
		return true;
	}

	bool IsValid()
	{
		return v.IsValueValid() && v.IsPrimitiveData();
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		if(!value.IsPrimitiveData())
		{
			return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
		}
		v = value;
		return BC_OK;
	}

	BACnetResult Decode(const BACnetValue& value, U32& index)
	{
		return Decode(value.GetElement(index++));
	}

	BACnetResult Encode(BACnetValue &value)
	{
		value = v;
		return BC_OK;
	}
};

template<>
struct is_bacnet_template<BACnetApplicationAnyType> : public std::true_type {};

static_assert(is_bacnet_template_v<BACnetApplicationAnyType> == true, "is_bacnet_template does not return true on BACnetApplicationAnyType");

template<>
struct is_application<BACnetApplicationAnyType> : public std::true_type { };

static_assert(is_application_v<BACnetApplicationAnyType> == true, "is_application does not return true on BACnetApplicationAnyType");

/*
"Specialization" of BACnetAnyType specifically for use in BACnetNameValue.
This is used for supporting tags.
*/
class BACnetApplicationAnyDateTimeType
{
	BACnetValue v;
public:

	BACnetApplicationAnyDateTimeType() = default;
	explicit BACnetApplicationAnyDateTimeType(const BACnetValue& InitialValue) : v(InitialValue) {}

	BACnetValue get()
	{
		return v;
	}

	bool set(BACnetValue &val)
	{
		if(!val.IsPrimitiveData())
		{
			if(val.GetNumElements() != 2 || (val.GetElement(0).GetTag() != ValueType_Date || val.GetElement(1).GetTag() != ValueType_Time))
			{
				return false;
			}
		}
		v = val;
		return true;
	}

	bool IsValid()
	{
		return v.IsValueValid();
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		if(!value.IsPrimitiveData())
		{
			return BCE_REJECT_INVALID_PARAMETER_DATATYPE;
		}
		v = value;
		return BC_OK;
	}

	BACnetResult Decode(const BACnetValue& value, U32& index)
	{
		BACnetValue v1 = value.GetElement(index++);
		if(v1.GetTag() == ValueType_Date)
		{
			if(value.GetNumElements() > index)
			{
				BACnetValue v2 = value.GetElement(index++);
				if(v2.GetTag() == ValueType_Time)
				{
					//Date/Time encoded value. 
					v.SetType(ValueType_Constructed);
					v.SetTag(NoTag);
					v.AddValue(v1);
					v.AddValue(v2);
					return BC_OK;
				}
				//back up by one.
				--index;
			}
		}
		return Decode(v1);
	}

	BACnetResult Encode(BACnetValue &value)
	{
		if(v.IsConstructedData())
		{
			if(value.IsUninitialized())
			{
				value.SetType(ValueType_Constructed);
				value.SetTag(NoTag);
			}
			value.AddValue(v.GetElement(0));
			value.AddValue(v.GetElement(1));
			return BC_OK;
		}
		value = v;
		return BC_OK;
	}
};

template<>
struct is_bacnet_template<BACnetApplicationAnyDateTimeType> : public std::true_type {};

static_assert(is_bacnet_template_v<BACnetApplicationAnyDateTimeType> == true, "is_bacnet_template does not return true on BACnetApplicationAnyDateTimeType");

template<>
struct is_application<BACnetApplicationAnyDateTimeType> : public std::true_type {};

static_assert(is_application_v<BACnetApplicationAnyDateTimeType> == true, "is_application does not return true on BACnetApplicationAnyDateTimeType");

template<U32 Tag, typename T>
class BACnetChoiceElement
{
	T elem;
public:
	static constexpr U32 TagNumber = Tag;
	typedef T ValueType;

	static_assert(TagNumber != NoTag || is_application<ValueType>::value == true, "An untagged choice element must be an application tagged type!");

	ValueType& value()
	{
		return elem;
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		if constexpr(is_sequence_v<ValueType>)
		{
			if(!value.IsConstructedData())
			{
				__debugbreak();
				return BCE_REJECT_INVALID_TAG;
			}
			U32 index = 0;
			BACnetResult r = elem.Decode(value, index);
			if(index != value.GetNumElements() && BCE_SUCCEEDED(r))
			{
				//didn't use a value!
				__debugbreak();
				r = BCE_REJECT_TOO_MANY_ARGUMENTS;
			}
			return r;
		}
		else
		{
			return elem.Decode(value);
		}
	}

	BACnetResult Encode(BACnetValue &value)
	{
		BACnetResult r = elem.Encode(value);
		if(BCE_FAILED(r))
		{
			return r;
		}
		if constexpr(TagNumber != NoTag)
		{
			value.SetTag(TagNumber);
		}
		return BC_OK;
	}
};

template<U32 TN, typename T>
struct is_bacnet_template<BACnetChoiceElement<TN, T>> : std::true_type {};

template<U32 TN, typename T>
struct is_choice_element<BACnetChoiceElement<TN, T>> : std::true_type { };

/*
Choice type
Used for when you need to choose one of several types of values.
*/

//forward declaration
template<U32 DefaultChoice, typename... T> class BACnetChoice;

//forward declaration of the helper for compact storage
template<typename... T> union BACnetChoiceStorage;

//forward declaration of the helper for numeric iteration
template<U32 Index, typename... T> struct BACnetChoiceElementHolder;

//Numeric iteration found type
template <typename T, typename... Tail>
struct BACnetChoiceElementHolder<0, BACnetChoiceStorage<T, Tail...>>
{
	typedef T Type;
};

//numeric iteration still needs to find type
template <U32 Index, typename T, typename... Tail>
struct BACnetChoiceElementHolder<Index, BACnetChoiceStorage<T, Tail...>>
{
	typedef typename BACnetChoiceElementHolder<Index - 1, BACnetChoiceStorage<Tail...>>::Type Type;
};

template<>
union BACnetChoiceStorage<>
{
	template<typename...> friend union BACnetChoiceStorage;
	template<U32, typename...> friend class BACnetChoice;
private:
	void DestroySelection(U32 selection)
	{
		//if we get here, we did something very wrong.
		(void)selection;
		assert("DestroySelection called without a selection - Fix This!" && false);
	}

	void CopySelection(U32 Selection, BACnetChoiceStorage<>& Other)
	{
		(void)Selection;
		(void)Other;
		assert("CopySelection called without a selection - Fix This!" && false);
	}

public:


	BACnetResult Decode(U32& selection, const BACnetValue& value)
	{
		(void)value;
		(void)selection;
		return BCE_REJECT_MISSING_REQUIRED_PARAMETER;
	}

	BACnetResult Encode(BACnetValue& value)
	{
		(void)value;
		return BCE_REJECT_MISSING_REQUIRED_PARAMETER;
	}
};

template<typename T, typename... Tail>
union BACnetChoiceStorage<T, Tail...>
{
private:
	static_assert(is_choice_element<T>::value, "T must be a BACnet Choice Element.");
	T choiceval;
	BACnetChoiceStorage<Tail...> Remaining;
	//Stupid, but we have to do this to keep DestroySelection private.
	//Prevents us from making a mess of the union (outside of here).
	template<typename...> friend union BACnetChoiceStorage;
	template<U32, typename...> friend class BACnetChoice;

	void CopySelection(U32 Selection, BACnetChoiceStorage<T, Tail...>& Other)
	{
		if(Selection == 0)
		{
			choiceval = Other.choiceval;
		}
		Remaining.CopySelection(--Selection, Other.Remaining);
	}

	void DestroySelection(U32 Selection)
	{
		if(Selection == 0)
		{
			choiceval.~T();
		}
		Remaining.DestroySelection(--Selection);
	}
public:
	//default constructor does nothing - we cannot initialize this directly.
	BACnetChoiceStorage() {}
	//do nothing - we cannot destroy the value directly
	~BACnetChoiceStorage() {}

	template <U32 Index>
	typename std::enable_if_t<
		Index == 0, typename BACnetChoiceElementHolder<0, BACnetChoiceStorage<T, Tail...>>::Type::ValueType&>
		get()
	{
		return choiceval.value();
	}

	template <U32 Index>
	typename std::enable_if_t<
		Index != 0, typename BACnetChoiceElementHolder<Index, BACnetChoiceStorage<T, Tail...>>::Type::ValueType&>
		get()
	{
		return Remaining.get<Index - 1>();
	}

	BACnetResult Decode(U32& selection, const BACnetValue& value)
	{
		if(value.IsUntaggedData())
		{
			//does this choice element have a tag number?
			if(T::TagNumber == NoTag)
			{
				//No. Speculatively parse ahead, and skip this choice if we get an error.
				if(BCE_SUCCEEDED(choiceval.Decode(value)))
				{
					return BC_OK;
				}
			}
			//We need a tag number, but this value does not have one. skip to the next.
		}
		else if(value.GetTag() == T::TagNumber)
		{
			//this is the value.
			return choiceval.Decode(value);
		}
		return Remaining.Decode(++selection, value);
	}

	BACnetResult Encode(U32 selection, BACnetValue& value)
	{
		if(selection == 0)
		{
			return choiceval.Encode(value);
		}
		return Remaining.Encode(--selection, value);
	}
};

static const U32 NoDefault = (U32)-1;
static const U32 InvalidIndex = (U32)-1;

template<U32 DefaultChoice, typename... Types>
class BACnetChoice
{
	BACnetChoiceStorage<Types...> storage;
	U32 selection;

public:

	BACnetChoice() : selection(DefaultChoice) {}
	~BACnetChoice()
	{
		if(IsValid())
		{
			storage.DestroySelection(selection);
		}
	}

	BACnetChoice(BACnetChoice<DefaultChoice, Types...>& Other) : selection(Other.selection)
	{
		if(IsValid())
		{
			//copy the other's storage.
			storage.CopySelection(selection, Other.storage);
		}
	}

	BACnetChoice(BACnetChoice<DefaultChoice, Types...>&& Other) : selection(Other.selection)
	{
		if(IsValid())
		{
			storage.CopySelection(selection, Other.storage);
		}
	}

	BACnetChoice& operator=(BACnetChoice<DefaultChoice, Types...>& Other)
	{
		if(this != &Other)
		{
			selection = Other.selection;
			if(IsValid())
			{
				//copy the other's storage.
				storage.CopySelection(selection, Other.storage);
			}
		}
		return *this;
	}

	bool IsValid()
	{
		return selection != InvalidIndex && is_valid_selection(selection);
	}

	bool is_selected(U32 Index)
	{
		return Index == selection;
	}

	bool is_valid_selection(U32 Index)
	{
		return Index >= 0 && Index < sizeof...(Types);
	}

	void make_selected(U32 Index)
	{
		if(is_valid_selection(Index))
		{
			storage.DestroySelection(selection);
			selection = Index;
		}
	}

	void clear_selection()
	{
		storage.DestroySelection(selection);
		selection = InvalidIndex;
	}

	U32 get_selection()
	{
		return selection;
	}

	template <U32 Index>
	typename BACnetChoiceElementHolder<Index, BACnetChoiceStorage<Types...>>::Type::ValueType& get()
	{
		if(!is_selected(Index))
		{
			__debugbreak();
		}
		return storage.get<Index>();
	}

	BACnetResult Decode(const BACnetValue& value)
	{
		BACnetResult r = storage.Decode(selection, value);
		if(BCE_FAILED(r))
		{
			selection = InvalidIndex;
		}
		return r;
	}

	BACnetResult Decode(const BACnetValue& value, U32& index)
	{
		if(!value.IsConstructedData())
		{
			return BCE_REJECT_INVALID_TAG;
		}
		return Decode(value.GetElement(index++));
	}

	BACnetResult Encode(BACnetValue &value)
	{
		return storage.Encode(selection, value);
	}
};

template<U32 dc, typename... Types>
struct is_bacnet_template<BACnetChoice<dc, Types...>> : public std::true_type {};

template<U32 dc, typename... Types>
struct is_choice<BACnetChoice<dc, Types...>> : public std::true_type { };

template<typename T>
class BACnetSequenceOf
{
	std::vector<T> seq;
public:

	BACnetSequenceOf() {}
	BACnetSequenceOf(BACnetSequenceOf<T>& Other) :
		seq(Other.seq)
	{

	}
	BACnetSequenceOf(BACnetSequenceOf<T>&& Other)
	{
		std::swap(seq, Other.seq);
	}

	~BACnetSequenceOf() {}

	bool IsValid()
	{
		return true;
	}

	size_t size()
	{
		return seq.size();
	}

	T& get(U32 Index)
	{
		return seq.at(Index);
	}

	std::vector<T> get_list()
	{
		return seq;
	}

	void set(U32 Index, T Value)
	{
		seq[Index] = Value;
	}

	void set_list(std::vector<T> ValueList)
	{
		seq = ValueList;
	}

	void add(T Value)
	{
		seq.push_back(Value);
	}

	void add_list(std::vector<T> ValueList)
	{
		seq.insert(seq.end(), ValueList.begin(), ValueList.end());
	}

	void clear_list()
	{
		seq.clear();
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		U32 index = 0;
		return Decode(value, index);
	}

	BACnetResult Decode(const BACnetValue &value, U32& index)
	{
		while(index < value.GetNumElements())
		{
			BACnetResult r = 0;
			T elem;
			if(is_sequence_v<T>)
			{
				r = elem.Decode(value, index);
			}
			else
			{
				r = elem.Decode(value.GetElement(index));
				++index;
			}
			if(BCE_FAILED(r))
			{
				return r;
			}
			seq.push_back(elem);
		}
		return BC_OK;
	}

	BACnetResult Encode(BACnetValue& value)
	{
		//set up a constructed value.
		if(value.IsUninitalized())
		{
			value.SetType(ValueType_Constructed);
			value.SetTag(NoTag);
		}
		for(T v : seq)
		{
			BACnetResult r;
			//sequence type?
			if(is_sequence_v<T>)
			{
				//encode it directly into this value.
				r = v.Encode(value);
			}
			else
			{
				//encode it as a subvalue.
				BACnetValue val;
				r = v.Encode(val);
				value.AddValue(val);
			}
			if(BCE_FALED(r))
			{
				return r;
			}
		}
		return BC_OK;
	}
};

template<typename T>
struct is_bacnet_template<BACnetSequenceOf<T>> : public std::true_type {};

template<typename T>
struct is_sequence<BACnetSequenceOf<T>> : public std::true_type { };

template<U8 TagValue, typename T, bool Optional = false>
class BACnetSequenceElement
{
	//static_assert((TagValue != NoTag) || (is_application<T>::value), "Complex or context-tagged data must have a valid tag.");
public:
	static constexpr U8 Tag = TagValue;
	static constexpr bool IsOptional = Optional;
	typedef T ValueType;

private:
	ValueType ThisValue;
public:

	ValueType & value()
	{
		return ThisValue;
	}

	BACnetResult Decode(const BACnetValue& value)
	{
		if(is_application<ValueType>::value)
		{
			//tagged application data.
			//parse by value.
			return ThisValue.Decode(value);
		}
		//tagged non application data.
		//parse by root/index
		U32 index = 0;
		return ThisValue.Decode(value, index);
	}

	template<U8 VTag = Tag>
	typename std::enable_if_t<VTag != NoTag, BACnetResult>
		Encode(BACnetValue& value)
	{
		//tagged application data.
		BACnetResult r = ThisValue.Encode(value);
		value.SetTag(VTag);
		return r;
	}

	template<U8 VTag = Tag>
	typename std::enable_if_t<VTag == NoTag, BACnetResult>
		Encode(BACnetValue& value)
	{
		//untagged application data.
		return ThisValue.Encode(value);
	}
};

template<U8 Tag, typename T, bool Opt>
struct is_bacnet_template<BACnetSequenceElement<Tag, T, Opt>> : public std::true_type {};

template<U8 Tag, typename T, bool Opt>
struct is_sequence_element<BACnetSequenceElement<Tag,T,Opt>> : public std::true_type { };

template<typename... T> class BACnetSequence;

//Type iterator
template<U32 Index, typename... T> struct BACnetSequenceElementHolder;

template <typename T, typename... Tail>
struct BACnetSequenceElementHolder<0, BACnetSequence<T, Tail...>>
{
	typedef T Type;
};

template <U32 Index, typename T, typename... Tail>
struct BACnetSequenceElementHolder<Index, BACnetSequence<T, Tail...>>
{
	typedef typename BACnetSequenceElementHolder<Index - 1, BACnetSequence<Tail...>>::Type Type;
};

template<>
class BACnetSequence<>
{
public:

	bool IsValid()
	{
		return true;
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		(void)value;
		return BC_OK;
	}

	BACnetResult Decode(const BACnetValue &value, U32 &index)
	{
		(void)value; (void)index;
		return BC_OK;
	}

protected:
	BACnetResult Encode_(BACnetValue &value)
	{
		(void)value;
		return BC_OK;
	}
};

template<>
struct is_bacnet_template<BACnetSequence<>> : public std::true_type {};

template<>
struct is_sequence<BACnetSequence<>> : public std::true_type { };

template<typename T, typename... Tail>
class BACnetSequence<T, Tail...> : private BACnetSequence<Tail...>
{
	static_assert(is_sequence_element<T>::value, "T is not a BACnetSequenceElement.");

	using Base = BACnetSequence<Tail...>;

	T ThisValue;
	bool IsPresent;

public:

	BACnetSequence() {}

	BACnetSequence(std::enable_if<T::IsOptional, BACnetSequence<T, Tail...>&> Other)
	{
		
	}

	template<U32 Index>
	typename std::enable_if_t<(Index == 0) && (!T::IsOptional), bool>
		is_present()
	{
		return true;
	}

	template <U32 Index>
	typename std::enable_if_t<Index == 0 && (T::IsOptional), bool>
		is_present()
	{
		return IsPresent;
	}

	template <U32 Index>
	typename std::enable_if_t<Index != 0, bool>
		is_present()
	{
		return Base::is_present<Index - 1>();
	}

	template<U32 Index>
	typename std::enable_if_t<Index == 0 && T::IsOptional == false, void>
		make_present(bool ShouldBePresent)
	{
	}

	template <U32 Index>
	typename std::enable_if_t<Index == 0 && T::IsOptional == true, void>
		make_present(bool ShouldBePresent)
	{
		IsPresent = ShouldBePresent;
	}

	template <U32 Index>
	typename std::enable_if_t<Index != 0, void>
		make_present(bool ShouldBePresent)
	{
		Base::make_present<Index - 1>(ShouldBePresent);
	}

	template <U32 Index>
	typename std::enable_if_t<
		Index == 0, typename BACnetSequenceElementHolder<0, BACnetSequence<T, Tail...>>::Type::ValueType&>
		get()
	{
		return ThisValue.value();
	}

	template <U32 Index>
	typename std::enable_if_t<
		Index != 0, typename BACnetSequenceElementHolder<Index, BACnetSequence<T, Tail...>>::Type::ValueType&>
		get()
	{
		return Base::get<Index - 1>();
	}

	bool IsValid()
	{
		return true;
	}

	BACnetResult Decode(const BACnetValue &value)
	{
		U32 index = 0;
		return Decode(value, index);
	}

	BACnetResult Decode(const BACnetValue &value, U32& index)
	{
		if(T::IsOptional)
		{
			//Are we off the end, or 
			if(index >= value.GetNumElements() ||
				//is the value tagged, and the tag doesn't match?
				(T::Tag != NoTag && value.GetElement(index).GetTag() != T::Tag))
			{
				//Forward past this element.
				return Base::Decode(value, index);
			}
			//index is valid and either the tag or the type matches.
			BACnetResult r = ThisValue.Decode(value.GetElement(index++));
			if(BCE_FAILED(r))
			{
				return r;
			}
			IsPresent = true;
			return Base::Decode(value, index);
		}
		else
		{
			//Are we off the end, or 
			if(index >= value.GetNumElements() ||
				//is the value tagged, and the tag doesn't match?
				(T::Tag != NoTag && value.GetElement(index).GetTag() != T::Tag))
			{
				__debugbreak();
				return BCE_REJECT_MISSING_REQUIRED_PARAMETER;
			}
			//Index is valid. The tag is either valid, or the application type needs to be parsed.
			BACnetResult r = ThisValue.Decode(value.GetElement(index++));
			if(BCE_FAILED(r))
			{
				//either wrong type or lower error.
				return r;
			}
			return Base::Decode(value, index);
		}
	}

protected:

	template<typename VT = T>
	typename std::enable_if_t<
		VT::IsOptional == true, BACnetResult>
		Encode_(BACnetValue &value)
	{
		if(IsPresent)
		{
			//encode the value.
			BACnetValue val;
			BACnetResult r = ThisValue.Encode(val);
			if(BCE_FAILED(r))
			{
				return r;
			}
			value.AddValue(val);
		}
		return Base::Encode_(value);
	}

	template<typename VT = T>
	typename std::enable_if_t<
		VT::IsOptional == false, BACnetResult>
		Encode_(BACnetValue &value)
	{
		//encode the value.
		BACnetValue val;
		BACnetResult r = ThisValue.Encode(val);
		if(BCE_FAILED(r))
		{
			return r;
		}
		if(VT::Tag == NoTag && is_sequence<VT::ValueType>::value == true)
		{
			//untagged sequence - copy the elements of the temporary into the parent sequence.
		}
		value.AddValue(val);
		return Base::Encode_(value);
	}

public:
	BACnetResult Encode(BACnetValue& value)
	{
		if(value.IsUninitialized())
		{
			value.SetType(ValueType_Constructed);
			value.SetTag(NoTag);
		}
		return Encode_(value);
	}
};

template<typename T, typename... Tail>
struct is_sequence<BACnetSequence<T, Tail...>> : public std::true_type { };

template<typename T, typename... Tail>
struct is_bacnet_template<BACnetSequence<T, Tail...>> : public std::true_type {};

//#include "BACnetAPDUHelpers.inl"
