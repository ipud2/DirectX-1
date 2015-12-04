#ifndef Vector4fParameter_h
#define Vector4fParameter_h

#include "BaseNumericTypeRenderParameter.h"
#include "Vector4f.h"

namespace Sand
{
	class Vector4fParameter : public BaseNumericTypeRenderParameter
	{
	public:
		Vector4fParameter( std::wstring name );
		Vector4fParameter( Vector4fParameter& copy );
		virtual ~Vector4fParameter();

		/*
			设置数据，将会改变标识符
		*/
		virtual void SetParameterData( void* pData );

		/*
			获取参数类型
		*/
		virtual const ParameterType GetParameterType();

		/*
			获取向量值
		*/
		Vector4f GetVector();
		
		/*
			设置向量值，并且不改变标识符
		*/
		void SetVector( Vector4f v );

	protected:
		Vector4f m_Vector;
	};
};
#endif