#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Object/ShaderResourceParameter.h"

using namespace Sand;

ShaderResourceParameter::ShaderResourceParameter( std::wstring name )
	:RenderParameter( name )
{
	// 默认视图对象
	m_iShaderResourceID = 0;
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

int ShaderResourceParameter::GetResourceViewID()
{
	return m_iShaderResourceID;
}