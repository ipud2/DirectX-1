#include "PCH.h"
#include "VectorParameter.h"

using namespace Sand;

VectorParameter::VectorParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// 清零
	m_Vector.MakeZero();
}

VectorParameter::VectorParameter( VectorParameter& copy )
	:BaseNumericTypeRenderParameter( copy )
{
	m_Vector = copy.m_Vector;
}

VectorParameter::~VectorParameter()
{

}

void VectorParameter::SetParameterData( void* pData )
{
	// 逐字节比较数据是否是一样的
	if( 0 != memcmp( pData , &m_Vector , sizeof( Vector4f ) ) )
	{
		// 非0表示是不一样的数据
		m_Identifier++;
		m_Vector = *reinterpret_cast< Vector4f* >( pData );
	}
}

const ParameterType VectorParameter::GetParameterType()
{
	return PT_VECTOR;
}

Vector4f VectorParameter::GetVector()
{
	return m_Vector;
}

void VectorParameter::SetVector( Vector4f v )
{
	// 若不一致，则设置为新的值
	if( m_Vector != v )
	{
		m_Vector = v;
	}
}