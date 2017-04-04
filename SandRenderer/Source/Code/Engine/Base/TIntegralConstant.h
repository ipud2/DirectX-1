#pragma once

/*
	Defines a value metafunction of the given value
*/
template<typename T , T Val>
struct TIntegralConstant
{
	static const T Value = Val;
};