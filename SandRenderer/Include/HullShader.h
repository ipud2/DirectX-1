#ifndef HullShader_h
#define HullShader_h

#include "Shader.h"

namespace Sand
{
	class HullShader : public Shader
	{
	public:
		HullShader( ID3D11HullShader* pShader );
		virtual ~HullShader();

		virtual ShaderType GetType();

	protected:
		ID3D11HullShader* m_pHullShader;

		friend class HullStage;

	};
};
#endif