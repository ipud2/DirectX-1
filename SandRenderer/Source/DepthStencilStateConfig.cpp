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
	DepthFunc = D3D11_COMPARISON_LESS;	// ��Ȳ��Ժ���

	// Ĭ�ϲ�����ģ�����
	StencilEnable = FALSE;
	StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	// ģ����Ժ���
	FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// ģ����Ժ���Ȳ��Զ�ͨ����ģ�建��Ӧ����θ���
	FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	// ģ�����ʧ�ܣ�ģ�建����θ���
	FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	// ģ�����ͨ������Ȳ���ʧ�ܣ�ģ�建�����θ���
	FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
}