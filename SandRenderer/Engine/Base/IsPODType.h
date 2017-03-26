#pragma once

#include "AddOrNot.h"
#include "TIsArithmetic.h"
#include "TIsPointer.h"

#if _MSC_VER == 1900
	#pragma warning(push)
	#pragma warning(disable:4647)
#endif

template<typename T>
struct TIsPODType
{
	enum
	{
		Value = TOrValue<__is_pod( T ) || __is_enum( T ) , TIsArithmetic<T> , TIsPointer<T>>::Value
	};
};

#if _MSC_VER == 1900
	#pragma  warning(pop)
#endif