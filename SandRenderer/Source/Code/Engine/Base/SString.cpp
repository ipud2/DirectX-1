#include <Engine/PCH.h>
#include "TEnableIf.h"
#include "TChar.h"
#include "SString.h"
#include "TChar.h"

int32 SString::Find( const TCHAR* str , ESearchCase::Type SearchCase , ESearchDir::Type SearchDir , int32 StartPostion ) const
{
	if( str == nullptr )
	{
		return INDEX_NONE;
	}

	if( SearchDir == ESearchDir::FromStart )
	{
		const TCHAR* Start = m_pData.GetData();

		if( StartPostion != INDEX_NONE )
		{
			Start += StartPostion < 0 ? 0 : ( StartPostion > Length() - 1 ? Length() - 1 : StartPostion );
		}

		const TCHAR* Tmp = SearchCase == ESearchCase::IgnoreCase ? SCString::Stristr( Start , str ) : SCString::Strstr( Start , str );

		return Tmp ? (int32)(Tmp - m_pData.GetData()) : INDEX_NONE;
	}
	else
	{
		if( SearchCase == ESearchCase::IgnoreCase )
		{
			return ToUpper().Find( SString( str ).ToUpper() , ESearchCase::CaseSensitive , SearchDir , StartPostion );
		}
		else
		{
			const int32 SearchStringLength = SCString::Strlen( str ) > 1 ? SCString::Strlen( str ) : 1;

			if( StartPostion == INDEX_NONE )
			{
				StartPostion = Length();
			}

			for( int32 i = StartPostion - SearchStringLength; i >= 0; i-- )
			{
				int32 j;
				for( j = 0; str[j]; j++ )
				{
					if( ( *this )[i + j] != str[j] )
					{
						break;
					}
				}

				if( !str[j] )
				{
					return i;
				}
			}
			return INDEX_NONE;
		}
	}
}

SString SString::ToLower() const
{
	SString NewString( m_pData.GetData() );
	NewString.ToLowerInline();
	return NewString;
}

SString SString::ToUpper() const
{
	SString NewString( m_pData.GetData() );
	NewString.ToUpperInline();
	return NewString;
}

void SString::ToLowerInline()
{
	const int32 StringLength = Length();
	TCHAR* pData = m_pData.GetData();
	for( int i = 0; i < StringLength; i++ )
	{
		pData[i] = SChar::ToLower( pData[i] );
	}
}

void SString::ToUpperInline()
{
	const int32 StringLength = Length();
	TCHAR* pData = m_pData.GetData();
	for( int i = 0; i < StringLength; i++ )
	{
		pData[i] = SChar::ToUpper( pData[i] );
	}
}

bool SString::StartsWith( const SString& InPrefix , ESearchCase::Type SearchCase /* = ESearchCase::IgnoreCase */ ) const
{
	if( SearchCase == ESearchCase::IgnoreCase )
	{
		return InPrefix.Length() > 0 && !SCString::Stricmp( m_pData.GetData() , InPrefix.AsChar());
	}
	else
	{
		return InPrefix.Length() > 0 && !SCString::Strcmp( m_pData.GetData() , InPrefix.AsChar() );
	}
}

bool SString::StartsWith( const TCHAR* InPrefix , ESearchCase::Type SearchCase /* = ESearchCase::IgnoreCase */ ) const
{
	if( SearchCase == ESearchCase::IgnoreCase )
	{
		return InPrefix && *InPrefix && !SCString::Strnicmp( m_pData.GetData() , InPrefix , SCString::Strlen( InPrefix ) );
	}
	else
	{
		return InPrefix && *InPrefix && !SCString::Strncmp( m_pData.GetData() , InPrefix , SCString::Strlen( InPrefix ) );
	}
}

bool SString::EndWith( const SString& InSuffix , ESearchCase::Type SearchCase /* = ESearchCase::IgnoreCase */ ) const
{
	if( SearchCase == ESearchCase::IgnoreCase )
	{
		return InSuffix.Length() > 0 && Length() > InSuffix.Length() && !SCString::Stricmp( m_pData.GetData() + Length() - InSuffix.Length() , InSuffix.AsChar() );
	}
	else
	{
		return InSuffix.Length() > 0 && Length() > InSuffix.Length() && !SCString::Strcmp( m_pData.GetData() + Length() - InSuffix.Length() , InSuffix.AsChar() );
	}
}

bool SString::EndWith( const TCHAR* InSuffix , ESearchCase::Type SearchCase /* = ESearchCase::IgnoreCase */ ) const
{
	if( !InSuffix || *InSuffix == TEXT( '\0' ) )
	{
		return false;
	}

	int Len = Length();
	int SuffixLen = SCString::Strlen( InSuffix );

	if( SuffixLen > Len )	return false;

	const TCHAR* Ptr = m_pData.GetData() + Len - SuffixLen;
	if( SearchCase == ESearchCase::IgnoreCase )
	{
		return !SCString::Strnicmp( Ptr , InSuffix , SuffixLen );
	}
	else
	{
		return !SCString::Strncmp( Ptr , InSuffix , SuffixLen );
	}
}

SString SString::Replace( const TCHAR* From , const TCHAR* To , ESearchCase::Type SearchCase /* = ESearchCase::IgnoreCase */ )
{
	if( IsEmpty() || !From || !To )
	{
		return *this;
	}

	const TCHAR* Travel = m_pData.GetData();

	int32 FromLength	= SCString::Strlen( From );
	int32 ToLength		= SCString::Strlen( To );

	SString Result;
	while( true )
	{
		const TCHAR* FromLocation = SearchCase == ESearchCase::IgnoreCase ? SCString::Stristr( Travel , From ) : SCString::Strstr( Travel , From );

		if( !FromLocation )
		{
			break;
		}

		Result.AppendChars(Travel, (int32)(FromLocation - Travel));

		Result.Append( To , ToLength );

		Travel = FromLocation + FromLength;
	}

	Result += Travel;

	return Result;
}

SString SString::Format( const TCHAR* format , ... )
{
	SString DestString;

	va_list args;
	va_start(args, format);
	DestString.AppendFormat( format , args );
	va_end( args );

	return DestString;
}

void SString::AppendFormat( const TCHAR* format , ... )
{
	va_list args;
	va_start( args , format );
	AppendFormat( format , args );
	va_end( args );
}

void SString::AppendFormat( const TCHAR* format , va_list& args )
{
	TCHAR Dest[1024];
	vswprintf_s( Dest , format , args );
	AppendChars( Dest , SCString::Strlen( Dest ) );
}