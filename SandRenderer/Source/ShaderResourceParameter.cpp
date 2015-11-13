#include "PCH.h"
#include "ShaderResourceParameter.h"

using namespace Sand;

ShaderResourceParameter::ShaderResourceParameter( std::wstring name )
	:RenderParameter( name )
{
	m_iShaderResourceID = -1;
}

ShaderResourceParameter::ShaderResourceParameter( ShaderResourceParameter& copy )
	: RenderParameter( copy )
{
	m_iShaderResourceID = copy.m_iShaderResourceID;
}

ShaderResourceParameter::~ShaderResourceParameter()
{

}

void ShaderResourceParameter::SetParameterData( void * pData )
{
	// ��������Ƿ�һ��
	if( 0 != memcmp( pData , &m_iShaderResourceID , sizeof( int ) ) )
	{
		// ��һ��
		m_iShaderResourceID = *reinterpret_cast< int* >( pData );
	}
}

const ParameterType ShaderResourceParameter::GetParameterType()
{
	return PT_SHADER_RESOURCE;
}

int ShaderResourceParameter::GetResourceViewID()
{
	return m_iShaderResourceID;
}