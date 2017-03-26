#pragma once

#include "PCH.h"

template<typename T>
struct TLiteral
{
	static const ANSICHAR Select( const ANSICHAR ansi , const WIDECHAR )
	{
		return ansi;
	}

	static const ANSICHAR* Select( const ANSICHAR* ansi , const WIDECHAR* )
	{
		return ansi;
	}
};

template<> struct TLiteral<WIDECHAR>
{
	static const WIDECHAR Select( const ANSICHAR , const WIDECHAR wide )
	{
		return wide;
	}

	static const WIDECHAR* Select( const ANSICHAR* , const WIDECHAR* wide )
	{
		return wide;
	}
};

#define LITERAL(CharType , StringLiteral) TLiteral<CharType>::Select(StringLiteral , L##StringLiteral)

template<typename T>
struct TChar
{
	typedef T CharType;

public:
	static inline CharType ToUpper( CharType Char );
	static inline CharType ToLower( CharType Char );
	static inline bool IsUpper( CharType Char );
	static inline bool IsLower( CharType Char );
	static inline bool IsAlpha( CharType Char );	// IsLower或IsUpper将会返回true的字符，即字母
	static inline bool IsPunct( CharType Char );	// 标点字符

	static inline bool IsAlnum( CharType Char );	// 字母或数字
	static inline bool IsDigit( CharType Char );
	static inline bool IsOctDigit( CharType Char )
	{
		return Char >= '0' && Char <= '7';
	}
	static inline bool IsHexDigit( CharType Char );	// 十六进制
	static inline int32 ConvertCharDigitToInt( CharType Char )
	{
		return static_cast< int32 >( Char ) - static_cast< int32 >( '0' );
	}
	static inline bool IsWhitespace( CharType Char );
	static inline bool IsIdentifier( CharType Char )
	{
		return IsAlnum( Char ) || IsUnderscore( Char );
	}
	static inline bool IsUnderscore( CharType Char )
	{
		return Char == LITERAL( CharType , '_' );
	}
};

typedef TChar<TCHAR> SChar;
typedef TChar<WIDECHAR> SCharWide;
typedef TChar<ANSICHAR> SCharAnsi;

/*
	TCHAR specialized functions
*/
template<> inline TChar<WIDECHAR>::CharType TChar<WIDECHAR>::ToUpper( CharType Char )
{
	return ::toupper( Char );
}
template<> inline TChar<WIDECHAR>::CharType TChar<WIDECHAR>::ToLower( CharType Char )
{
	return ::tolower( Char );
}
template<> inline bool TChar<WIDECHAR>::IsUpper( CharType Char )
{
	return ::iswupper( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsLower( CharType Char )
{
	return ::iswlower( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsAlpha( CharType Char )
{
	return ::iswalpha( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsPunct( CharType Char )
{
	return ::iswpunct( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsAlnum( CharType Char )
{
	return ::iswalnum( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsDigit( CharType Char )
{
	return ::iswdigit( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsHexDigit( CharType Char )
{
	return ::iswxdigit( Char ) != 0;
}
template<> inline bool TChar<WIDECHAR>::IsWhitespace( CharType Char )
{
	return ::iswspace( Char ) != 0;
}

/*
	ANSICHAR specified functions
*/
template<> inline TChar<ANSICHAR>::CharType TChar<ANSICHAR>::ToUpper( CharType Char )
{
	return ::toupper( Char );
}
template<> inline TChar<ANSICHAR>::CharType TChar<ANSICHAR>::ToLower( CharType Char )
{
	return ::tolower( Char );
}
template<> inline bool TChar<ANSICHAR>::IsUpper( CharType Char )
{
	return ::isupper( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsLower( CharType Char )
{
	return ::islower( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsAlpha( CharType Char )
{
	return ::isalpha( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsPunct( CharType Char )
{
	return ::ispunct( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsAlnum( CharType Char )
{
	return ::isalnum( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsDigit( CharType Char )
{
	return ::isdigit( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsHexDigit( CharType Char )
{
	return ::isxdigit( Char ) != 0;
}
template<> inline bool TChar<ANSICHAR>::IsWhitespace( CharType Char )
{
	return ::isspace( Char ) != 0;
}