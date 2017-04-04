#ifndef MatrixParameter_h
#define MatrixParameter_h

#include "Engine/Parameter/Parameters/BaseClass/BaseNumericTypeRenderParameter.h"
#include "Engine/Math/Matrix4f.h"

namespace Sand
{
	class MatrixParameter : public BaseNumericTypeRenderParameter
	{
	public:
		MatrixParameter( std::wstring name );
		MatrixParameter( MatrixParameter& copy );
		virtual ~MatrixParameter();

		/*
			�����µľ���ֵ�����µ�ֵ��ԭ����ֵ��һ�������ı��ʶ��
		*/
		virtual void SetParameterData( void * pData );

		/*
			��ȡ��������
		*/
		virtual const ParameterType GetParameterType();

		/*
			��ȡ����ֵ
		*/
		Matrix4f GetMatrix();

	protected:
		Matrix4f m_Matrix;
	};
};
#endif