#ifndef SamplerStateConfig_h
#define SamplerStateConfig_h

#include "PCH.h"

namespace Sand
{
	class Renderer;

	class SamplerStateConfig : public D3D11_SAMPLER_DESC
	{
	public:
		SamplerStateConfig();
		~SamplerStateConfig();

	private:
		void SetDefault();

		friend Renderer;
	};
};
#endif