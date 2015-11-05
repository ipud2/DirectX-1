#include "PCH.h"
#include "RenderTargetView.h"
#include "Renderer.h"

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