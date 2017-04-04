#ifndef SwapChain_h
#define SwapChain_h

#include "Engine/Resource/ResourceProxy.h"
#include <Engine/PCH.h>

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