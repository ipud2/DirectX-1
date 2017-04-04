#include <Engine/PCH.h>
#include "Engine/Resource/ResourceView/DepthStencilViewConfig.h"

using namespace Sand;

DepthStencilViewConfig::DepthStencilViewConfig()
{
	SetDefaults();
}

DepthStencilViewConfig::~DepthStencilViewConfig()
{

}

void DepthStencilViewConfig::SetDefaults()
{
	m_State.Format = DXGI_FORMAT_UNKNOWN;
	m_State.Flags = 0;

	m_State.ViewDimension = D3D11_DSV_DIMENSION_UNKNOWN;
}

void DepthStencilViewConfig::SetFormat( DXGI_FORMAT Format )
{
	m_State.Format = Format;
}

void DepthStencilViewConfig::SetFlags( UINT state )
{
	m_State.Flags = state;
}

void DepthStencilViewConfig::SetViewDimensions( D3D11_DSV_DIMENSION state )
{
	m_State.ViewDimension = state;
}

void DepthStencilViewConfig::SetTexture1D( D3D11_TEX1D_DSV Texture1D )
{
	m_State.Texture1D = Texture1D;
}

void DepthStencilViewConfig::SetTexture1DArray( D3D11_TEX1D_ARRAY_DSV Texture1DArray )
{
	m_State.Texture1DArray = Texture1DArray;
}

void DepthStencilViewConfig::SetTexture2D( D3D11_TEX2D_DSV Texture2D )
{
	m_State.Texture2D = Texture2D;
}

void DepthStencilViewConfig::SetTexture2DArray( D3D11_TEX2D_ARRAY_DSV Texture2DArray )
{
	m_State.Texture2DArray = Texture2DArray;
}

void DepthStencilViewConfig::SetTexture2DMS( D3D11_TEX2DMS_DSV Texture2DMS )
{
	m_State.Texture2DMS = Texture2DMS;
}

void DepthStencilViewConfig::SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray )
{
	m_State.Texture2DMSArray = Texture2DMSArray;
}

D3D11_DEPTH_STENCIL_VIEW_DESC& DepthStencilViewConfig::GetDesc()
{
	return m_State;
}

D3D11_TEX1D_DSV& DepthStencilViewConfig::GetTexture1DRef()
{
	return m_State.Texture1D;
}

D3D11_TEX1D_ARRAY_DSV& DepthStencilViewConfig::GetTexture1DArrayRef()
{
	return m_State.Texture1DArray;
}

D3D11_TEX2D_DSV& DepthStencilViewConfig::GetTexture2DRef()
{
	return m_State.Texture2D;
}

D3D11_TEX2D_ARRAY_DSV& DepthStencilViewConfig::GetTexture2DArrayRef()
{
	return m_State.Texture2DArray;
}

D3D11_TEX2DMS_DSV& DepthStencilViewConfig::GetTexture2DMSRef()
{
	return m_State.Texture2DMS;
}

D3D11_TEX2DMS_ARRAY_DSV& DepthStencilViewConfig::GetTexture2DMSArray()
{
	return m_State.Texture2DMSArray;
}