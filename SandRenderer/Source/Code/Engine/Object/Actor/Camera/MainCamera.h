#ifndef	MainCamera_h
#define MainCamera_h

#include "Engine/Object/Actor/Camera/BaseCamera.h"
#include "Engine/Parameter/ParameterContainer.h"

namespace Sand
{
	class Scene;

	class MainCamera : public BaseCamera
	{
	public:
		MainCamera();
		virtual ~MainCamera();

		virtual void RenderFrame( Renderer* pRenderer );

	public:
		void SetPerspectiveProjectionParams( float Near , float Far , float Aspect , float Fov );

		void SetClipPlane( float Near , float Far );
		void SetAspect( float Aspect );
		void SetFieldOfView( float Fov );
		
		float GetNearClipPlane();
		float GetFarClipPlane();
		float GetAspect();
		float GetFieldOfView();

	protected:
		// 将透视投影矩阵作为场景的投影矩阵
		void ApplyPerspectiveProjectionParams();

	protected:
		float m_fNear;
		float m_fFar;
		float m_fAspect;
		float m_fFov;
		float m_fWidth;
		float m_fHeight;
	};
};
#endif