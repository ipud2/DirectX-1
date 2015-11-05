#include "PCH.h"
#include "RenderTargetViewConfig.h"

using namespace Sand;


RenderTargetViewConfig::RenderTargetViewConfig()
{
	SetDefaults();
}

RenderTargetViewConfig::~RenderTargetViewConfig()
{

}

void RenderTargetViewConfig::SetDefaults()
{
	m_State.Format = DXGI_FORMAT_UNKNOWN;
	m_State.ViewDimension = D3D11_RTV_DIMENSION_UNKNOWN;
}

void RenderTargetViewConfig::SetFormat( DXGI_FORMAT Format )
{
	m_State.Format = Format;
}

void RenderTargetViewConfig::SetViewDimension( D3D11_RTV_DIMENSION ViewDimension )
{
	m_State.ViewDimension = ViewDimension;
}

void RenderTargetViewConfig::SetBuffer( D3D11_BUFFER_RTV Buffer )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_BUFFER;
	m_State.Buffer = Buffer;
}

void RenderTargetViewConfig::SetTexture1D( D3D11_TEX1D_RTV Texture1D )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
	m_State.Texture1D = Texture1D;
}

void RenderTargetViewConfig::SetTexture1DArray( D3D11_TEX1D_ARRAY_RTV Texture1DArray )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
	m_State.Texture1DArray = Texture1DArray;
}

void RenderTargetViewConfig::SetTexture2D( D3D11_TEX2D_RTV Texture2D )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	m_State.Texture2D = Texture2D;
}

void RenderTargetViewConfig::SetTexture2DArray( D3D11_TEX2D_ARRAY_RTV Texture2DArray )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	m_State.Texture2DArray = Texture2DArray;
}

void RenderTargetViewConfig::SetTexture2DMS( D3D11_TEX2DMS_RTV Texture2DMS )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	m_State.Texture2DMS = Texture2DMS;
}

void RenderTargetViewConfig::SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
	m_State.Texture2DMSArray = Texture2DMSArray;
}

void RenderTargetViewConfig::SetTexture3D( D3D11_TEX3D_RTV Texture3D )
{
	m_State.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
	m_State.Texture3D = Texture3D;
}

D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewConfig::GetDesc()
{
	return m_State;
}
