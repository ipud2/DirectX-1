#include "PCH.h"
#include "ShadowMap.h"
#include "Renderer.h"
#include "Texture2DConfig.h"
#include "ShaderResourceViewConfig.h"
#include "DepthStencilViewConfig.h"

using namespace Sand;

ShadowMap::ShadowMap( Renderer* pRenderer , float Width , float Height )
{
	Texture2DConfig ShadowMapConfigure;
	ShadowMapConfigure.SetBindFlags( D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL );
	ShadowMapConfigure.SetWidth( Width );
	ShadowMapConfigure.SetHeight( Height );
	ShadowMapConfigure.SetFormat( DXGI_FORMAT_R24G8_TYPELESS );

	ShaderResourceViewConfig ShaderResourceViewConfigure;
	ShaderResourceViewConfigure.SetFormat( DXGI_FORMAT_R24_UNORM_X8_TYPELESS );
	ShaderResourceViewConfigure.SetViewDimension( D3D11_SRV_DIMENSION_TEXTURE2D );
	ShaderResourceViewConfigure.GetTexture2DRef().MipLevels = ShadowMapConfigure.GetMipLevels();
	ShaderResourceViewConfigure.GetTexture2DRef().MostDetailedMip = 0;

	DepthStencilViewConfig DepthStencilViewConfigure;
	DepthStencilViewConfigure.SetFlags( 0 );
	DepthStencilViewConfigure.SetFormat( DXGI_FORMAT_D24_UNORM_S8_UINT );
	DepthStencilViewConfigure.SetViewDimensions( D3D11_DSV_DIMENSION_TEXTURE2D );
	DepthStencilViewConfigure.GetTexture2DRef().MipSlice = 0;

	m_pShadowMap = pRenderer->CreateTexture2D( &ShadowMapConfigure , nullptr , &ShaderResourceViewConfigure , nullptr , nullptr , &DepthStencilViewConfigure );
}

ShadowMap::~ShadowMap()
{

}

ResourceProxyPtr ShadowMap::GetShadowMap()
{
	return m_pShadowMap;
}