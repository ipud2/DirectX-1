#pragma once

struct SGenericPlatformMemory
{
	static __forceinline void* Memcpy( void* Dest , const void* Src , SIZE_T Count )
	{
		return memcpy( Dest , Src , Count );
	}

	static __forceinline void* Memset( void* Dest , uint8 Char , SIZE_T Count )
	{
		return memset( Dest , Char , Count );
	}

	static __forceinline void* Memzero( void* Dest , SIZE_T Count )
	{
		return memset( Dest , 0 , Count );
	}

	static __forceinline int32 Memcmp( const void* Buf1 , const void* Buf2 , SIZE_T Count )
	{
		return memcmp( Buf1 , Buf2 , Count );
	}

	static __forceinline void* Memmove( void* Dest , const void* Src , SIZE_T Count )
	{
		return memmove( Dest , Src , Count );
	}
};