#include "PCH.h"
#include "Vector3fParameter.h"

using namespace Sand;

Vector3fParameter::Vector3fParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// ����
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
	// ���ֽڱȽ������Ƿ���һ����
	if ( 0 != memcmp( pData , &m_Vector , sizeof( Vector3f ) ) )
	{
		// ��0��ʾ�ǲ�һ��������
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
	// ����һ�£�������Ϊ�µ�ֵ
	if ( m_Vector != v )
	{
		m_Vector = v;
	}
}