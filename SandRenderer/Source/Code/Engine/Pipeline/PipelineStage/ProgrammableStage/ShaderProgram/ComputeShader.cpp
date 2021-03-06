#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/ComputeShader.h"

using namespace Sand;

ComputeShader::ComputeShader( ID3D11ComputeShader* pShader )
{
	m_pComputeShader = pShader;
}

ComputeShader::~ComputeShader()
{

}

ShaderType ComputeShader::GetType()
{
	return ST_COMPUTE_SHADER;
}