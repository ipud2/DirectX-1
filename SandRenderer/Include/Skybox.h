#ifndef Skybox_h
#define Skybox_h

#include "Actor.h"
#include "Geometry.h"

namespace Sand
{
	class Skybox : public Actor
	{
	public:
		Skybox( std::wstring& filename , int sampler , float Radius = 1000.0f );
		virtual ~Skybox();

	protected:
		Entity* m_pSkybox;
		GeometryPtr m_pGeometry;
		EffectPtr m_pShaderEffect;
		int m_iSamplerState;
		float m_Radius;
	};
}
#endif