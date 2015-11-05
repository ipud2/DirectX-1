#include "PCH.h"
#include "RasterizerStateConfig.h"

using namespace Sand;

RasterizerStateConfig::RasterizerStateConfig()
{
	SetDefaults();
}

RasterizerStateConfig::~RasterizerStateConfig()
{
	
}

void RasterizerStateConfig::SetDefaults()
{
	// 设置默认配置
	FillMode = D3D11_FILL_SOLID;		// 实体绘制
	CullMode = D3D11_CULL_BACK;			// 剔除背面
	FrontCounterClockwise = false;		// 绕序为顺时针的为前面
	DepthBias = 0;
	SlopeScaledDepthBias = 0.0f;
	DepthBiasClamp = 0.0f;
	DepthClipEnable = false;
	ScissorEnable = false;
	MultisampleEnable = false;
	AntialiasedLineEnable = false;
}