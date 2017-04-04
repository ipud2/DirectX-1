#pragma once

#include "TChar.h"
#include "windows.h"
#include <tchar.h>
#include "GenericPlatformString.h"
#include "GenericPlatformStricmp.h"

struct SMicrosoftPlatformString : public SGenericPlatformString
{
	/*
		Wide character implementation
	*/
	static FORCEINLINE WIDECHAR* Strcpy( WIDECHAR* Dest , SIZE_T DestCount , const WIDECHAR* Src )
	{
#if USE_SECURE_CRT
		_tcscpy_s( Dest , DestCount , Src );
		return Dest;
#else
		_tcscpy_s( Dest , DestCount , Src );
		return Dest;
#endif
	}

	static FORCEINLINE WIDECHAR* Strncpy( WIDECHAR* Dest , const WIDECHAR* Src , SIZE_T MaxLen )
	{
		#if USE_SECURE_CRT
		_tcsncpy_s( Dest , MaxLen , Src , MaxLen - 1 );
		#else
		_tcsncpy_s( Dest , MaxLen , Src , MaxLen - 1 );
		Dest[MaxLen - 1] = 0;
		#endif

		return Dest;
	}

	static FORCEINLINE WIDECHAR* Strcat( WIDECHAR* Dest , SIZE_T DestCount , const WIDECHAR* Src )
	{
#if USE_SECURE_CRT
		_tcscat_s( Dest , DestCount , Src );
		return Dest;
#else
		_tcscat_s( Dest , DestCount , Src );
		return Dest;
#endif
	}

	static FORCEINLINE WIDECHAR* Strupr( WIDECHAR* Dest , SIZE_T DestCount )
	{
#if USE_SECURE_CRT
		_tcsupr_s( Dest , DestCount );
		return Dest;
#else
		_tcsupr_s( Dest , DestCount );
		return Dest;
#endif
	}

	static FORCEINLINE int32 Strcmp( const WIDECHAR* String1 , const WIDECHAR* String2 )
	{
		return _tcscmp( String1 , String2 );
	}

	static FORCEINLINE int32 Strncmp( const WIDECHAR* String1 , const WIDECHAR* String2 , SIZE_T Count )
	{
		return _tcsncmp( String1 , String2 , Count );
	}

	static FORCEINLINE int32 Strnicmp( const WIDECHAR* String1 , const WIDECHAR* String2 , SIZE_T Count )
	{
		return _tcsnicmp( String1 , String2 , Count );
	}

	static FORCEINLINE int32 Strlen( const WIDECHAR* String )
	{
		return (int32)_tcslen(String);
	}

	static FORCEINLINE const WIDECHAR* Strstr( const WIDECHAR* String , const WIDECHAR* Find )
	{
		return _tcsstr( String , Find );
	}

	static FORCEINLINE const WIDECHAR* Strchr( const WIDECHAR* String , WIDECHAR c )
	{
		return _tcschr( String , c );
	}

	static FORCEINLINE int32 Atoi( const WIDECHAR* String )
	{
		return _tstoi( String );
	}

	static FORCEINLINE int64 Atoi64( const WIDECHAR* String )
	{
		return _tstoi64( String );
	}

	static FORCEINLINE float Atof( const WIDECHAR* String )
	{
		return (float)_tstof(String);
	}

	static FORCEINLINE double Atod( const WIDECHAR* String )
	{
		return _tcstod( String , NULL );
	}

	// convert strings to unsigned long-integer value.
	static FORCEINLINE int32 Strtoi( const WIDECHAR* Start , WIDECHAR** End , int32 Base )
	{
		return _tcstoul( Start , End , Base );
	}

	static FORCEINLINE uint64 Strtoui64( const WIDECHAR* Start , WIDECHAR** End , int32 Base )
	{
		return _tcstoui64( Start , End , Base );
	}

	static FORCEINLINE WIDECHAR* Strtok( WIDECHAR* StrToken , const WIDECHAR* Delim , WIDECHAR** Context )
	{
		return _tcstok_s( StrToken , Delim , Context );
	}

	static FORCEINLINE int32 GetVarArgs( WIDECHAR* Dest , SIZE_T DestSize , int32 Count , const WIDECHAR*& Format , va_list ArgPtr )
	{
#if USE_SECURE_CRT
		int32 Result = _vsntprintf_s( Dest , DestSize , Count , Format , ArgPtr );
#else
		int32 Result = _vsntprintf_s( Dest , DestSize , Count , Format , ArgPtr );
#endif

		va_end( ArgPtr );
		return Result;
	}

	/*
		Anis implementation	
	*/
	static FORCEINLINE ANSICHAR* Strcpy( ANSICHAR* Dest , SIZE_T DestCount , const ANSICHAR* Src )
	{
#if USE_SECURE_CRT
		strcpy_s( Dest , DestCount , Src );
		return Dest;
#else
		strcpy_s( Dest , DestCount, Src );
		return Dest;
#endif
	}

