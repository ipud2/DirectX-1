#include <Engine/PCH.h>
#include "Engine/Resource/ResourceView/UnorderedAccessView.h"

using namespace Sand;

UnorderedAccessView::UnorderedAccessView( Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> pUnorderedAccessView )
{
	m_UnorderedAccessView = pUnorderedAccessView;
}

UnorderedAccessView::~UnorderedAccessView()
{

}

ID3D11UnorderedAccessView* UnorderedAccessView::Get()
{
	return m_UnorderedAccessView.Get();
}