#ifndef SSTRING_H
#define SSTRING_H

#include "TArray.h"
#include "TestTemplate.h"
#include "CString.h"
#include "SMemory.h"
#include "MemoryOps.h"

namespace ESearchCase
{
	enum Type
	{
		// Case sensitive. Upper/lower casing must match for strings to be considered equal.
		CaseSensitive , 

		// Ignore case. Upper/lower casing does not matter when making a comparison.
		IgnoreCase
	};
}

namespace ESearchDir
{
	enum Type
	{
		// Search from the start, moving forward through the string.
		FromStart , 

		// Search from the end, moving backward through the string.
		FromEnd,
	};
};

class SString
{
public:
	FORCEINLINE SString()
	{

	}
	
	FORCEINLINE SString( SString&& Other )
		:m_pData( MoveTemp( Other.m_pData ) )
	{

	}

	FORCEINLINE SString( const SString& Other )
		: m_pData( Other.m_pData )
	{

	}

	FORCEINLINE SString& operator=( SString&& Other )
	{
		m_pData = MoveTemp( Other.m_pData );
		return *this;
	}

	FORCEINLINE SString& operator= ( const SString& Other )
	{
		m_pData = Other.m_pData;
		return *this;
	}

	FORCEINLINE SString( const SString& Other , int32 ExtraSlack )
		:m_pData( Other.m_pData , ExtraSlack + ( ( Other.m_pData.GetSize() || !ExtraSlack ) ? 0 : 1 ) )
	{

	}
	/*
		Constructor using an array of TCHAR
		TEnableIf is to ensure we don't instantiate this constructor for non-char types
	*/
	template<typename CharType>
	SString( const CharType* Src , typename TEnableIf<TIsCharType<CharType>::Value>::Type* Dummy = nullptr )
	{
		if( Src && *Src )
		{
			int32 SrcLen = TCString<CharType>::Strlen( Src ) + 1;
			int32 DestLen = SPlatformString::ConvertedLength<TCHAR>( Src , SrcLen );

			m_pData.AddUninitialized( DestLen );

			SPlatformString::Convert( m_pData.GetData() , DestLen , Src , SrcLen );
		}
	}

	FORCEINLINE explicit SString( int32 InCount , const TCHAR* InSrc )
	{
		m_pData.AddUninitialized( InCount ? InCount + 1 : 0 );
		
		if( m_pData.GetSize() > 0 )
		{
			SCString::Strncpy( m_pData.GetData() , InSrc , InCount + 1 );
		}
	}

	FORCEINLINE SString& operator=( const TCHAR* Other )
	{
		if( m_pData.GetData() != Other )
		{
			int32 Len = ( Other && *Other ) ? SCString::Strlen( Other ) + 1 : 0;
			m_pData.Empty( Len );
			m_pData.AddUninitialized( Len );

			if( Len )
			{
				SMemory::Memcpy( m_pData.GetData() , Other , Len * sizeof( TCHAR ) );
			}
		}
	}
	
	FORCEINLINE int32 Length() const
	{
		return m_pData.GetSize() ? m_pData.GetSize() - 1 : 0;
	}

	FORCEINLINE bool IsValidIndex( int32 index ) const
	{
		return index >= 0 && index < Length();
	}

	FORCEINLINE TCHAR& operator[]( int32 index )
	{
		assert( IsValidIndex( index ) );

		return m_pData.GetData()[index];
	}

	FORCEINLINE const TCHAR& operator[]( int32 Index ) const
	{
		assert( IsValidIndex( Index ) );
		return m_pData.GetData()[Index];
	}

	FORCEINLINE bool IsEmpty() const
	{
		return m_pData.GetSize() <= 1;
	}

	// Create empty string of given size with zero terminating character.
	// @param Slack length of empty string to create.
	FORCEINLINE void Empty( int Slack = 0 )
	{
		m_pData.Empty( Slack );
	}

	// returns a pointer to the underlying array serving as character storage.
	// the pointer is such that the range[AsChar(); AsChar() + size();] is valid
	// and the values in it correspond to the values stored in the string.
	// 1) Modifying the character array accessed through data has undefined behavior.
	// 2) Modifyiing the past-the-end null terminator stored at data() + size() has undefined behavior.
	const TCHAR* AsChar() const
	{
		return m_pData.GetData();
	}

	FORCEINLINE void AppendChars( const TCHAR* Array , int32 Count )
	{
		assert( Count >= 0 );
		if( !Count )	return;

		int32 Index = m_pData.GetSize();
		// Reserve enough space - including an extra gap for a null terminator if we don't already have a string allocated.
		m_pData.AddUninitialized( Count + ( Index ? 0 : 1 ) );
		
		TCHAR* EndPtr = m_pData.GetData() + Index - ( Index ? 1 : 0 );

		CopyAssignItems( EndPtr , Array , Count );

		*( EndPtr + Count ) = 0;
	}


	FORCEINLINE SString& operator+=(const TCHAR* Str)
	{
		AppendChars( Str , SCString::Strlen( Str ) );

		return *this;
	}

	template<typename CharType>
	FORCEINLINE typename TEnableIf<TIsCharType<CharType>::Value , SString&>::Type operator+=( CharType InChar )
	{
		if( InChar != 0 )
		{
			int32 InsertIndex = m_pData.GetSize() ? m_pData.GetSize() - 1 : 0;

			int32 InsertCount = m_pData.GetSize() > 0 ? 1 : 2;

			m_pData.AddUninitialized( InsertCount );
			m_pData[InsertIndex]		= InChar;
			m_pData[InsertIndex + 1]	= 0;
		}

		return *this;
	}

