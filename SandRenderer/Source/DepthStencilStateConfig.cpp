#include "PCH.h"
#include "DepthStencilStateConfig.h"

using namespace Sand;

DepthStencilStateConfig::DepthStencilStateConfig()
{
	SetDefault();
}

DepthStencilStateConfig::~DepthStencilStateConfig()
{

}

void DepthStencilStateConfig::SetDefault()
{
	DepthEnable = true;

	DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthFunc = D3D11_COMPARISON_LESS;	// 深度测试函数

	// 默认不启用模板测试
	StencilEnable = FALSE;
	StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	// 模板测试函数
	FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// 模板测试和深度测试都通过，模板缓存应该如何更新
	FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	// 模板测试失败，模板缓存如何更新
	FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	// 模板测试通过，深度测试失败，模板缓存该如何更新
	FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
}