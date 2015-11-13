#include "PCH.h"
#include "HullShader.h"

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