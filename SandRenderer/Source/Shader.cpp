#include "PCH.h"
#include "Shader.h"

using namespace Sand;

Shader::Shader()
{

}

Shader::~Shader()
{

}

void Shader::SetShaderReflection( ShaderReflection* pShaderReflection )
{
	m_ShaderReflection = pShaderReflection;
}

ShaderReflection* Shader::GetShaderReflection()
{
	return m_ShaderReflection;
}

std::wstring Shader::GetShaderFileName()
{
	return m_Name;
}

std::wstring Shader::GetFunctionName()
{
	return m_FunctionName;
}

std::wstring Shader::GetShaderModelName()
{
	return m_ShaderModelName;
}

std::string Shader::GetShaderTex()
{
	return m_ShaderText;
}

ID3DBlob* Shader::GetCompiledShader()
{
	return m_pCompiledShader;
}

ShaderReflection* Shader::GetShaderReflection()
{
	return m_ShaderReflection;
}