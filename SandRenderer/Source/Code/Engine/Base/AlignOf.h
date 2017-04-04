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

	// ����ElementType���ն����ֽڶ���
	// ����ElementType�ǰ�k�ֽڶ���(k >= 1)����sizeof(ElementType)�ض�Ϊk�ı�������k*n
	// ����FAlignmentElementsֻ���������һ��uint8��Ա,����1 <= k
	// ������Ȼ�ᰴ��k�ֽڶ��룬��ˣ���С����Ϊk * (n + 1)
	// ����CalculatedAlignmentΪk
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

// �ػ���class
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
	// ��Ϊsizeof(ElementType)�ض����ڵ���sizeof(uint8)
	// ���Աض��ǰ���sizeof(ElementType)����
	enum
	{
		Value = sizeof( FAlignedElements ) - sizeof( ElementType )
	};
};

// ����T���ն����ֽڶ���
#define ALIGNOF(T)	(TElementAlignmentCalculator<T>::Value)