#ifndef ShaderFactory_h
#define ShaderFactory_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Shader.h"

namespace Sand
{
	class ShaderFactory
	{
	public:
		~ShaderFactory();

		static ID3DBlob* GenerateShader( ShaderType type , std::wstring& Filename , std::wstring& Function , std::wstring& Model , const D3D_SHADER_MACRO* pDefines , bool EnableLogging = true );

	private:
		ShaderFactory();
	};
};
#endif