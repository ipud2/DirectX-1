#include "PCH.h"
#include "Shader.h"

using namespace Sand;

Shader::Shader()
{

}

Shader::~Shader()
{

}

ShaderReflection* Shader::GetShaderReflection()
{
	return m_ShaderReflection;
}

std::wstring Shader::GetShaderFileName()
{
	return m_FileName;
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

void Shader::SetShaderFileName( std::wstring& FileName )
{
	m_FileName = FileName;
}

void Shader::SetShaderFunctionName( std::wstring& Function )
{
	m_FunctionName = Function;
}

void Shader::SetShaderModelName( std::wstring& Model )
{
	m_ShaderModelName = Model;
}

void Shader::SetShaderTex( std::string ShaderTex )
{
	m_ShaderText = ShaderTex;
}

void Shader::SetCompiledShader( ID3DBlob* pCompiledShader )
{
	m_pCompiledShader = pCompiledShader;
}

void Shader::SetShaderReflection( ShaderReflection* pShaderReflection )
{
	m_ShaderReflection = pShaderReflection;
}