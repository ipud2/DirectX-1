#ifndef RasterizerStateConfig_h
#define RasterizerStateConfig_h

#include <Engine/PCH.h>

namespace Sand
{
	class Renderer;

	class RasterizerStateConfig : public D3D11_RASTERIZER_DESC
	{
	public:
		RasterizerStateConfig();
		~RasterizerStateConfig();

	private:
		void SetDefaults();

	protected:
		friend Renderer;
	};
}

#endif