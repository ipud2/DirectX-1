#ifndef SampleStateConfig_h
#define SampleStateConfig_h

#include "PCH.h"

namespace Sand
{
	class Renderer;

	class SampleStateConfig : public D3D11_SAMPLER_DESC
	{
	public:
		SampleStateConfig();
		~SampleStateConfig();

	private:
		void SetDefault();

		friend Renderer;
	};
}

#endif