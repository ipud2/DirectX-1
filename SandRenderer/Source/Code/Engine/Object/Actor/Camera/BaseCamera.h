#ifndef BaseCamera_h
#define BaseCamera_h

#include "Engine/Object/Actor/Actor.h"
#include "Engine/Object/Controller/SpatialController.h"
#include "Engine/Object/Controller/OrientationController.h"
#include "Engine/Event/IEvent.h"
#include "Engine/Event/IEventListener.h"
#include "Engine/Utility/Timer.h"
#include "Engine/Event/EventManager.h"

namespace Sand
{
	enum ControlKeys
	{
		ForwardKey = 0 ,
		BackKey ,
		LeftKey ,
		RightKey ,
		UpKey ,
		DownKey ,
		SpeedUpKey ,

		NumControlKeys
	};

	class BaseCamera : public Actor , public IEventListener
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

		Vector3f GetViewPosition();
		void SetViewPosition( Vector3f ViewPosition );

		bool HandleEvent( EventPtr pEvent );

	public:
		void Update();

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

	public:
		static const UINT keyBindings[NumControlKeys];
		bool m_bProcessKey[NumControlKeys];

		int m_iLastMouseX;
		int m_iLastMouseY;
		int m_iMouseDeltaX;
		int m_iMouseDeltaY;

		Timer m_Timer;
	};
};
#endif