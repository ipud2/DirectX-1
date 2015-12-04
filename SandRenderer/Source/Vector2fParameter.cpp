#include "PCH.h"
#include "Vector2fParameter.h"

using namespace Sand;

Vector2fParameter::Vector2fParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// 清零
	m_Vector.MakeZero();
}

Vector2fParameter::Vector2fParameter( Vector2fParameter& copy )
	:BaseNumericTypeRenderParameter( copy )
{
	m_Vector = copy.m_Vector;
}

Vector2fParameter::~Vector2fParameter()
{

}

void Vector2fParameter::SetParameterData( void* pData )
{
	// 逐字节比较数据是否是一样的
	if ( 0 != memcmp( pData , &m_Vector , sizeof( Vector2f ) ) )
	{
		// 非0表示是不一样的数据
		m_Identifier++;
		m_Vector = *reinterpret_cast< Vector2f* >( pData );
	}
}

const ParameterType Vector2fParameter::GetParameterType()
{
	return PT_VECTOR_3F;
}

Vector2f Vector2fParameter::GetVector()
{
	return m_Vector;
}

void Vector2fParameter::SetVector( Vector2f v )
{
	// 若不一致，则设置为新的值
	if ( m_Vector != v )
	{
		m_Vector = v;
	}
}