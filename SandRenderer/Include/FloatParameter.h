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
			�������ݣ����ı��ʶ��
		*/
		virtual void SetParameterData( void* pData );

		/*
			��ȡ��������
		*/
		virtual const ParameterType GetParameterType();

		/*
			��ȡ����ֵ
		*/
		float GetValue();

		/*
			��������ֵ�����Ҳ��ı��ʶ��
		*/
		void SetValue( float value );

	protected:
		float m_Value;
	};
}

#endif