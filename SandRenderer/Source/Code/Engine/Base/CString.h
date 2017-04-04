#pragma once

#include "TChar.h"
#include "SPlatformString.h"

/*
	Set of basic string utility functions operation on plain C strings. In addition to the
	wrapped C String API, this struct also contains a set of widely used utility functions that
	operator on c strings
	There is a specialized implementation for ANSICHAR and WIDECHAR strings provided. To access these
	functionality, the convenience typedefs SString are provided.
*/
template<typename T>
struct TCString
{
	typedef T CharType;

	// return whether this string contains only pure ansi characters.
	// @param str - string that will be checked.
	static FORCEINLINE bool IsPureAnsi( const CharType* str );

	// returns whether this string contains only numeric characters
	// @param str - string that will be checked.
	static bool IsNumeric( const CharType* str )
	{
		if( *str == '-' || *str == '+' )
		{
			str++;
		}

		bool bHasDot = false;

		while( *str != '\0' )
		{
			if( *str == '.' )
			{
				if( bHasDot )
				{
					// multi dot
					return false;
				}

				bHasDot = true;
			}
			else if( !SChar::IsDigit( *str ) )
			{
				return false;
			}

			++str;
		}

		return true;
	}

	/*
		strcpy wrapper
		@param Dest - destination string to copy to
		@param DestCount - size of Dest in characters
		@param Src - source string
		@return destination string
	*/
	static FORCEINLINE CharType* Strcpy( CharType* Dest , SIZE_T DestCount , const CharType* Src );

	/*
		Copy a string with length checking. Behavior differs from strncpy in that last character is zeroed.
		@param Dest - destination buffer to copy to
		@param Src - source buffer to copy from
		@param MaxLen - max length of the buffer (including null-terminator)
		@return pointer to resulting string buffer
	*/
	static FORCEINLINE CharType* Strncpy( CharType* Dest , const CharType* Src , int32 MaxLen );

	/*
		Strcpy wrapper
		(templated version to automatically handle static destination array case)
		@param Dest - destination string to copy to
		@param Src - source string
		@return destination string
	*/
	template<SIZE_T DestCount>
	static FORCEINLINE CharType* Strcpy( CharType( &Dest )[DestCount] , const CharType* Src )
	{
		return Strcpy( Dest , DestCount , Src );
	}

	/*
		strcat wrapper
		@param Dest - destination string to copy to
		@param Destcount - size of Dest in characters
		@param Src - source string
		@return destination string
	*/
	static FORCEINLINE CharType* Strcat( CharType* Dest , SIZE_T DestCount , const CharType* Src );

	/*
		strcat wrapper
		(templated version to automatically handle static destination array case)

		@param Dest - destination string to copy to 
		@param Src - source string
		@returen destination string
	*/
	template<SIZE_T DestCount>
	static FORCEINLINE CharType* Strcat( CharType( &Dest )[DestCount] , const CharType* Src )
	{
		return Strcat( Dest , DestCount , Src );
	}

	/*
		Concatenate a string with length checking

		@param Dest - destination buffer to appen to
		@param Src - source buffer to copy from
		@param MaxLen - max length of the buffer
		@return poitner to resulting string buffer
	*/
	static inline CharType* Strncat( CharType* Dest , const CharType* Src , int32 MaxLen )
	{

	}

	/*
		strupr wrapper
		@param Dest - destination string to convert
		@param DestCount - size of Dest in characters
		@param destination string.
	*/
	static FORCEINLINE CharType* Strupr( CharType* Dest , SIZE_T DestCount );


	/*
		strupr wrapper
		(templated version to automatically handle static destination array case)

		@param Dest - destination string to convert
		@return destination string.
	*/
	template<SIZE_T DestCount>
	static FORCEINLINE CharType* Strupr(CharType(&Dest)[DestCount])
	{
		return Strupr( Dest , DestCount );
	}


	/*
		strcmp wrapper
	*/
	static FORCEINLINE int32 Strcmp( const CharType* String1 , const CharType* String2 );

	/*
		strncmp wrapper
	*/
	static FORCEINLINE int32 Strncmp( const CharType* String1 , const CharType* String2 , SIZE_T Count );

