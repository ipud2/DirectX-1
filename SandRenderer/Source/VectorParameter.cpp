#include "PCH.h"
#include "VectorParameter.h"

using namespace Sand;

VectorParameter::VectorParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	// ����
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
	// ���ֽڱȽ������Ƿ���һ����
	if( 0 != memcmp( pData , &m_Vector , sizeof( Vector4f ) ) )
	{
		// ��0��ʾ�ǲ�һ��������
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
	// ����һ�£�������Ϊ�µ�ֵ
	if( m_Vector != v )
	{
		m_Vector = v;
	}
}