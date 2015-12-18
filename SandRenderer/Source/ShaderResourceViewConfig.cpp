#include "PCH.h"
#include "ShaderResourceViewConfig.h"

using namespace Sand;

ShaderResourceViewConfig::ShaderResourceViewConfig()
{
	SetDefaults();
}

ShaderResourceViewConfig::~ShaderResourceViewConfig()
{

}

void ShaderResourceViewConfig::SetDefaults()
{
	m_State.Format = DXGI_FORMAT_UNKNOWN;
	m_State.ViewDimension = D3D11_SRV_DIMENSION_UNKNOWN;
}

void ShaderResourceViewConfig::SetFormat( DXGI_FORMAT Format )
{
	m_State.Format = Format;
}

void ShaderResourceViewConfig::SetTexture1D( D3D11_TEX1D_SRV Texture1D )
{
	m_State.Texture1D = Texture1D;
}

void ShaderResourceViewConfig::SetTexture1DArray( D3D11_TEX1D_ARRAY_SRV Texture1DArray )
{
	m_State.Texture1DArray = Texture1DArray;
}

void ShaderResourceViewConfig::SetTexture2D( D3D11_TEX2D_SRV Texture2D )
{
	m_State.Texture2D = Texture2D;
}

void ShaderResourceViewConfig::SetTexture2DArray( D3D11_TEX2D_ARRAY_SRV Texture2DArray )
{
	m_State.Texture2DArray = Texture2DArray;
}

void ShaderResourceViewConfig::SetTexture2DMS( D3D11_TEX2DMS_SRV Texture2DMS )
{
	m_State.Texture2DMS = Texture2DMS;
}

void ShaderResourceViewConfig::SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_SRV Texture2DMSArray )
{
	m_State.Texture2DMSArray = Texture2DMSArray;
}

void ShaderResourceViewConfig::SetTexture3D( D3D11_TEX3D_SRV Texture3D )
{
	m_State.Texture3D = Texture3D;
}

void ShaderResourceViewConfig::SetTextureCube( D3D11_TEXCUBE_SRV TextureCbue )
{
	m_State.TextureCube = TextureCbue;
}

void ShaderResourceViewConfig::SetTextureCubeArray( D3D11_TEXCUBE_ARRAY_SRV TextureCubeArray )
{
	m_State.TextureCubeArray = TextureCubeArray;
}

void ShaderResourceViewConfig::SetBufferEx( D3D11_BUFFEREX_SRV BufferEx )
{
	m_State.BufferEx = BufferEx;
}

D3D11_SHADER_RESOURCE_VIEW_DESC& ShaderResourceViewConfig::GetDesc()
{
	return m_State;
}

void ShaderResourceViewConfig::SetViewDimension( D3D11_SRV_DIMENSION ViewDimension )
{
	m_State.ViewDimension = ViewDimension;
}

void ShaderResourceViewConfig::SetBuffer( D3D11_BUFFER_SRV Buffer )
{
	m_State.Buffer = Buffer;
}

D3D11_BUFFER_SRV& ShaderResourceViewConfig::GetBufferRef()
{
	return m_State.Buffer;
}

D3D11_TEX1D_SRV& ShaderResourceViewConfig::GetTexture1DRef()
{
	return m_State.Texture1D;
}

D3D11_TEX1D_ARRAY_SRV& ShaderResourceViewConfig::GetTexture1DArrayRef()
{
	return m_State.Texture1DArray;
}

D3D11_TEX2D_SRV& ShaderResourceViewConfig::GetTexture2DRef()
{
	return m_State.Texture2D;
}

D3D11_TEX2D_ARRAY_SRV& ShaderResourceViewConfig::GetTexture2DArrayRef()
{
	return m_State.Texture2DArray;
}

D3D11_TEX2DMS_SRV& ShaderResourceViewConfig::GetTexture2DMSRef()
{
	return m_State.Texture2DMS;
}

D3D11_TEX2DMS_ARRAY_SRV& ShaderResourceViewConfig::GetTexture2DMSArrayRef()
{
	return m_State.Texture2DMSArray;
}

D3D11_TEX3D_SRV& ShaderResourceViewConfig::GetTexture3DRef()
{
	return m_State.Texture3D;
}

D3D11_TEXCUBE_SRV& ShaderResourceViewConfig::GetTextureCubRefe()
{
	return m_State.TextureCube;
}

D3D11_TEXCUBE_ARRAY_SRV& ShaderResourceViewConfig::GetTextureCubeArrayRef()
{
	return m_State.TextureCubeArray;
}

D3D11_BUFFEREX_SRV& ShaderResourceViewConfig::GetBufferExRef()
{
	return m_State.BufferEx;
}
