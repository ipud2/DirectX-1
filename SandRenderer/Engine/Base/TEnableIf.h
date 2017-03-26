#pragma once

/*
	Include a function in an overload set if the predicate is true.
	It should be used similarly to this:
	
	// This function will only be instantiated if SomeTrait<T>::Value is true for a partical T
	template<typename T>
	typename TEnableIf<SomeTrait<T>::Value , ReturnType>::Type Function(T& Obj)
	{
		...
	}

	ReturnType is the real return type of the function
*/
template<bool Predicate , typename Result = void>
class TEnableIf;

template<typename Result>
class TEnableIf<true , Result>
{
public:
	typedef Result Type;
};

template<typename Result>
class TEnableIf<false , Result>
{
};