#ifndef BaseCamera_h
#define BaseCamera_h

#include "Actor.h"
#include "SpatialController.h"
#include "OrientationController.h"

namespace Sand
{
	class BaseCamera : public Actor
	{
	public:
		BaseCamera();
		virtual ~BaseCamera();

	public:
		SceneRenderTask* GetRenderView();
		void SetRenderView( SceneRenderTask* pSceneTask );

		Scene* GetScene();
		void SetScene( Scene* pScene );

		virtual void RenderFrame( Renderer* pRenderer ) = 0;

		const Matrix4f& GetProjectionMatrix() const;

		Vector3f& GetViewPosition();
		void SetViewPosition( Vector3f ViewPosition );

	protected:
		SceneRenderTask* m_pRenderView;
		Scene* m_pScene;

	public:
		SpatialController<Node>& Spatial();
		OrientationController<Node>& Orientation();

	protected:
		SpatialController<Node>* m_pSpatialController;
		OrientationController<Node>* m_pOrientationController;

	protected:
		Vector3fParameterWriter* m_pViewPositionWriter;

	public:
		ParameterContainer ParameterWriters;

	protected:
		Matrix4f m_ProjMatrix;
		Vector3f m_ViewPosition;
	};
};
#endif