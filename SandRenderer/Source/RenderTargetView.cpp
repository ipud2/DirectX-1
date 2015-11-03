#include "RenderTargetView.h"
#include "Renderer.h"

using namespace Sand;

RenderTargetView::RenderTargetView( ID3D11RenderTargetView* pRenderTargetView )
{
	m_RenderTargetView = pRenderTargetView;
}

RenderTargetView::~RenderTargetView()
{

}

ID3D11RenderTargetView* RenderTargetView::Get()
{
	return m_RenderTargetView.Get();
}