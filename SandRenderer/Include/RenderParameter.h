#ifndef RenderParameter_h
#define RenderParameter_h

#include "PCH.h"

namespace Sand
{
	enum ParameterType
	{
		// 数值型
		PT_VECTOR , 
		PT_MATRIX , 
		PT_MATRIX_ARRAY , 

		// 对象类型
		PT_SHADER_RESOURCE , 
		PT_CONSTANT_BUFFER , 
		PT_UNORDERED_ACCESS , 
		PT_SAMPLER
	};


	class RenderParameter
	{
	public:
		RenderParameter();
		RenderParameter( RenderParameter& copy );
		virtual ~RenderParameter();

		/*
			设置参数名
		*/
		void SetName( const std::wstring & name );

		/*
			获取参数名
		*/
		std::wstring& GetName();

		/*
			获取参数类型
		*/
		virtual const ParameterType GetParameterType() = 0;

		/*
			使用pData初始化参数
		*/
		void InitializeParameterData( void* pData );

		/*
			写入参数值
		*/
		virtual void SetParameterData( void* pData ) = 0;

	protected:
		std::wstring m_Name;
	};
}

#endif