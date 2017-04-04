#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/HullShader.h"

using namespace Sand;

HullShader::HullShader( ID3D11HullShader* pShader )
{
	m_pHullShader = pShader;
}

HullShader::~HullShader()
{

}

ShaderType HullShader::GetType()
{
	return ST_HULL_SHADER;
}