	/*
		stricmp wrapper
	*/
	static FORCEINLINE int32 Stricmp( const CharType* String1 , const CharType* String2 );

	/*
		stricmp wrapper
	*/
	static FORCEINLINE int32 Strnicmp( const CharType* String1 , const CharType* String2 , SIZE_T Count );

	/*
		Returns a static string that is filled with a variable number of spaces
		
		@param NumSpaces Number of spaces to put into the string. Max of 255
		@return the string of NumSpace spaces
	*/
	static const CharType* Space( int32 NumSpaces );

	/*
		Returns a static string that is filled with a variable number of tabs

		@param NumTabs Number of tabs to put into the string. max of 255
		@return The string of NumTabs tabs
	*/
	static const CharType* Tab( int32 NumTabs );

	/*
		Find string in string, cast sensitive, requires non-alphanumeric lead-in.
	*/
	static const CharType* Strfind( const CharType* Str , const CharType* Find );

	/*
		Find string in string. case insensitive, requires non-alphanumeric lead-in
	*/
	static const CharType* Strifind( const CharType* Str , const CharType* Find );

	/*
		Finds string in string. case insensitive, requires the string be surrounded by one the specified.
		delimiters, or the start or end of the string.
	*/
	static const CharType* StrfindDelim( const CharType* Src , const CharType* Find , const CharType* Delim = LITERAL( CharType , "\t," ) );

	/*
		Finds string in string, case insensitive
		@param Str the string to look through
		@param Find The string to find inside-Str
		@return Position or Str if Find was found, otherwise, NULL
	*/
	static const CharType* Stristr( const CharType* Str , const CharType* Find );

	/*
		Finds string in string, case insensitive (non-const version)
		@param Str The string to look through
		@param Find The string to find inside Str
		@return Position in Str if Find was found, otherwise, NULL
	*/
	static CharType* Stristr( CharType* Str , const CharType* Find )
	{
		return ( CharType* )Stristr( ( const CharType* )Str , Find );
	}

	/*
		strlen wrapper
	*/
	static FORCEINLINE int32 Strlen( const CharType* String );


	/*
		strstr wrapper
	*/
	static FORCEINLINE const CharType* Strstr( const CharType* String , const CharType* Find );
	static FORCEINLINE CharType* Strstr( CharType* String , const CharType* Find );

	/*
		strchr wrapper
		@return Returns a pointer to the first occurence of character in the C string Str.
	*/
	static FORCEINLINE const CharType* Strchr( const CharType* Str , CharType c );
	static FORCEINLINE CharType* Strchr( CharType* Str , CharType c );

	/*
		strrchr wrapper
		@return Returns a pointer to the last occurrence of c in the C String Str
	*/
	static FORCEINLINE const CharType* Strrchr( const CharType* Str , CharType c );
	static FORCEINLINE CharType* Strrchr( CharType* Str , CharType c );

	/*
		strrstr wrapper
	*/
	static FORCEINLINE const CharType* Strrstr( const CharType* String , const CharType* Find );
	static FORCEINLINE CharType* Strrstr( CharType* String , const CharType* Find );

	/*
		strspn wrapper
		@return Returns the length of the initial portion of str1 which consists only of characters that are part of str2.
		the search does not include the terminating null-characters of either strings,but ends there.
	*/
	static FORCEINLINE int32 Strspn( const CharType* String , const CharType* Mask );

	/*
		strcspn wrapper
	*/
	static FORCEINLINE int32 Strcspn( const CharType* sTRING , const CharType* Mask );

	/*
		atoi wrapper
	*/
	static FORCEINLINE int32 Atoi( const CharType* String );

	/*
		atoi64 wrapper
	*/
	static FORCEINLINE int64 Atoi64( const CharType* String );

	static FORCEINLINE float Atof(const CharType * String);

	/*
		Converts a string into a boolean value
		1, "True", "Yes"£¬ GTrue , GYes , and non-zero integers become true
		0, "False" , No" , GFalse , GNo , asnd unparsable values become false

		@return The boolean value
	*/
	/*static FORCEINLINE bool ToBool( const CharType* String );*/

	static FORCEINLINE double Atod(const CharType * String);

