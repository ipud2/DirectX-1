#ifndef PixelShader_h
#define PixelShader_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Shader.h"

namespace Sand
{
	class PixelShader : public Shader
	{
	public:
		PixelShader( ID3D11PixelShader* pShader );
		virtual ~PixelShader();

		virtual ShaderType GetType();

	protected:
		ID3D11PixelShader* m_pPixelShader;

		friend class PixelStage;

	};
};
#endif