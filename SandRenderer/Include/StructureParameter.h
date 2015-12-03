#ifndef StructureParameter_h
#define StructureParameter_h

#include "BaseNumericTypeRenderParameter.h"

namespace Sand
{
	class StructureParameter : public BaseNumericTypeRenderParameter
	{
	public:
		StructureParameter( std::wstring name , int size );
		StructureParameter( StructureParameter& copy );
		virtual ~StructureParameter();

		/*
			设置新的矩阵值，若新的值与原来的值不一样，则会改变标识符
		*/
		virtual void SetParameterData( void * pData );

		/*
			获取参数类型
		*/
		virtual const ParameterType GetParameterType();

		char* GetStructureData();
		int GetStructureSize();

	protected:
		char *m_pData;

		// 结构体的总大小，若为结构体数组，则为该数组的总大小
		int m_Size;
	};
};
#endif