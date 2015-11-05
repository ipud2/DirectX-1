#include "BlendStateConfig.h"

using namespace Sand;

BlendStateConfig::BlendStateConfig()
{
	SetDefault();
}

BlendStateConfig::~BlendStateConfig()
{

}

void BlendStateConfig::SetDefault()
{
	AlphaToCoverageEnable = false;

	// 该参数为false，则所有的render target使用RenderTarget[0]进行混合
	IndependentBlendEnable = false;

	// color = color_src * SrcBlend BlendOp color_dest * .DestBlend
	// alpha = a_src * SrcBlendAlpha BlendOpAlpha a_dest * DestBlendAlpha
	for( int i = 0; i < 8; i++ )
	{
		RenderTarget[i].BlendEnable = false;

		RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		RenderTarget[i].DestBlend = D3D11_BLEND_ZERO;
		RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;

		RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
		RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
}