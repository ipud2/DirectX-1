#include "PCH.h"
#include "UnorderedAccessViewConfig.h"

using namespace Sand;

UnorderedAccessViewConfig::UnorderedAccessViewConfig()
{
	SetDefaults();
}

UnorderedAccessViewConfig::~UnorderedAccessViewConfig()
{

}

void UnorderedAccessViewConfig::SetDefaults()
{
	m_State.Format = DXGI_FORMAT_UNKNOWN;
	m_State.ViewDimension = D3D11_UAV_DIMENSION_UNKNOWN;
}

void UnorderedAccessViewConfig::SetFormat( DXGI_FORMAT Format )
{
	m_State.Format = Format;
}

void UnorderedAccessViewConfig::SetViewDimension( D3D11_UAV_DIMENSION ViewDimension )
{
	m_State.ViewDimension = ViewDimension;
}

void UnorderedAccessViewConfig::SetTexture1D( D3D11_TEX1D_UAV Texture1D )
{
	m_State.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
	m_State.Texture1D = Texture1D;
}

void UnorderedAccessViewConfig::SetTexture1DArray( D3D11_TEX1D_ARRAY_UAV Texture1DArray )
{
	m_State.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
	m_State.Texture1DArray = Texture1DArray;
}

void UnorderedAccessViewConfig::SetTexture2D( D3D11_TEX2D_UAV Texture2D )
{
	m_State.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	m_State.Texture2D = Texture2D;
}

void UnorderedAccessViewConfig::SetTexture2DArray( D3D11_TEX2D_ARRAY_UAV Texture2DArray )
{
	m_State.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
	m_State.Texture2DArray = Texture2DArray;
}

void UnorderedAccessViewConfig::SetTexture3D( D3D11_TEX3D_UAV Texture3D )
{
	m_State.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
	m_State.Texture3D = Texture3D;
}

D3D11_UNORDERED_ACCESS_VIEW_DESC& UnorderedAccessViewConfig::GetDesc()
{
	return m_State;
}