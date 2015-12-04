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
		Vector3f GetVector();

		/*
			��������ֵ�����Ҳ��ı��ʶ��
		*/
		void SetVector( Vector3f v );

	protected:
		Vector3f m_Vector;
	};
};
#endif