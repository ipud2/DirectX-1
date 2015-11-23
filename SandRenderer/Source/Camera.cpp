#include "PCH.h"
#include "Camera.h"
#include "Scene.h"

using namespace Sand;

Camera::Camera()
	:m_pCameraView( nullptr ) ,
	m_pScene( nullptr ) ,

	m_fNear( 0.1f ) ,
	m_fFar( 100.0f ) ,
	m_fAspect( 1280.0f / 800.0f ) ,
	m_fFov( static_cast< float >( SAND_PI ) / 4.0f ) , 
	m_fWidth(1280.0f) , 
	m_fHeight(800.0f) , 
	m_ProjMatrix() , 
	m_pViewPositionWriter(nullptr) , 
	m_pSpatialController(nullptr)
{
	m_pSpatialController = new SpatialController < Node >();
	GetRootNode()->GetControllersRef().Attach( m_pSpatialController );

	m_ProjMatrix.MakeIdentity();

	// 用于将View Position写入到对应参数的Writer中
	// 这里是第一次调用，因此会在参数管理器中创建一个名字为ViewPosition的参数对象
	// 并设置其初始值
	m_pViewPositionWriter = Parameters.SetValueToVectorParameterWriter( L"ViewPosition" , Vector4f( 0.0f , 0.0f , 0.0f , 0.0f ) );
}

Camera::~Camera()
{
	SAFE_DELETE( m_pCameraView );
}

void Camera::SetRenderView( SceneRenderTask* pSceneTask )
{
	m_pCameraView = pSceneTask;
}

SceneRenderTask* Camera::GetRenderView()
{
	return m_pCameraView;
}

void Camera::SetScene( Scene* pScene )
{
	m_pScene = pScene;
}

Scene* Camera::GetScene()
{
	return m_pScene;
}

void Camera::RenderFrame( Renderer* pRenderer )
{
	if( m_pCameraView )
	{
		if( m_pScene )
		{
			m_pCameraView->SetScene( m_pScene );
		}

		// 计算相机的位置
		Vector3f p = GetRootNode()->GetTransformRef().GetPositionRef();
		m_pViewPositionWriter->SetValue( Vector4f( p.x , p.y , p.z , 1.0f ) );

		// 初始化渲染参数的值
		Parameters.InitRenderParams();

		m_pCameraView->SetViewMatrix( m_pRoot->GetTransformRef().GetView() );
		m_pCameraView->QueuePreTasks( pRenderer );

		pRenderer->ProcessTaskQueue();
	}
}

void Camera::SetPerspectiveProjectionParams( float Near , float Far , float Aspect , float Fov )
{
	m_fNear = Near;
	m_fFar = Far;
	m_fAspect = Aspect;
	m_fFov = Fov;

	ApplyPerspectiveProjectParams();
}

void Camera::SetOrthogonalProjectionParams( float Near , float Far , float Width , float Height )
{
	m_fNear = Near;
	m_fFar = Far;
	m_fWidth = Width;
	m_fHeight = Height;

	ApplyOrthogonalProjectionParams();
}

void Camera::SetOffsetProjectionParams( float Left , float Right , float Bottom , float Top , float Near , float Far )
{
	m_ProjMatrix[0] = 2.0f * Near / ( Right - Left );
	m_ProjMatrix[1] = 0.0f;
	m_ProjMatrix[2] = 0.0f;
	m_ProjMatrix[3] = 0.0f;

	m_ProjMatrix[4] = 0.0f;
	m_ProjMatrix[5] = 2.0f * Near / ( Top - Bottom );
	m_ProjMatrix[6] = 0.0f;
	m_ProjMatrix[7] = 0.0f;

	m_ProjMatrix[8] = ( Left + Right ) / ( Left - Right );
	m_ProjMatrix[9] = ( Top + Bottom ) / ( Bottom - Top );
	m_ProjMatrix[10] = Far / ( Far - Near );
	m_ProjMatrix[11] = 1.0f;

	m_ProjMatrix[12] = 0.0f;
	m_ProjMatrix[13] = 0.0f;
	m_ProjMatrix[14] = Near * Far / ( Near - Far );
	m_ProjMatrix[15] = 0.0f;

	if( m_pCameraView )
	{
		m_pCameraView->SetProjMatrix( m_ProjMatrix );
	}
}

const Matrix4f& Camera::GetProjectionMatrix() const
{
	return m_ProjMatrix;
}

void Camera::SetClipPlane( float Near , float Far )
{
	m_fNear = Near;

	m_fFar = Far;

	ApplyPerspectiveProjectParams();
}

void Camera::SetAspect( float Aspect )
{
	m_fAspect = Aspect;

	ApplyPerspectiveProjectParams();
}

void Camera::SetFieldOfView( float Fov )
{
	m_fFov = Fov;

	ApplyPerspectiveProjectParams();
}

float Camera::GetNearClipPlane()
{
	return m_fNear;
}

float Camera::GetFarClipPlane()
{
	return m_fFar;
}

float Camera::GetAspect()
{
	return m_fAspect;
}

float Camera::GetFieldOfView()
{
	return m_fFov;
}

void Camera::ApplyPerspectiveProjectParams()
{
	m_ProjMatrix = Matrix4f::PerspectiveFovLHMatrix( m_fFov , m_fAspect , m_fNear , m_fFar );

	if( m_pCameraView )
	{
		m_pCameraView->SetProjMatrix( m_ProjMatrix );
	}
}

void Camera::ApplyOrthogonalProjectionParams()
{
	m_ProjMatrix = Matrix4f::OrthographicLHMatrix( m_fNear , m_fFar , m_fWidth , m_fHeight );

	if( m_pCameraView )
	{
		m_pCameraView->SetProjMatrix( m_ProjMatrix );
	}
}

SpatialController<Node>& Camera::Spatial()
{
	return ( *m_pSpatialController );
}