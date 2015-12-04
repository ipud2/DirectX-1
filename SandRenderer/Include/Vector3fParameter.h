#ifndef Vector3fParameter_h
#define Vector3fParameter_h

#include "BaseNumericTypeRenderParameter.h"
#include "Vector3f.h"

namespace Sand
{
	class Vector3fParameter : public BaseNumericTypeRenderParameter
	{
	public:
		Vector3fParameter( std::wstring name );
		Vector3fParameter( Vector3fParameter& copy );
		virtual ~Vector3fParameter();

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
		Vector3f GetVector();

		/*
			设置向量值，并且不改变标识符
		*/
		void SetVector( Vector3f v );

	protected:
		Vector3f m_Vector;
	};
};
#endif