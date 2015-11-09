#include "PCH.h"
#include "ShaderResourceParameter.h"

using namespace Sand;

ShaderResourceParameter::ShaderResourceParameter()
{
	m_iShaderResourceID = -1;
}

ShaderResourceParameter::ShaderResourceParameter( ShaderResourceParameter& copy )
{
	m_iShaderResourceID = copy.m_iShaderResourceID;
}

ShaderResourceParameter::~ShaderResourceParameter()
{

}

void ShaderResourceParameter::SetParameter( void * pData )
{
	// 检测数据是否一致
	if( 0 != memcmp( pData , &m_iShaderResourceID , sizeof( int ) ) )
	{
		// 不一致
		m_iShaderResourceID = *reinterpret_cast< int* >( pData );
	}
}

const ParameterType ShaderResourceParameter::GetParameterType()
{
	return PT_SHADER_RESOURCE;
}

int ShaderResourceParameter::GetValue()
{
	return m_iShaderResourceID;
}