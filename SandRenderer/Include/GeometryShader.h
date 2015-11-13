#ifndef GeometryShader_h
#define GeometryShader_h

#include "Shader.h"

namespace Sand
{
	class GeometryShader : public Shader
	{
	public:
		GeometryShader( ID3D11GeometryShader* pShader );
		virtual ~GeometryShader();

		virtual ShaderType GetType();

	protected:
		ID3D11GeometryShader* m_pGeometryShader;

		friend class GeometryStage;

	};
};
#endif