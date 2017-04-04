#ifndef ComputeShader_h
#define ComputeShader_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Shader.h"

namespace Sand
{
	class ComputeShader : public Shader
	{
	public:
		ComputeShader( ID3D11ComputeShader* pShader );
		virtual ~ComputeShader();

		virtual ShaderType GetType();

	protected:
		ID3D11ComputeShader* m_pComputeShader;

		friend class ComputeStage;

	};
};
#endif