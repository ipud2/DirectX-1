#include "PCH.h"
#include "ConstantBufferParameter.h"

using namespace Sand;

ConstantBufferParameter::ConstantBufferParameter()
{
	m_iConstantBufferID = -1;
}

ConstantBufferParameter::ConstantBufferParameter( ConstantBufferParameter& copy )
{
	m_iConstantBufferID = copy.m_iConstantBufferID;
}

ConstantBufferParameter::~ConstantBufferParameter()
{

}

void ConstantBufferParameter::SetParameter( void * pData )
{
	// ��������Ƿ����仯
	if( 0 != memcmp( pData , &m_iConstantBufferID , sizeof( int ) ) )
	{
		// ��һ��
		m_iConstantBufferID = *reinterpret_cast< int* >( pData );
	}
}

const ParameterType ConstantBufferParameter::GetParameterType()
{
	return PT_CONSTANT_BUFFER;
}

int ConstantBufferParameter::GetValue()
{
	return m_iConstantBufferID;
}