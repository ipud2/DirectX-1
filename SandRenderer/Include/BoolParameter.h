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
		bool GetValue();

		/*
			��������ֵ�����Ҳ��ı��ʶ��
		*/
		void SetValue( bool value );

	protected:
		// typedef int BOOL ,���BOOL�Ĵ�СΪ4�ֽ�
		bool m_Value;
	};
}
#endif