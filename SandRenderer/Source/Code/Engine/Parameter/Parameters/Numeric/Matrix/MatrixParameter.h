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
			设置新的矩阵值，若新的值与原来的值不一样，则会改变标识符
		*/
		virtual void SetParameterData( void * pData );

		/*
			获取参数类型
		*/
		virtual const ParameterType GetParameterType();

		/*
			获取参数值
		*/
		Matrix4f GetMatrix();

	protected:
		Matrix4f m_Matrix;
	};
};
#endif