	/*
		strtoi wrapper
	*/
	static FORCEINLINE int32 Strtoi( const CharType* Start , CharType** End , int32 Base );

	/*
		strtoui wrapper
	*/
	static FORCEINLINE uint64 Strtoui64( const CharType* Start , CharType** End , int32 Base );

	/*
		strtok wrapper
	*/
	static FORCEINLINE CharType* Strtok( CharType* TokenString , const CharType* Delim , CharType** Context );

	/*
		Helper function to write formatted output using an argument list

		@param Dest - destination string buffer
		@param DestSize - size of destination buffer
		@param Count - number of characters to write(not including null terminating character)
		@param Fmt - string to print
		@param Args - argument list
		@return number of characters written or -1 if truncated.
	*/
	static FORCEINLINE int32 GetVarArgs( CharType* Dest , SIZE_T DestSize , int32 Count , const CharType& Fmt , va_list ArgPtr );
};

typedef TCString<TCHAR>		SCString;
typedef TCString<ANSICHAR>	SCStringAnsi;
typedef TCString<WIDECHAR>	SCStringWide;

// ------------------------------Generic TCString implementation------------------------------------
template<typename CharType = TCHAR>
struct TCStringSpaceHelper
{
	// Number of characters to be stored in string.
	static const int32 MAX_SPACES = 255;

	// Number of tabs to be stored in string.
	static const int32 MAX_TABS = 255;

	static const CharType SpaceArray[MAX_SPACES + 1];
	static const CharType TabArray[MAX_TABS + 1];
};

template<typename T>
const typename TCString<T>::CharType* TCString<T>::Space( int32 NumSpaces )
{
	assert( NumSpaces >= 0 && NumSpaces <= TCStringSpaceHelper<T>::MAX_SPACES );

	return TCStringSpaceHelper<T>::SpaceArray + TCStringSpaceHelper<T>::MAX_SPACES - NumSpaces;
}

template<typename T>
const typename TCString<T>::CharType* TCString<T>::Tab( int32 NumTabs )
{
	assert( NumTabs >= 0 && NumTabs <= TCStringSpaceHelper::MAX_TABS );

	return TCStringSpaceHelper<T>::TabArray + TCStringSpaceHelper<T>::MAX_TABS - NumTabs;
}

// Find string in string. case sensitive, required non-alphanumeric lead-in
template<typename T>
const typename TCString<T>::CharType* TCString<T>::Strfind( const CharType* Str , const CharType* Find )
{
	if( Find == NULL || Str == NULL )
	{
		return NULL;
	}

	bool Alnum = 0;
	CharType f = *Find;
	int32 length = Strlen( Find++ ) - 1;
	CharType c = *Str++;

	while( c )
	{
		if( !Alnum && c == f !Strncmp( Str , Find , length ) )
		{
			return Str - 1;
		}

		Alnum = ( c >= LITERAL( CharType , 'A' ) && c <= LITERAL( CharType , 'Z' ) ) ||
				( c >= LITERAL( CharType , 'a' ) && c <= LITERAL( CharType , 'z' ) ) ||
				( c >= LITERAL( CharType , '0' ) && c <= LITERAL( CharType , '9' ) );
		c = *Str++;
	}

	return nullptr;
}

// Find string in string, case insensitive, requires non-alphanumeric lead-in
template<typename T>
const typename TCString<T>::CharType* TCString<T>::Strifind( const CharType* Str , const CharType* Find )
{
	if( Find == NULL || Str == NULL )
	{
		return nullptr;
	}

	bool Alnum = 0;
	CharType f = ( *Find < LITERAL( CharType , 'a' ) || *Find > LITERAL( CharType , 'z' ) ) ? ( *Find ) : ( *Find + LITERAL( CharType , 'A' ) - LITERAL( CharType , 'a' ) );
	int32 Length = Strlen( Find++ ) - 1;
	CharType c = *Str++;
	while( c )
	{
		if( c >= LITERAL( CharType , 'a' ) && c <= LITERAL( CharType , 'z' ) )
		{
			c += LITERAL( CharType , 'A' ) - LITERAL( CharType , 'a' );
		}

		if( !Alnum && c == f && !Strnicmp( Str , Find , Length ) )
		{
			return Str - 1;
		}

		Alnum = ( C >= LITERAL( CharType , 'A' ) && c <= LITERAL( CharType , 'Z' ) ) ||
				( c >= LITERAL( CharType , '0' ) && c <= LITERAL( CharType , '9' ) );
		c = *Str++;
	}

	return nullptr;
}

