#pragma once

#include "TIsPointer.h"
#include "WindowsPlatformMemory.h"

struct SMemory
{
	static FORCEINLINE void* Memmove(void* Dest, const void* Src, SIZE_T Count)
	{
		return SPlatformMemory::Memmove(Dest, Src, Count);
	}

	static __forceinline void* Memcpy( void* Dest , const void* Src , SIZE_T Count )
	{
		return SPlatformMemory::Memcpy( Dest , Src , Count );
	}

	template<class T>
	static __forceinline void Memcpy( T& Dest , const T& Src )
	{
		static_assert( !TIsPointer<T>::Value , "For pointers use the three parameters function" );
		Memcpy( &Dest , &Src , sizeof( T ) );
	}
};