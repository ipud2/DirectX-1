#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/DomainShader.h"

using namespace Sand;

DomainShader::DomainShader( ID3D11DomainShader* pShader )
{
	m_pDomainShader = pShader;
}

DomainShader::~DomainShader()
{

}

ShaderType DomainShader::GetType()
{
	return ST_DOMAIN_SHADER;
}