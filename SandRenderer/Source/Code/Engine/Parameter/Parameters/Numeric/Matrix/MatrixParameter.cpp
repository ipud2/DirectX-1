#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Numeric/Matrix/MatrixParameter.h"

using namespace Sand;

MatrixParameter::MatrixParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	m_Matrix.MakeIdentity();
}

MatrixParameter::MatrixParameter( MatrixParameter& copy )
	: BaseNumericTypeRenderParameter( copy )
{
	m_Matrix = copy.m_Matrix;
}

MatrixParameter::~MatrixParameter()
{

}

void MatrixParameter::SetParameterData( void * pData )
{
	// ���ֽڵıȽ�������ԭ�����Ƿ�һ��
	if( 0 != memcmp( pData , &m_Matrix , sizeof( Matrix4f ) ) )
	{
		// ��һ��,���������
		m_Matrix = *reinterpret_cast< Matrix4f* >( pData );
		m_Identifier++;
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