	static FORCEINLINE void Strncpy( ANSICHAR* Dest , const ANSICHAR* Src , SIZE_T MaxLen )
	{
#if USE_SECURE_CRT
		strncpy_s( Dest , MaxLen , Src , MaxLen - 1 );
#else
		strncpy_s(Dest, MaxLen, Src, MaxLen - 1);
		Dest[MaxLen - 1] = 0;
#endif
	}

	static FORCEINLINE ANSICHAR* Strcat( ANSICHAR* Dest , SIZE_T DestCount , const ANSICHAR* Src )
	{
#if USE_SECURE_CRT
		strcat_s( Dest , DestCount , Src );
		return Dest;
#else
		strcat_s( Dest , DestCount , Src );
		return Dest;
#endif
	}

	// convert a string to uppercase
	static FORCEINLINE ANSICHAR* Strupr( ANSICHAR* Dest , SIZE_T DestCount )
	{
#if USE_SECURE_CRT
		_strupr_s( Dest , DestCount );
		return Dest;
#else
		_strupr_s( Dest , DestCount );
		return Dest;
#endif
	}

	static FORCEINLINE int32 Strcmp( const ANSICHAR* String1 , const ANSICHAR* String2 )
	{
		return strcmp( String1 , String2 );
	}

	// @param Count Maximum number of characters to compare.
	static FORCEINLINE int32 Strncmp( const ANSICHAR* String1 , const ANSICHAR* String2 , SIZE_T Count )
	{
		return strncmp( String1 , String2 , Count );
	}

	/*
		`Compares two strings case-insensitive

		specialized version for ANSICHAR types.

		@param String1 First string to compare.
		@param String2 Second string to compare.

		@return Zero if both strings are equal. Greater than zero if first
				string is greater than the second one. Less than zero, otherwise
	*/
	static FORCEINLINE int32 Stricmp( const ANSICHAR* String1 , const ANSICHAR* String2 )
	{
		return _stricmp( String1 , String2 );
	}

	template<typename CharType1 , typename CharType2>
	static FORCEINLINE int32 Stricmp(const CharType1* String1, const CharType2* String2)
	{
		return SGenericPlatformStricmp::Stricmp(String1, String2);
	}

	static FORCEINLINE int32 Strnicmp( const ANSICHAR* String1 , const ANSICHAR* String2 , SIZE_T Count )
	{
		return _strnicmp( String1 , String2 , Count );
	}

	static FORCEINLINE int32 Strlen( const ANSICHAR* String )
	{
		return (int32)strlen( String );
	}

	static FORCEINLINE const ANSICHAR* Strstr( const ANSICHAR* String , const ANSICHAR* Find )
	{
		return strstr( String , Find );
	}

	static FORCEINLINE const ANSICHAR* Strchr( const ANSICHAR* String , ANSICHAR c )
	{
		return strchr( String , c );
	}

	// @return Returns a pointer to the last occurrence of character in the String.
	static FORCEINLINE const ANSICHAR* Strrchr( const ANSICHAR* String , ANSICHAR c )
	{
		return strrchr( String , c );
	}

	static FORCEINLINE int32 Atoi( const ANSICHAR* String )
	{
		return atoi( String );
	}

	static FORCEINLINE int64 Atoi64( const ANSICHAR* String )
	{
		return _strtoi64( String , NULL , 10 );
	}

	static FORCEINLINE float Atof( const ANSICHAR* String )
	{
		return ( float )atof( String );
	}

	static FORCEINLINE double Atod( const ANSICHAR* String )
	{
		return atof( String );
	}

	static FORCEINLINE int32 Strtoi( const ANSICHAR* Start , ANSICHAR** End , int32 Base )
	{
		return strtol( Start , End , Base );
	}

	static FORCEINLINE uint64 Strtoui64( const ANSICHAR* Start , ANSICHAR** End , int32 Base )
	{
		return _strtoui64( Start , End , Base );
	}

	static FORCEINLINE ANSICHAR* Strtok( ANSICHAR* StrToken , const ANSICHAR* Delim , ANSICHAR** Context )
	{
		return strtok_s( StrToken , Delim , Context );
	}

	static FORCEINLINE int32 GetVarArgs( ANSICHAR* Dest , SIZE_T DestSize , int32 Count , const ANSICHAR*& Format , va_list ArgPtr )
	{
#if USE_SECURE_CRT
		int32 Result = _vsnprintf_s( Dest , DestSize , Count , Format , ArgPtr );
#else
		int32 Result = _vsnprintf_s( Dest, DestSize , Count , Format , ArgPtr );
#endif
		va_end( ArgPtr );
		return Result;
	}
};