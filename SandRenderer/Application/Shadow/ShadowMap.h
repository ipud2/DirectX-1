#ifndef ShadowMap_h
#define ShadowMap_h

#include "ResourceProxy.h"

namespace Sand
{
	class ShadowMap
	{
	public:
		ShadowMap( Renderer* pRenderer , float Width , float Height );
		~ShadowMap();

		ResourceProxyPtr GetShadowMap();

	protected:
		ResourceProxyPtr m_pShadowMap;
	};
};
#endif