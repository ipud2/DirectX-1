#include "PCH.h"
#include "MatrixParameter.h"

using namespace Sand;

MatrixParameter::MatrixParameter()
{
	m_Matrix.MakeIdentity();
}

MatrixParameter::MatrixParameter( MatrixParameter& copy )
{
	m_Matrix = copy.m_Matrix;
}

MatrixParameter::~MatrixParameter()
{

}

void MatrixParameter::SetParameterData( void * pData )
{
	// 逐字节的比较数据与原数据是否一致
	if( 0 != memcmp( pData , &m_Matrix , sizeof( Matrix4f ) ) )
	{
		// 不一致,则更新数据
		m_Matrix = *reinterpret_cast< Matrix4f* >( pData );
		m_IdentifierChange++;
	}
}

const ParameterType MatrixParameter::GetParameterType()
{
	return PT_MATRIX;
}

Matrix4f MatrixParameter::GetMatrix()
{
	return m_Matrix;
}