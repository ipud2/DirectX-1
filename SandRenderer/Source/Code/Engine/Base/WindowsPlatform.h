#pragma once

#if defined(__clang__)
	#define GCC_PACK(n)	__attribute__((packed,aligned(n)))
	#define GCC_ALIGN(n) __attribute__((aligned(n)))
	#if defined(__MSC_VER)
		#define MS_ALIGN(n)	__declspec(align(n))
	#endif
#else
	#define MS_ALIGN(n)	__declspec(align(n))
#endif