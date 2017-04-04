#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Numeric/Vector/Vector4fParameter.h"

using namespace Sand;

Vector4fParameter::Vector4fParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// ����
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
	// ���ֽڱȽ������Ƿ���һ����
	if( 0 != memcmp( pData , &m_Vector , sizeof( Vector4f ) ) )
	{
		// ��0��ʾ�ǲ�һ��������
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
	// ����һ�£�������Ϊ�µ�ֵ
	if( m_Vector != v )
	{
		m_Vector = v;
	}
}