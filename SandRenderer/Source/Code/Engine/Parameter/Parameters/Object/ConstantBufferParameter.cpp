#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Object/ConstantBufferParameter.h"

using namespace Sand;

ConstantBufferParameter::ConstantBufferParameter( std::wstring name )
	:RenderParameter( name )
{
	m_iConstantBufferID = -1;
}

ConstantBufferParameter::ConstantBufferParameter( ConstantBufferParameter& copy )
	: RenderParameter( copy )
{
	m_iConstantBufferID = copy.m_iConstantBufferID;
}

ConstantBufferParameter::~ConstantBufferParameter()
{

}

void ConstantBufferParameter::SetParameterData( void * pData )
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

int ConstantBufferParameter::GetResourceID()
{
	return m_iConstantBufferID;
}