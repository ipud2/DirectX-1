#ifndef VertexShader_h
#define VertexShader_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Shader.h"

namespace Sand
{
	class VertexShader : public Shader
	{
	public:
		VertexShader( ID3D11VertexShader* pShader );
		virtual ~VertexShader();

		virtual ShaderType GetType();

	protected:
		ID3D11VertexShader* m_pVertexShader;

		friend class VertexStage;

	};
};
#endif