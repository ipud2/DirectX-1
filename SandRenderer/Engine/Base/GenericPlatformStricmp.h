#pragma once

#include "Platform.h"
#include "TChar.h"
#include "TEnableIf.h"
#include "STypeTraits.h"

template<typename A , typename B>
struct TIsComparisonCompatibleChar
{
	enum { Value = false };
};

template<>
struct TIsComparisonCompatibleChar<WIDECHAR, ANSICHAR>
{
	enum 
	{
		Value = true
	};
};

/*
	static struct that implements generic stricmp functionality.
*/
struct SGenericPlatformStricmp
{
private:
	/*
		Compares two strings case-insensitive assuming that both char char type are compatible.

		@param String1 First string to compare.
		@param String2 Second string to compare.
		@return Zero if both string are equal.
				Greater than zero if first string is greater than the second one.
				Less than zero otherwise.
	*/
	template<typename CompatibleCharType1 , typename CompatibleCharType2>
	static inline int32 CompatibleCharTypeStricmp(const CompatibleCharType1* String1, const CompatibleCharType2* String2)
	{
		// Walk the strings. comparing them case insensitively.
		for (; *String1 || *String2; String1++, String2++)
		{
			if (*String1 != *String2)
			{
				CompatibleCharType1 Char1 = TChar<CompatibleCharType1>::ToLower(*String1);
				CompatibleCharType2 Char2 = TChar<CompatibleCharType2>::ToLower(*String2);

				if (Char1 != Char2)
				{
					return Char1 - Char2;
				}
			}
		}

		return 0;
	}

	/*
		Help function wrapper to verify compatibility. This overload checks if CharType1 == CharType2
	*/
	template<typename CharType1 , typename CharType2>
	static inline int32 StricmpImpl(const CharType1* String1, const CharType2* String2, typename TEnableIf<TIsSame<CharType1, CharType2>::Value>::Type* Dummy = nullptr)
	{
		return CompatibleCharTypeStricmp(String1, String2);
	}

	/*
		Helper function wrapper to verify compatibility.
		This overload checks if CharType1 is compatible with CharType2.
	*/
	template<typename CharType1 , typename CharType2>
	static inline int32 StricmpImpl(const CharType1* String1, const CharType2* String2, typename TEnableIf<TIsComparisonCompatibleChar<CharType1, CharType2>::Value>::Type* Dummpy = nullptr)
	{
		return CompatibleCharTypeStricmp(String1, String2);
	}
	
	template<typename CharType1 , typename CharType2>
	static inline int32 StricmpImpl(const CharType1* String1, const CharType2* String2, typename TEnableIf<TIsComparisonCompatibleChar<CharType2, CharType2>::Value>::Type* Dummpy = nullptr)
	{
		return CompatibleCharTypeStricmp(String1, String2);
	}

public:
	/*
		Compares two strings case-insensitive.

		@param String1 First string to compare.
		@param String2 Second string to compare.
		@return Zero if both are equals.
				Greater than zero if first string is greater than the second one.
				Less than zero otherwise.
	*/
	template<typename CharType1 , typename CharType2>
	static inline int32 Stricmp(const CharType1* String1, const CharType2* String2)
	{
		return SGenericPlatformStricmp::StricmpImpl(String1, String2);
	}


};