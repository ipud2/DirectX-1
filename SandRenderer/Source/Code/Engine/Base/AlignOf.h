#pragma once

#include "IsClass.h"
#include "TChooseClass.h"
#include "TIntegralConstant.h"

template<typename ElementType , bool IsClass = TIsClass<ElementType>::Value>
class TElementAlignmentCalculator
{
private:
	// in the case of class ElementType , we inherit it to allow abstract types to work.
	struct FAlignmentElements : ElementType
	{
		uint8 MisalignmentPadding;

		FAlignmentElements();
		~FAlignmentElements();
	};

	// 计算ElementType按照多少字节对齐
	// 比如ElementType是按k字节对齐(k >= 1)，则sizeof(ElementType)必定为k的倍数，即k*n
	// 由于FAlignmentElements只额外添加了一个uint8成员,由于1 <= k
	// 则其依然会按照k字节对齐，因此，大小将会为k * (n + 1)
	// 所以CalculatedAlignment为k
	enum
	{
		CalculatedAlignment = sizeof( FAlignmentElements ) - sizeof( ElementType )
	};

public:
	enum
	{
		Value = TChooseClass<CalculatedAlignment != 0 , TIntegralConstant<SIZE_T , CalculatedAlignment> , TElementAlignmentCalculator<ElementType , false>>::Result::Value>
	};
};

// 特化非class
template<typename ElementType>
class TElementAlignmentCalculator<ElementType , false>
{
private:
	/*
		In the case of non-class ElementTypes , we contain it because non-class types cannot be inherited.
	*/
	struct FAlignedElements
	{
		uint8 MisalignmentPadding;
		ElementType Element;

		FAlignedElements();
		~FAlignedElements();
	};

public:
	// 因为sizeof(ElementType)必定大于等于sizeof(uint8)
	// 所以必定是按照sizeof(ElementType)对齐
	enum
	{
		Value = sizeof( FAlignedElements ) - sizeof( ElementType )
	};
};

// 计算T按照多少字节对齐
#define ALIGNOF(T)	(TElementAlignmentCalculator<T>::Value)