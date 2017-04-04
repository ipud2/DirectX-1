#ifndef MatrixArrayParameter_h
#define MatrixArrayParameter_h

#include "Engine/Parameter/Parameters/BaseClass/BaseNumericTypeRenderParameter.h"
#include "Engine/Math/Matrix4f.h"

namespace Sand
{
	class MatrixArrayParameter : public BaseNumericTypeRenderParameter
	{
	public:
		MatrixArrayParameter( std::wstring name , int count );
		MatrixArrayParameter( MatrixArrayParameter& copy );
		MatrixArrayParameter& operator=( MatrixArrayParameter&  parameter );
		virtual ~MatrixArrayParameter();

		virtual void SetParameterData( void *pData );

		virtual const ParameterType GetParameterType();

		int GetMatrixCount();
		Matrix4f* GetMatrices();

	protected:
		int m_iMatrixCount;
		Matrix4f* m_pMatrices;
	};
};
#endif