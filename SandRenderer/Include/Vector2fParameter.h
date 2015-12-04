#ifndef Vector2fParameter_h
#define Vector2fParameter_h

#include "BaseNumericTypeRenderParameter.h"
#include "Vector2f.h"

namespace Sand
{
	class Vector2fParameter : public BaseNumericTypeRenderParameter
	{
	public:
		Vector2fParameter( std::wstring name );
		Vector2fParameter( Vector2fParameter& copy );
		virtual ~Vector2fParameter();

		/*
		设置数据，并改变标识符
		*/
		virtual void SetParameterData( void* pData );

		/*
		获取参数类型
		*/
		virtual const ParameterType GetParameterType();

		/*
		获取向量值
		*/
		Vector2f GetVector();

		/*
		设置向量值，并且不改变标识符
		*/
		void SetVector( Vector2f v );

	protected:
		Vector2f m_Vector;
	};
};
#endif