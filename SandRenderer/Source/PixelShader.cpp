#include "PCH.h"
#include "PixelShader.h"

using namespace Sand;

PixelShader::PixelShader( ID3D11PixelShader* pShader )
{
	m_pPixelShader = pShader;
}

PixelShader::~PixelShader()
{

}

ShaderType PixelShader::GetType()
{
	return ST_PIXEL_SHADER;
}