#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/VertexShader.h"

using namespace Sand;

VertexShader::VertexShader( ID3D11VertexShader* pShader )
{
	m_pVertexShader = pShader;
}

VertexShader::~VertexShader()
{

}

ShaderType VertexShader::GetType()
{
	return ST_VERTEX_SHADER;
}