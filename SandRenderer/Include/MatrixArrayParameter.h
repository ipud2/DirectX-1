#ifndef MatrixArrayParameter_h
#define MatrixArrayParameter_h

#include "BaseNumericTypeRenderParameter.h"
#include "Matrix4f.h"

namespace Sand
{
	class MatrixArrayParameter : public BaseNumericTypeRenderParameter
	{
	public:
		MatrixArrayParameter( int count );
		MatrixArrayParameter( MatrixArrayParameter& copy );
		MatrixArrayParameter& operator=( MatrixArrayParameter&  parameter );
		virtual ~MatrixArrayParameter();

		virtual void SetParameter( void *pData );

		virtual const ParameterType GetParameterType();

		int GetMatrixCount();
		Matrix4f* GetMatrices();

	protected:
		int m_iMatrixCount;
		Matrix4f* m_pMatrices;
	};
};
#endif