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
		Vector2f GetVector();

		/*
		��������ֵ�����Ҳ��ı��ʶ��
		*/
		void SetVector( Vector2f v );

	protected:
		Vector2f m_Vector;
	};
};
#endif