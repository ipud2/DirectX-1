#ifndef VectorParameter_h
#define VectorParameter_h

#include "BaseNumericTypeRenderParameter.h"
#include "Vector4f.h"

namespace Sand
{
	class VectorParameter : public BaseNumericTypeRenderParameter
	{
	public:
		VectorParameter();
		VectorParameter( VectorParameter& copy );
		virtual ~VectorParameter();

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