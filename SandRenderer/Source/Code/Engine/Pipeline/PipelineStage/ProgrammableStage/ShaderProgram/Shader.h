#ifndef Shader_h
#define Shader_h

#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Reflection/ShaderReflection.h"

namespace Sand
{
	class Shader
	{
	public:
		Shader();
		virtual ~Shader();

		virtual ShaderType GetType() = 0;

		std::wstring GetShaderFileName();
		std::wstring GetFunctionName();
		std::wstring GetShaderModelName();
		std::string GetShaderTex();
		ID3DBlob* GetCompiledShader();
		ShaderReflection* GetShaderReflection();

		void SetShaderFileName( std::wstring& FileName );
		void SetShaderFunctionName( std::wstring& Function );
		void SetShaderModelName( std::wstring& Model );
		void SetShaderTex( std::string ShaderTex );
		void SetCompiledShader( ID3DBlob* pCompiledShader );
		void SetShaderReflection( ShaderReflection* pShaderReflection );

	private:
		std::wstring		m_FileName;
		std::wstring		m_FunctionName;
		std::wstring		m_ShaderModelName;
		std::string			m_ShaderText;
		ID3DBlob*			m_pCompiledShader;
		ShaderReflection*	m_ShaderReflection;
	};
};
#endif