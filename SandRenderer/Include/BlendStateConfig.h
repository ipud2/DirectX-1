#ifndef BlendStateConfig_h
#define BlendStateConfig_h

#include "PCH.h"

namespace Sand
{
	class Renderer;

	class BlendStateConfig : public D3D11_BLEND_DESC
	{
	public:
		BlendStateConfig();
		~BlendStateConfig();

	private:
		void SetDefault();

	protected:
		friend Renderer;
	};
}

#endif