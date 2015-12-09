#ifndef BoolParameter_h
#define BoolParameter_h

#include "BaseNumericTypeRenderParameter.h"

namespace Sand
{
	class BoolParameter : public BaseNumericTypeRenderParameter
	{
	public:
		BoolParameter( std::wstring name );
		BoolParameter( BoolParameter& copy );
		virtual ~BoolParameter();

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
		bool GetValue();

		/*
			设置向量值，并且不改变标识符
		*/
		void SetValue( bool value );

	protected:
		// typedef int BOOL ,因此BOOL的大小为4字节
		bool m_Value;
	};
}
#endif