	FORCEINLINE SString& AppendChar( const TCHAR InChar )
	{
		*this += InChar;
		return *this;
	}

	FORCEINLINE SString& Append( const SString& Text )
	{
		*this += Text;
		return *this;
	}

	SString& Append( const TCHAR* Text , int32 Count )
	{
		if( Count != 0 )
		{
			int32 InsertIndex = m_pData.GetSize() > 0 ? m_pData.GetSize() - 1 : 0;

			int32 FinalCount = ( m_pData.GetSize() > 0 ) ? Count : Count + 1;

			m_pData.AddUninitialized( FinalCount );

			for( int32 Index = 0; Index < Count; Index++ )
			{
				m_pData[InsertIndex + Index] = Text[Index];
			}

			m_pData[m_pData.GetSize() - 1] = 0;
		}

		return *this;
	}

	FORCEINLINE SString& operator+=( const SString& Str )
	{
		AppendChars( Str.m_pData.GetData() , Str.Length() );
		return *this;
	}

	template<typename CharType>
	FORCEINLINE friend typename TEnableIf<TIsCharType<CharType>::Value , SString>::Type operator+( const SString& Lhs , CharType Rhs )
	{
		SString Result( Lhs , 1 );
		Result += Rhs;
		return Result;
	}

	template<typename CharType>
	FORCEINLINE friend typename TEnableIf<TIsCharType<CharType>::Value , SString>::Type operator+( const SString&& Lhs , CharType Rhs )
	{
		SString Result( MoveTemp( Lhs ) , 1 );
		Result += Rhs;
		return Result;
	}

	// Searches the string for a substring, and returns index into this string
	// of the first found instance. Can search from begining or end, and ignore case or not
	//
	// @param str				The string array of char to search for
	// @param StartPosition		The start character position to search from
	// @param SearchCase		Indicates whether the search is case sensitive or not
	// @param SearchDir			Indicates whether the search starts at the begining or at the end
	int32 Find( const TCHAR* str , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase , ESearchDir::Type SearchDir = ESearchDir::FromStart , int32 StartPosition = INDEX_NONE ) const;

	FORCEINLINE int32 Find( const SString& SubStr , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase , ESearchDir::Type SearchDir = ESearchDir::FromStart , int32 StartPosition = INDEX_NONE ) const
	{
		return Find( SubStr.AsChar() , SearchCase , SearchDir , StartPosition );
	}

	FORCEINLINE bool Contains( const TCHAR* SubStr , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase , ESearchDir::Type SearchDir = ESearchDir::FromStart , int32 StartPosition = INDEX_NONE ) const
	{
		return Find( SubStr , SearchCase , SearchDir , StartPosition ) != INDEX_NONE;
	}

	FORCEINLINE bool Contains( const SString& SubStr , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase , ESearchDir::Type SearchDir = ESearchDir::FromStart , int32 StartPosition = INDEX_NONE ) const
	{
		return Find( SubStr , SearchCase , SearchDir , StartPosition ) != INDEX_NONE;
	}

	FORCEINLINE bool Equals( const SString& Other , ESearchCase::Type SearchCase = ESearchCase::CaseSensitive )
	{
		if( SearchCase == ESearchCase::IgnoreCase )
		{
			return SCString::Stricmp( m_pData.GetData() , Other.AsChar() ) == 0;
		}
		else
		{
			return SCString::Strcmp( m_pData.GetData() , Other.AsChar() ) == 0;
		}
	}

	bool Split( const SString& Str , SString* LeftStr , SString* RightStr , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase , ESearchDir::Type SearchDir = ESearchDir::FromStart ) const
	{
		int32 InPos = Find( Str , SearchCase , SearchDir );
		if( InPos < 0 ) return false;

		if( LeftStr ) *LeftStr = Left( InPos );

		if( RightStr ) *RightStr = Mid( InPos + Str.Length() );

		return true;
	}
	
	// return the left most given number of characters.
	FORCEINLINE SString Left( int32 Count ) const
	{
		int Len = Length();
		return SString( Count < 0 ? 0 : ( Count > Len ? Len : Count ) , m_pData.GetData() );
	}

	// return the string to the right of specified location , counting back from the right (end of the word).
	FORCEINLINE SString Right( int32 Count ) const
	{
		int len = Length();
		return SString( m_pData.GetData() + ( Count < 0 ? 0 : ( Count > len ? len : Count ) ) );
	}

	// return the substring from start position for count characters.
	FORCEINLINE SString Mid( int32 Start , int Count = Max_int32 ) const
	{
		int32 End = Start + Count;
		Start	= Start < 0 ? 0 : ( Start > Length() ? Length() : Start );
		End		= End < 0 ? 0 : ( End > Length() ? Length() : End );

		return SString( End - Start , m_pData.GetData() + Start );
	}

	SString ToLower() const;
	SString ToUpper() const;

	void ToLowerInline();
	void ToUpperInline();

	bool StartsWith( const TCHAR* InPrefix , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase ) const;

	bool StartsWith( const SString& InPrefix , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase ) const;

	bool EndWith( const TCHAR* InPrefix , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase ) const;

	bool EndWith( const SString& InPrefix , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase ) const;

	static SString Format( const TCHAR* FormatString , ... );

	void AppendFormat( const TCHAR* FormatString , ... );

	SString Replace( const TCHAR* From , const TCHAR* To , ESearchCase::Type SearchCase = ESearchCase::IgnoreCase );

protected:
	void AppendFormat( const TCHAR* FormatString , va_list& args );

private:
	TArray<TCHAR> m_pData;
};

#endif