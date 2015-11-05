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
	// ����Ĭ������
	FillMode = D3D11_FILL_SOLID;		// ʵ�����
	CullMode = D3D11_CULL_BACK;			// �޳�����
	FrontCounterClockwise = false;		// ����Ϊ˳ʱ���Ϊǰ��
	DepthBias = 0;
	SlopeScaledDepthBias = 0.0f;
	DepthBiasClamp = 0.0f;
	DepthClipEnable = false;
	ScissorEnable = false;
	MultisampleEnable = false;
	AntialiasedLineEnable = false;
}