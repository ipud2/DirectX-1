#include "PCH.h"
#include "MatrixArrayParameter.h"

using namespace Sand;

MatrixArrayParameter::MatrixArrayParameter( std::wstring name , int count )
	:BaseNumericTypeRenderParameter( name )
{
	if( count < 1 )
	{
		count = 1;
	}

	m_iMatrixCount = count;

	m_pMatrices = new Matrix4f[count];
}

MatrixArrayParameter::MatrixArrayParameter( MatrixArrayParameter& copy )
	:BaseNumericTypeRenderParameter( copy )
{
	// �����������һ�£����Ϊ�µľ�����
	if( this->m_iMatrixCount != copy.m_iMatrixCount )
	{
		delete[] m_pMatrices;
		// �����µľ�������
		m_pMatrices = new Matrix4f[copy.m_iMatrixCount];

		this->m_iMatrixCount = copy.m_iMatrixCount;
	}

	// ��������
	memcpy( m_pMatrices , copy.m_pMatrices , sizeof( Matrix4f ) * m_iMatrixCount );
}

MatrixArrayParameter& MatrixArrayParameter::operator=( MatrixArrayParameter& parameter )
{
	// �����������һ�������Ϊ�µľ�����
	if( this->m_iMatrixCount != parameter.m_iMatrixCount )
	{
		delete[] m_pMatrices;
		// �����µľ�������
		m_pMatrices = new Matrix4f[parameter.m_iMatrixCount];

		this->m_iMatrixCount = parameter.m_iMatrixCount;
	}

	// ��������
	memcpy( m_pMatrices , parameter.m_pMatrices , sizeof( Matrix4f ) * m_iMatrixCount );

	return *this;
}

MatrixArrayParameter::~MatrixArrayParameter()
{
	delete[] m_pMatrices;
	m_pMatrices = nullptr;
}

void MatrixArrayParameter::SetParameterData( void *pData )
{
	// Ĭ�ϸ���һ��
	if( 0 != memcmp( pData , m_pMatrices , m_iMatrixCount * sizeof( Matrix4f ) ) )
	{
		memcpy( m_pMatrices , pData , m_iMatrixCount * sizeof( Matrix4f ) );
	}
}

const ParameterType MatrixArrayParameter::GetParameterType()
{
	return PT_MATRIX_ARRAY;
}

int MatrixArrayParameter::GetMatrixCount()
{
	return m_iMatrixCount;
}

Matrix4f* MatrixArrayParameter::GetMatrices()
{
	return m_pMatrices;
}