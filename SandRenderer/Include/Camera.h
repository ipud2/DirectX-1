#ifndef Camera_h
#define Camera_h

#include "Actor.h"
#include "SceneRenderTask.h"
#include "SpatialController.h"
#include "ParameterContainer.h"

namespace Sand
{
	class Scene;

	class Camera : public Actor
	{
	public:
		Camera();
		virtual ~Camera();

	public:
		SceneRenderTask* GetRenderView();
		void SetRenderView( SceneRenderTask* pSceneTask );

		Scene* GetScene();
		void SetScene( Scene* pScene );

		void RenderFrame( Renderer* pRenderer );

	public:
		void SetPerspectiveProjectionParams( float Near , float Far , float Aspect , float Fov );
		void SetOrthogonalProjectionParams( float Near , float Far , float Width , float Height );
		void SetOffsetProjectionParams( float Left , float Right , float Bottom , float Up , float Near , float Far );

		const Matrix4f& GetProjectionMatrix() const;

		void SetClipPlane( float Near , float Far );
		void SetAspect( float Aspect );
		void SetFieldOfView( float Fov );
		
		float GetNearClipPlane();
		float GetFarClipPlane();
		float GetAspect();
		float GetFieldOfView();

		SpatialController<Node>& Spatial();

	protected:
		// set perspective project matrix to RenderView for render scene
		void ApplyPerspectiveProjectionParams();
		// set orthogonal project matrix to RenderView for render scene
		void ApplyOrthogonalProjectionParams();

	public:
		ParameterContainer Parameters;

	protected:
		SceneRenderTask* m_pCameraView;
		Scene* m_pScene;

	protected:
		float m_fNear;
		float m_fFar;
		float m_fAspect;
		float m_fFov;
		float m_fWidth;
		float m_fHeight;
		
	protected:
		Matrix4f m_ProjMatrix;

	protected:
		Vector3fParameterWriter* m_pViewPositionWriter;
		SpatialController<Node>* m_pSpatialController;
	};
}
#endif