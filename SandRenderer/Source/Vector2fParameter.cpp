#include "PCH.h"
#include "Vector2fParameter.h"

using namespace Sand;

Vector2fParameter::Vector2fParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// ����
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
	// ���ֽڱȽ������Ƿ���һ����
	if ( 0 != memcmp( pData , &m_Vector , sizeof( Vector2f ) ) )
	{
		// ��0��ʾ�ǲ�һ��������
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
	// ����һ�£�������Ϊ�µ�ֵ
	if ( m_Vector != v )
	{
		m_Vector = v;
	}
}