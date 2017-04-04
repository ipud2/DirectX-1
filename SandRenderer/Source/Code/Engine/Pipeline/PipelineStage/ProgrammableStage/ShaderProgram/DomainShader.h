#ifndef DomainShader_h
#define DomainShader_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Shader.h"

namespace Sand
{
	class DomainShader : public Shader
	{
	public:
		DomainShader( ID3D11DomainShader* pShader );
		virtual ~DomainShader();

		virtual ShaderType GetType();

	protected:
		ID3D11DomainShader* m_pDomainShader;

		friend class DomainStage;

	};
};
#endif