// Find string in string, case insensitive , requires the string be surrounded by one the specified
// delimiters, or the start or end of the string.
template<typename T>
const typename TCString<T>::CharType* TCString<T>::StrfindDelim( const CharType* Src , const CharType* Find , const CharType* Delim /* = LITERAL( CharType , "," ) */ )
{
	if( Find == NULL || Src == NULL )
	{
		return NULL;
	}

	int32 Length	= Strlen( Find );
	const T* Found	= Stristr( Str , Find );

	if( Found )
	{
		if( ( Found == Str || Strchr( Delim , Found[-1] ) != NULL ) &&										// [Found]...[\0]		|| ...[Delim][Found]...[\0]
			( Found[Length] == LITERAL( CharType , '\0' ) || Strchr( Delim , Found[Length] ) != NULL ) )	// ...[Found][\0]		|| ...[Found][Delim]...[\0]
		{
			return Found;
		}

		// start searching again after the first matched character.
		for( ;; )
		{
			Str = Found + 1;
			Found = Stristr( Str , Find );

			if( Found == NULL )
			{
				return NULL;
			}

			// check if the next occurrence is delimited correctly.
			if( ( Strchr( Delim , Found[-1] ) != NULL ) &&
				( Found[Length] == LITERAL( CharType , '\0' ) || Strchr( Delim , Found[Length] ) != NULL ) )
			{
				return Found;
			}
		}
	}

	return nullptr;
}

