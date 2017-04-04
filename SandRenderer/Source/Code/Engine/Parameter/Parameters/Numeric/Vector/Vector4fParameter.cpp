#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Numeric/Vector/Vector4fParameter.h"

using namespace Sand;

Vector4fParameter::Vector4fParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// 清零
	m_Vector.MakeZero();
}

Vector4fParameter::Vector4fParameter( Vector4fParameter& copy )
	:BaseNumericTypeRenderParameter( copy )
{
	m_Vector = copy.m_Vector;
}

Vector4fParameter::~Vector4fParameter()
{

}

void Vector4fParameter::SetParameterData( void* pData )
{
	// 逐字节比较数据是否是一样的
	if( 0 != memcmp( pData , &m_Vector , sizeof( Vector4f ) ) )
	{
		// 非0表示是不一样的数据
		m_Identifier++;
		m_Vector = *reinterpret_cast< Vector4f* >( pData );
	}
}

const ParameterType Vector4fParameter::GetParameterType()
{
	return PT_VECTOR_4F;
}

Vector4f Vector4fParameter::GetVector()
{
	return m_Vector;
}

void Vector4fParameter::SetVector( Vector4f v )
{
	// 若不一致，则设置为新的值
	if( m_Vector != v )
	{
		m_Vector = v;
	}
}