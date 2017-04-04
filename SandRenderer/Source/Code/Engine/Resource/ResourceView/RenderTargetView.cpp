#include <Engine/PCH.h>
#include "Engine/Resource/ResourceView/RenderTargetView.h"
#include "Engine/Render/DXGI/Renderer.h"

using namespace Sand;

RenderTargetView::RenderTargetView( Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView )
{
	m_RenderTargetView = pRenderTargetView;
}

RenderTargetView::~RenderTargetView()
{

}

ID3D11RenderTargetView* RenderTargetView::GetRenderTargetView()
{
	return m_RenderTargetView.Get();
}