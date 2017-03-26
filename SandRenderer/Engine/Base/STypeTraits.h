#pragma once

#include "PCH.h"
#include "TIsArithmetic.h"
#include "AddOrNot.h"

#define IS_ENUM(T)	__is_enum(T)

template<typename T>
class TIsZeroConstructType
{
	enum
	{
		Value = TOrValue<IS_ENUM( T ), TIsArithmetic<T> , TIsPointer<T>>::Value
	};
};

/*
	TIsCharType
*/
template<typename T>
struct TIsCharType
{
	enum
	{
		Value = false
	};
};

template<>
struct TIsCharType<ANSICHAR>
{
	enum
	{
		Value = true
	};
};

template<>
struct TIsCharType<WIDECHAR>
{
	enum
	{
		Value = true
	};
};

template<>
struct TIsCharType<UCS2CHAR>
{
	enum
	{
		Value = true
	};
};

/*
	TIsSame.
	implement of std::is_same trait.
*/
template<typename A , typename B>
struct TIsSame
{
	enum
	{
		Value = false
	};
};

template<typename T>
struct TIsSame<T , T>
{
	enum
	{
		Value = true
	};
};

template<typename T , typename Arg>
struct TIsBitwiseConstructible
{
	enum
	{
		Value = false
	};
};

template<typename T>
struct TIsBitwiseConstructible<T, T>
{
	enum { Value = TIsTriviallyCopyAssignable<T>::Value };
};

template<typename T , typename U>
struct TIsBitwiseConstructible<const T, U> : TIsBitwiseConstructible<T, U>
{

};

template<typename T>
struct TIsBitwiseConstructible<const T*, T*>
{
	enum
	{
		Value = true
	};
};

// Unsigned types can be bitwise converted to their signed equivalents, and vice versa.
// (assuming two's-complement, which we are)
template <> struct TIsBitwiseConstructible<uint8, int8> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible< int8, uint8> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible<uint16, int16> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible< int16, uint16> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible<uint32, int32> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible< int32, uint32> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible<uint64, int64> { enum { Value = true }; };
template <> struct TIsBitwiseConstructible< int64, uint64> { enum { Value = true }; };