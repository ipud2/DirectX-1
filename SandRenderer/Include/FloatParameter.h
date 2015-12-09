#ifndef FloatParameter_h
#define FloatParameter_h

#include "BaseNumericTypeRenderParameter.h"

namespace Sand
{
	class FloatParameter : public BaseNumericTypeRenderParameter
	{
	public:
		FloatParameter( std::wstring name );
		FloatParameter( FloatParameter& copy );
		virtual ~FloatParameter();

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
		float GetValue();

		/*
			设置向量值，并且不改变标识符
		*/
		void SetValue( float value );

	protected:
		float m_Value;
	};
}

#endif