#include "PCH.h"
#include "Vector3fParameter.h"

using namespace Sand;

Vector3fParameter::Vector3fParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// 清零
	m_Vector.MakeZero();
}

Vector3fParameter::Vector3fParameter( Vector3fParameter& copy )
	:BaseNumericTypeRenderParameter( copy )
{
	m_Vector = copy.m_Vector;
}

Vector3fParameter::~Vector3fParameter()
{

}

void Vector3fParameter::SetParameterData( void* pData )
{
	// 逐字节比较数据是否是一样的
	if ( 0 != memcmp( pData , &m_Vector , sizeof( Vector3f ) ) )
	{
		// 非0表示是不一样的数据
		m_Identifier++;
		m_Vector = *reinterpret_cast< Vector3f* >( pData );
	}
}

const ParameterType Vector3fParameter::GetParameterType()
{
	return PT_VECTOR_3F;
}

Vector3f Vector3fParameter::GetVector()
{
	return m_Vector;
}

void Vector3fParameter::SetVector( Vector3f v )
{
	// 若不一致，则设置为新的值
	if ( m_Vector != v )
	{
		m_Vector = v;
	}
}