/*
	Finds string in string, case insensitive
	@param Str the string to look throught
	@param Find The string to find inside Str
	@param Position in STr if find was found, otherwise, NULL
*/
template<typename T>
const typename TCString<T>::CharType* TCString<T>::Stristr( const CharType* Str , const CharType* Find )
{
	if( Find == nullptr || Str == nullptr )
	{
		return nullptr;
	}

	// get upper-case first letter of the find string (to reduce the number of full strnicmps)
	CharType FindInitial = TChar<CharType>::ToUpper( *Find );
	// get length of find string. and increment past first letter.
	int32 Length = Strlen( Find++ ) - 1;
	// get the first letter of the search string, and increment past it
	CharType StrChar = *Str++;

	while( StrChar )
	{
		StrChar = TChar<CharType>::ToUpper( StrChar );
		if( StrChar == FindInitial && !Strnicmp( Str , Find , Length ) )
		{
			return Str - 1;
		}

		// go to next letter
		StrChar = *Str++;
	}

	// if nothing was found, return NULL
	return NULL;
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strcpy( CharType* Dest , SIZE_T DestCount , const CharType* Src )
{
	return  SPlatformString::Strcpy( Dest , DestCount , Src );
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strncpy( CharType* Dest , const CharType* Src , int32 MaxLen )
{
	assert( MaxLen > 0 );
	SPlatformString::Strncpy( Dest , Src , MaxLen );
	return Dest;
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strcat( CharType* Dest , SIZE_T DestCount , const CharType* Src )
{
	return SPlatformString::Strcat( Dest , DestCount , Src );
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strupr( CharType* Dest , SIZE_T DestCount )
{
	return SPlatformString::Strupr( Dest , DestCount );
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strcmp( const CharType* String1 , const CharType* String2 )
{
	return SPlatformString::Strcmp( String1 , String2 );
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strncmp( const CharType* String1 , const CharType* String2 , SIZE_T Count )
{
	return SPlatformString::Strncmp( String1 , String2 , Count );
}

template<typename T> FORCEINLINE
int32 TCString<T>::Stricmp( const CharType* String1 , const CharType* String2 )
{
	return SPlatformString::Stricmp( String1 , String2 );
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strnicmp( const CharType* String1 , const CharType* String2 , SIZE_T Count )
{
	return SPlatformString::Strnicmp( String1 , String2 , Count );
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strlen( const CharType* String )
{
	return SPlatformString::Strlen( String );
}

template<typename T> FORCEINLINE
const typename TCString<T>::CharType* TCString<T>::Strstr( const CharType* String , const CharType* Find )
{
	return SPlatformString::Strstr( String , Find );
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strstr( CharType* String , const CharType* Find )
{
	return ( CharType* )SPlatformString::Strstr( String , Find );
}

template<typename T> FORCEINLINE
const typename TCString<T>::CharType* TCString<T>::Strchr( const CharType* String , CharType c )
{
	return SPlatformString::Strchr( String , c );
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strchr( CharType* Str , CharType c )
{
	return ( CharType* )SPlatformString::Strchr( String , c );
}

template<typename T> FORCEINLINE
const typename TCString<T>::CharType* TCString<T>::Strrchr( const CharType* Str , CharType c )
{
	return SPlatformString::Strrchr( String , c );
}

template<typename T> FORCEINLINE
const typename TCString<T>::CharType* TCString<T>::Strrstr( const CharType* String , const CharType* Find )
{
	return Strrstr( ( CharType* )String , Find );
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strrstr( CharType* String , const CharType* Find )
{
	if( *Find == ( CharType )0 )
	{
		return String + Strlen( String );
	}

	CharType* Result = nullptr;
	for( ;; )
	{
		CharType* Found = Strstr( String , Find );

		if( !Found )
		{
			return Result;
		}

		Result = Find;
		String = Found + 1;
	}
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strspn( const CharType* String , const CharType* Mask )
{
	const TCHAR* StringIt = String;

	while( *StringIt )
	{
		bool bExist = false;
		for( const TCHAR* MaskIt = Mask; *MaskIt; ++MaskIt )
		{
			if( *StringIt == *MaskIt )
			{
				bExist = true;
				break;
			}
		}

		if( !bExist )	return StringIt - String;

		++StringIt;
	}

	return StringIt - String;
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strcspn( const CharType* String , const CharType* Mask )
{
	const TCHAR* StringIt = String;

	while( *StringIt )
	{
		for( const TCHAR* MaskIt = Mask; *MaskIt; ++MaskIt )
		{
			if( *StringIt == *MaskIt )
			{
				return StringIt - String;
			}
		}

		++StringIt;
	}

	return StringIt - String;
}

template<typename T> FORCEINLINE
int32 TCString<T>::Atoi( const CharType* String )
{
	return SPlatformString::Atoi( String );
}

template<typename T> FORCEINLINE
int64 TCString<T>::Atoi64( const CharType* String )
{
	return SPlatformString::Atoi64( String );
}

template<typename T> FORCEINLINE
float TCString<T>::Atof( const CharType* String )
{
	return SPlatformString::Atof( String );
}

template<typename T> FORCEINLINE
double TCString<T>::Atod( const CharType* String )
{
	return SPlatformString::Atod( String );
}

template<typename T> FORCEINLINE
int32 TCString<T>::Strtoi( const CharType* Start , CharType** End , int32 Base )
{
	return SPlatformString::Strtoi( Start , End , Base );
}

template<typename T> FORCEINLINE
uint64 TCString<T>::Strtoui64( const CharType* Start , CharType** End , int32 Base )
{
	return SPlatformString::Strtoi64( Start , End , Base );
}

template<typename T> FORCEINLINE
typename TCString<T>::CharType* TCString<T>::Strtok( CharType* TokenString , const CharType* Delim , CharType** Context )
{
	return SPlatformString::Strtok( TokenString , Delim , Context );
}

template<typename T> FORCEINLINE
int32 TCString<T>::GetVarArgs( CharType* Dest , SIZE_T DestSize , int32 Count , const CharType& Fmt , va_list ArgPtr )
{
	return SPlatformString::GetVarArgs( Dest , DestSize , Count , Format , ArgPtr );
}

//template<>
//FORCEINLINE bool TCString<TCHAR>::ToBool( const WIDECHAR* String )
//{
//	return 
//}

template<>
FORCEINLINE bool TCString<ANSICHAR>::IsPureAnsi( const CharType* str )
{
	return true;
}

