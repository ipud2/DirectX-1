#include "UnorderedAccessView.h"

using namespace Sand;

UnorderedAccessView::UnorderedAccessView( ID3D11UnorderedAccessView* pUnorderedAccessView )
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