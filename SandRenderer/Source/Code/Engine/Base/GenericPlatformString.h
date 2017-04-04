#ifndef GENERIC_PLATFORM_STRING_H
#define GENERIC_PLATFORM_STRING_H

#include "TEnableIf.h"
#include "SMemory.h"

struct SGenericPlatformString
{
public:
	static void* Memcpy(void* Dest, const void* Src, SIZE_T Count);

public:
	template<typename Encoding>
	static bool IsValidChar( Encoding ch )
	{
		return true;
	}

	template<typename DestEncoding , typename SourceEncoding>
	static bool CanConvertChar( SourceEncoding Ch )
	{
		return IsValidChar( Ch ) && ( SourceEncoding )( DestEncoding )Ch == Ch && IsValidChar( ( DestEncoding )Ch );
	}

	/*
		Metafunction which tests whether a given character type represents a fixed-width encoding.
	*/
	template<bool Dummy , typename T>
	struct TIsFixedWidthEncoding_Helper
	{
		enum
		{
			Value = false
		};
	};

	template<bool Dummy>
	struct TIsFixedWidthEncoding_Helper<Dummy , ANSICHAR>
	{
		enum
		{
			Value = true
		};
	};

	template<bool Dummy>
	struct TIsFixedWidthEncoding_Helper<Dummy , WIDECHAR>
	{
		enum
		{
			Value = true
		};
	};

	template<bool Dummy>
	struct TIsFixedWidthEncoding_Helper<Dummy , UCS2CHAR>
	{
		enum
		{
			Value = true
		};
	};

	template<typename T>
	struct TIsFixedWidthEncoding : TIsFixedWidthEncoding_Helper<false , T>
	{

	};

	template<typename EncodingA , typename EncodingB>
	struct TAreEncodingsCompatible
	{
		enum
		{
			Value = TIsFixedWidthEncoding<EncodingA>::Value && TIsFixedWidthEncoding<EncodingB>::Value && sizeof( EncodingA ) == sizeof( EncodingB )
		};
	};

	/*
		@return the number of DestChar elements that Src will be converted into.
	*/
	template<typename DestEncoding , typename SourceEncoding>
	static typename TEnableIf<TIsFixedWidthEncoding<SourceEncoding>::Value && TIsFixedWidthEncoding<DestEncoding>::Value , int32>::Type ConvertedLength( const SourceEncoding* Src , int32 SrcSize )
	{
		return SrcSize;
	}

	/*
		Convert the [Src , Src+SrcSize) string range from SourceChar to DestChar and writes it to the [Dest,Dest+DestSize) range
		The Src range should contain a null-terminator if a null terminator is required in the output.
		If the Dest range is not big enough to hold the converted output. NULL is returned.

		@param Dest		the start of the destination buffer.
		@param DestSize	the size of the destination buffer.
		@param Src		the start of the string to convert.
		@param SrcSize	the number of Src element to convert.
		@return			A pointer to one past the last-written element.
	*/
	template<typename SourceEncoding , typename DestEncoding>
	static typename TEnableIf<TAreEncodingsCompatible<SourceEncoding , DestEncoding>::Value , DestEncoding*>::Type Convert( DestEncoding* Dest , int32 DestSize , const SourceEncoding* Src , int32 SrcSize , DestEncoding BogusChar = ( DestEncoding )'?' )
	{
		if( DestSize < SrcSize )
		{
			return nullptr;
		}

		return (DestEncoding*)Memcpy(Dest, Src, SrcSize * sizeof(SourceEncoding)) + SrcSize;
	}

	template<typename SourceEncoding , typename DestEncoding>
	static typename TEnableIf<!TAreEncodingsCompatible<SourceEncoding , DestEncoding>::Value && TIsFixedWidthEncoding<SourceEncoding>::Value , DestEncoding*>::Type Convert( DestEncoding* Dest , int32 DestSize , const SourceEncoding* Src , int32 SrcSize , DestEncoding BogusChar = ( DestEncoding )'?' )
	{
		const SourceEncoding* InSrc = Src;
		int32 InSrcSize				= SrcSize;
		bool bInvalidChars			= false;

		while( SrcSize )
		{
			if( !DestSize )
			{
				return nullptr;
			}

			SourceEncoding SrcCh = *Src++;
			if( CanConvertChar<DestEncoding>( SrcCh ) )
			{
				*Dest++ = ( DestEncoding )SrcCh;
			}
			else
			{
				*Dest++			= BogusChar;
				bInvalidChars	= false;
			}

			--SrcSize;
			--DestSize;
		}

		if( bInvalidChars )
		{
			// TODO: Print Log..
		}

		return Dest;
	}
};
#endif