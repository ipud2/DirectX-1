#pragma once

#include "AlignOf.h"
#include "WindowsPlatform.h"

template<int32 Size , uint32 Alignment>
struct TAlignedBytes;

// unaligned storage.
template<int32 Size>
struct TAlignedBytes<Size , 1>
{
	uint8 Pad[Size];
};

// c++/cli doesn't supoort alignment of native types in managed code, so we enforce that the element
// size is a multiple of the desired alignment
#ifdef __cplusplus_cli
#define  IMPLEMENT_ALIGNED_STORAGE(Align)\
		template<int32 Size>	\
		struct TAlignedBytes<Size , Align>	\
		{	\
			uint8 Pad[Size];	\
			static assert(Size % Align == 0 , "CLR interop types must not be aligned.");	\
		};
#else
#define IMPLEMENT_ALIGNED_STORAGE(Align)\
	template<int32 Size>\
	struct TAlignedBytes<Size , Align>	\
	{	\
		struct MS_ALIGN(Align) TPadding \
		{\
			uint8 Pad[Size];	\
		};	\
		TPadding Padding;		\
	};
#endif

IMPLEMENT_ALIGNED_STORAGE(16);
IMPLEMENT_ALIGNED_STORAGE( 8 );
IMPLEMENT_ALIGNED_STORAGE( 4 );
IMPLEMENT_ALIGNED_STORAGE( 2 );

#undef IMPLEMENT_ALIGNED_STORAGE

template<typename ElementType>
struct TTypeCompatibleBytes : public TAlignedBytes<sizeof( ElementType ) , ALIGNOF( ElementType )>
{

};