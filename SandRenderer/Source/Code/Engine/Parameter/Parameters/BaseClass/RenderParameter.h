#ifndef RenderParameter_h
#define RenderParameter_h

#include <Engine/PCH.h>

namespace Sand
{
	enum ParameterType
	{
		// 标量
		PT_FLOAT , 
		PT_BOOL , 
		PT_INT , 

		// 矢量
		PT_VECTOR_4F , 
		PT_VECTOR_3F , 
		PT_VECTOR_2F ,
		PT_MATRIX , 
		PT_MATRIX_ARRAY , 

		// 结构体
		PT_STRUCTURE , 

		// 对象类型
		PT_SHADER_RESOURCE , 
		PT_CONSTANT_BUFFER , 
		PT_UNORDERED_ACCESS , 
		PT_SAMPLER
	};


	class RenderParameter
	{
	public:
		RenderParameter( std::wstring name );
		RenderParameter( RenderParameter& copy );
		virtual ~RenderParameter();

		/*
			获取参数名
		*/
		std::wstring& GetName();

		/*
			获取参数类型
		*/
		virtual const ParameterType GetParameterType() = 0;

		/*
			写入参数值
		*/
		virtual void SetParameterData( void* pData ) = 0;

	protected:
		std::wstring m_Name;
	};
}

#endif