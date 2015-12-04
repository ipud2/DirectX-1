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
			�������ݣ�����ı��ʶ��
		*/
		virtual void SetParameterData( void* pData );

		/*
			��ȡ��������
		*/
		virtual const ParameterType GetParameterType();

		/*
			��ȡ����ֵ
		*/
		Vector4f GetVector();
		
		/*
			��������ֵ�����Ҳ��ı��ʶ��
		*/
		void SetVector( Vector4f v );

	protected:
		Vector4f m_Vector;
	};
};
#endif