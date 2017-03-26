#include "PCH.h"
#include "SMemory.h"
#include "GenericPlatformString.h"

void* SGenericPlatformString::Memcpy( void* Dest , const void* Src , SIZE_T Count )
{
	return SMemory::Memcpy( Dest , Src , Count );
}

template<>
inline bool SGenericPlatformString::IsValidChar<ANSICHAR>(ANSICHAR Ch)
{
	return Ch >= 0x00 && Ch <= 0x7F;
}