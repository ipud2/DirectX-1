#ifndef DepthStencilConfig_h
#define DepthStencilConfig_h

#include "PCH.h"

namespace Sand
{
	class Renderer;

	class DepthStencilStateConfig : public D3D11_DEPTH_STENCIL_DESC
	{
	public:
		DepthStencilStateConfig();
		~DepthStencilStateConfig();

	private:
		void SetDefault();

	protected:
		friend Renderer;
	};
}

#endif