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
	// 若矩阵个数不一致，则改为新的矩阵数
	if( this->m_iMatrixCount != copy.m_iMatrixCount )
	{
		delete[] m_pMatrices;
		// 创建新的矩阵数组
		m_pMatrices = new Matrix4f[copy.m_iMatrixCount];

		this->m_iMatrixCount = copy.m_iMatrixCount;
	}

	// 拷贝数据
	memcpy( m_pMatrices , copy.m_pMatrices , sizeof( Matrix4f ) * m_iMatrixCount );
}

MatrixArrayParameter& MatrixArrayParameter::operator=( MatrixArrayParameter& parameter )
{
	// 若矩阵个数不一样，则改为新的矩阵数
	if( this->m_iMatrixCount != parameter.m_iMatrixCount )
	{
		delete[] m_pMatrices;
		// 创建新的矩阵数组
		m_pMatrices = new Matrix4f[parameter.m_iMatrixCount];

		this->m_iMatrixCount = parameter.m_iMatrixCount;
	}

	// 拷贝数据
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
	// 默认个数一致
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