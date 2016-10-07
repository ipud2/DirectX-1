#include "PCH.h"
#include "BaseCamera.h"
#include "EventKeyUp.h"
#include "EventKeyDown.h"
#include "EventMouseMove.h"
#include "EventMouseRButtonDown.h"

using namespace Sand;

static const int InvalidMousePos = -99999;

const UINT BaseCamera::keyBindings[NumControlKeys] =
{
	'W' , 'S' , 'A' , 'D' , 'Q' , 'E' , VK_CONTROL
};

BaseCamera::BaseCamera()
	:
	m_pRenderView( nullptr ) ,
	m_pScene( nullptr ) ,
	m_pViewPositionWriter( nullptr ) ,
	m_pSpatialController( nullptr ) ,
	m_pOrientationController( nullptr ) ,
	m_iLastMouseY( 0.0f ) ,
	m_iLastMouseX( 0.0f ) ,
	m_iMouseDeltaX( 0.0f ) ,
	m_iMouseDeltaY( 0.0f ) ,
	m_ProjMatrix()
{
	m_pSpatialController = new SpatialController < Node >();
	GetRootNode()->GetControllersRef().Attach( m_pSpatialController );

	m_pOrientationController = new OrientationController<Node>();
	GetRootNode()->GetControllersRef().Attach( m_pOrientationController );

	m_ProjMatrix.MakeIdentity();

	m_pViewPositionWriter = ParameterWriters.GetVector3fParameterWriter( L"ViewPosition" );
	m_pViewPositionWriter->SetValue( Vector3f( 0.0f , 0.0f , 0.0f ) );

	RequestEvent( SYSTEM_KEY_UP );
	RequestEvent( SYSTEM_KEY_DOWN );
	RequestEvent( SYSTEM_RBUTTON_UP );
	RequestEvent( SYSTEM_RBUTTON_DOWN );
	RequestEvent( SYSTEM_MOUSE_MOVE );
	RequestEvent( SYSTEM_MOUSE_LEAVE );
	RequestEvent( RENDER_FRAME_START );

	for ( UINT i = 0; i < NumControlKeys; i++ )
	{
		m_bProcessKey[i] = false;
	}
}

BaseCamera::~BaseCamera()
{
	SAFE_DELETE( m_pRenderView );
}

void BaseCamera::SetRenderView( SceneRenderTask* pSceneTask )
{
	m_pRenderView = pSceneTask;
}

SceneRenderTask* BaseCamera::GetRenderView()
{
	return m_pRenderView;
}

void BaseCamera::SetScene( Scene* pScene )
{
	m_pScene = pScene;
}

Scene* BaseCamera::GetScene()
{
	return m_pScene;
}

SpatialController<Node>& BaseCamera::Spatial()
{
	return ( *m_pSpatialController );
}

OrientationController<Node>& BaseCamera::Orientation()
{
	return ( *m_pOrientationController );
}

const Matrix4f& BaseCamera::GetProjectionMatrix() const
{
	return m_ProjMatrix;
}

Vector3f& BaseCamera::GetViewPosition()
{
	return GetRootNode()->GetTransformRef().GetWorldMatrix().GetTranslate();
}

void BaseCamera::SetViewPosition( Vector3f ViewPosition )
{
	m_ViewPosition = ViewPosition;
}

bool BaseCamera::HandleEvent( EventPtr pEvent )
{
	EventType eEvent = pEvent->GetEventType();

	if ( eEvent == SYSTEM_KEY_DOWN )
	{
		EventKeyDownPtr pKeyDown = std::static_pointer_cast< EventKeyDown >( pEvent );
		UINT key = pKeyDown->GetCharacterCode();

		for ( UINT i = 0; i < NumControlKeys; i++ )
		{
			if ( key == keyBindings[i] )
			{
				m_bProcessKey[i] = true;
				return true;
			}
		}
	}
	else if ( eEvent == SYSTEM_KEY_UP )
	{
		EventKeyUpPtr pKeyUp = std::static_pointer_cast< EventKeyUp >( pEvent );

		UINT key = pKeyUp->GetCharacterCode();

		for ( UINT i = 0; i < NumControlKeys; i++ )
		{
			if ( key == keyBindings[i] )
			{
				m_bProcessKey[i] = false;
				return true;
			}
		}
	}
	else if ( eEvent == SYSTEM_MOUSE_MOVE )
	{
		EventMouseMovePtr pMouseMove = std::static_pointer_cast< EventMouseMove >( pEvent );

		m_iMouseDeltaX = 0.0f;
		m_iMouseDeltaY = 0.0f;

		const int mouseX = pMouseMove->GetX();
		const int mouseY = pMouseMove->GetY();

		if ( pMouseMove->LButtonDown() )
		{
			m_iMouseDeltaX = mouseX - m_iLastMouseX;
			m_iMouseDeltaY = mouseY - m_iLastMouseY;
		}

		m_iLastMouseX = mouseX;
		m_iLastMouseY = mouseY;

		return true;
	}
	else if ( eEvent == RENDER_FRAME_START )
	{
		Update();
	}

	return false;
}

void BaseCamera::Update()
{
	m_Timer.Update();

	float TimeDelta = m_Timer.DeltaTime();
	
	float CamMoveSpeed = 10.0f * TimeDelta;

	if ( m_bProcessKey[SpeedUpKey] )
	{
		CamMoveSpeed *= 3.0f;
	}

	if ( m_bProcessKey[RightKey] )
	{
		Spatial().MoveRight( CamMoveSpeed );
	}
	else if ( m_bProcessKey[LeftKey] )
	{
		Spatial().MoveLeft( CamMoveSpeed );
	}
	else if ( m_bProcessKey[ForwardKey] )
	{
		Spatial().MoveForward( CamMoveSpeed );
	}
	else if ( m_bProcessKey[BackKey] )
	{
		Spatial().MoveBackward( CamMoveSpeed );
	}
	else if ( m_bProcessKey[UpKey] )
	{
		Spatial().MoveUp( CamMoveSpeed );
	}
	else if ( m_bProcessKey[DownKey] )
	{
		Spatial().MoveDown( CamMoveSpeed );
	}

	// Update Rotate
	float dx = ConvertToRadius( static_cast< float >( m_iMouseDeltaX ) * 0.25f );
	float dy = ConvertToRadius( static_cast< float >( m_iMouseDeltaY ) * 0.25f );

	Orientation().Pitch( dy );
	Orientation().RotateY( dx );

	// 由于MouseMove消息比较慢，所以容易出现多帧Update才一帧MoveMove处理
	// 导致m_iMouseDeltaX , m_iMouseDeltaY使用多次
	// 所以要么在此处置0
	// 要么将update移到move之后，每次计算出move的delta，就调用Update函数.
	m_iMouseDeltaX = 0;
	m_iMouseDeltaY = 0;
}