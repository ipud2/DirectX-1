#ifndef ShadowMapCamera_h
#define ShadowMapCamera_h

#include "BaseCamera.h"

namespace Sand
{
	class Scene;

	class ShadowMapCamera : public BaseCamera
	{
	public:
		ShadowMapCamera();
		virtual ~ShadowMapCamera();

		virtual void RenderFrame( Renderer* pRenderer );

	public:
		void SetBoundSphereRadius( float Radius );

		void SetOrthographicParams( const Vector3f& SphereCenter );

	public:
		Matrix4f GetShadowTransformMatrix() const;

	protected:
		float m_Radius;
		MatrixParameterWriter* m_pShadowTransformWriter;
	};
};
#endif