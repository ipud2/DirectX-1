#pragma once

#include "AddOrNot.h"
#include "IsPODType.h"

template<typename T>
struct TIsTriviallyCopyAssignable
{
	enum
	{
		Value = TOrValue<__has_trivial_assign( T ) , TIsPODType<T>>::Value
	};
};