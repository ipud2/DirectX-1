#include "PCH.h"
#include "GeometryShader.h"

using namespace Sand;

GeometryShader::GeometryShader( ID3D11GeometryShader* pShader )
{
	m_pGeometryShader = pShader;
}

GeometryShader::~GeometryShader()
{

}

ShaderType GeometryShader::GetType()
{
	return ST_GEOMETRY_SHADER;
}