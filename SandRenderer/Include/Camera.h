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

		SceneRenderTask* GetRenderView();
		void SetRenderView( SceneRenderTask* pSceneTask );

		Scene* GetScene();
		void SetScene( Scene* pScene );
		
		// render a frame
		void RenderFrame( Renderer* pRenderer );

		// -------------------设置投影相关数据------------------------
		void SetPerspectiveProjectionParams( float Near , float Far , float Aspect , float Fov );
		void SetOrthogonalProjectionParams( float Near , float Far , float Width , float Height );
		void SetOffsetProjectionParams( float Left , float Right , float Bottom , float Up , float Near , float Far );

		const Matrix4f& GetProjectionMatrix() const;

		// ------------------设置相机相关属性---------------------
		void SetClipPlane( float Near , float Far );
		void SetAspect( float Aspect );
		void SetFieldOfView( float Fov );

		float GetNearClipPlane();
		float GetFarClipPlane();
		float GetAspect();
		float GetFieldOfView();


		SpatialController<Node>& Spatial();
		
	protected:
		void ApplyPerspectiveProjectParams();
		void ApplyOrthogonalProjectionParams();

	public:
		ParameterContainer Parameters;

	protected:
		SceneRenderTask* m_pCameraView;
		
		Scene* m_pScene;

		// -----------相机相关数据----------------
		float m_fNear;
		float m_fFar;
		float m_fAspect;
		float m_fFov;

		float m_fWidth;
		float m_fHeight;
		// ----------------------------------------

		Matrix4f m_ProjMatrix;

		VectorParameterWriter* m_pViewPositionWriter;

		SpatialController<Node>* m_pSpatialController;
	};
};
#endif