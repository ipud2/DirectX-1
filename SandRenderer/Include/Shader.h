#ifndef Shader_h
#define Shader_h

#include "PCH.h"
#include "ShaderReflection.h"

namespace Sand
{
	class Shader
	{
	public:
		Shader();
		virtual ~Shader();

		virtual ShaderType GetType() = 0;

		void SetShaderReflection( ShaderReflection* pShaderReflection );
		ShaderReflection* GetShaderReflection();

		std::wstring GetShaderFileName();
		std::wstring GetFunctionName();
		std::wstring GetShaderModelName();
		std::string GetShaderTex();
		ID3DBlob* GetCompiledShader();
		ShaderReflection* GetShaderReflection();

	private:
		std::wstring		m_Name;
		std::wstring		m_FunctionName;
		std::wstring		m_ShaderModelName;
		std::string			m_ShaderText;
		ID3DBlob*			m_pCompiledShader;
		ShaderReflection*	m_ShaderReflection;
	};
};
#endif