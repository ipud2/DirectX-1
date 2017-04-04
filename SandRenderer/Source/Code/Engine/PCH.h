// Ô¤±àÒëÍ·ÎÄ¼þ
#ifndef PCH_h
#define PCH_h

#ifndef STRICT
#define STRICT
#endif

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

// Standard C++ Library
#include <fstream>
#include <string.h>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>

// Standard C Library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <assert.h>
#include <fcntl.h>
#include <io.h>

// DirectX Header
#include <d3d11.h>
#include <d3dCompiler.h>

#include <wrl.h>

#define SAFE_RELEASE(x) {if(x){(x)->Release(); (x) = nullptr;}}
#define SAFE_DELETE(x) {if(x){delete (x); (x) = nullptr;}}
#define SAFE_DELETE_ARRAY(x) {if(x){delete[] x; (x) = nullptr;}}
#define SAFE_FREE(x)	{if(x){free((x)); (x) = nullptr;}}

#define SAND_PI 3.14159265f

#define ConvertToRadius(fDegree)	(fDegree) * (SAND_PI / 180.0f)

#define GET_X_LPARAM(lp)	((int)(short)((WORD)(((DWORD_PTR)(lp)) & 0xffff)))
#define GET_Y_LPARAM(lp)	((int)(short)((WORD)((((DWORD_PTR)(lp)) >> 16) & 0xffff)))

#define int64	signed long long
#define uint64	unsigned long long
#define int32	int
#define uint32	unsigned int
#define int16	signed short
#define uint16	unsigned short
#define int8	signed char
#define uint8	unsigned char
#define Float	float
#define ushort	unsigned short int

#define VBit(i)	1 << i
enum EInputMask
{
	EIM_NONE = VBit( 0 ) ,
	EIM_POSITION = VBit( 1 ) ,
	EIM_NORMAL = VBit( 2 ) ,
	EIM_TANGENT = VBit( 3 ) ,
	EIM_WEIGHT = VBit( 4 ) ,
	EIM_TEXCOORD0 = VBit( 5 ) ,
	EIM_TEXCOORD1 = VBit( 6 ) ,
	EIM_TEXCOORD2 = VBit( 7 ) ,
	EIM_TEXCOORD3 = VBit( 8 ) ,
	EIM_TEXCOORD4 = VBit( 9 ) ,
	EIM_TEXCOORD5 = VBit( 10 ) ,
	EIM_TEXCOORD6 = VBit( 11 ) ,
	EIM_TEXCOORD7 = VBit( 12 ) ,
	EIM_COLOR = VBit( 13 )
};

enum EMapType
{
	EMT_DIFFUSE ,
	EMT_NORMAL ,
	EMT_SPECULAR ,
	EMT_METAILLC ,
	EMT_ROUGHNESS ,
	EMT_EMISSIVE ,
	EMT_MAPNUM
};

#define EPSILON 10e-5f

enum { INDEX_NONE = -1 };

typedef wchar_t TCHAR;
typedef wchar_t WIDECHAR;
typedef char	ANSICHAR;
// A 16-bit character containing a UCS2 (Unicode, 16-bit, fixed-width) code unit, used for compatibility with 'Windows TCHAR' across multiple platforms.
typedef unsigned short UCS2CHAR;

typedef signed long long PTRINT;

#define Max_int8	((int8)		0x7f)
#define Max_int16	((int16)	0x7fff)
#define Max_int32	((int32)	0x7fffffff)
#define Max_int64	((int64)	0x7fffffffffffffff)
#define Max_uint8	((uint8)	0xff)
#define Max_uint16	((uint16)	0xffff)
#define Max_uint32	((uint32)	0xffffffff)
#define Max_uint64	((uint64)	0xffffffffffffffff)

#ifndef RESTRICT
#define RESTRICT	__restrict
#endif

#endif // PCH_h