#include <Engine/PCH.h>
#include "SwapChain.h"

using namespace Sand;

SwapChain::SwapChain( Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain , ResourceProxyPtr pResourceProxy )
{
	m_SwapChain = pSwapChain;

	m_ResourceProxy = pResourceProxy;
}

SwapChain::~SwapChain()
{

}

IDXGISwapChain* SwapChain::GetResoruce()
{
	return m_SwapChain.Get();
}