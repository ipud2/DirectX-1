#include "PCH.h"
#include "DepthStencilView.h"

using namespace Sand;

DepthStencilView::DepthStencilView( Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView )
{
	m_DepthStencilView = pDepthStencilView;
}

DepthStencilView::~DepthStencilView()
{

}

ID3D11DepthStencilView* DepthStencilView::Get()
{
	return m_DepthStencilView.Get();
}