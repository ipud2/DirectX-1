#ifndef SwapChain_h
#define SwapChain_h

#include "ResourceProxy.h"
#include "PCH.h"

namespace Sand
{
	class SwapChain
	{
	public:
		SwapChain( Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain , ResourceProxyPtr pResourceProxy );
		virtual ~SwapChain();

		IDXGISwapChain* GetResoruce();

	protected:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		ResourceProxyPtr m_ResourceProxy;

		friend class Renderer;
	};
}

#endif