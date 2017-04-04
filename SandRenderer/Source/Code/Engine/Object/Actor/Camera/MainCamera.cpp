#include <Engine/PCH.h>
#include "MainCamera.h"
#include "Engine/Object/Scene/Scene.h"

using namespace Sand;

MainCamera::MainCamera()
	:
	m_fNear( 1.0f ) ,
	m_fFar( 1000.0f ) ,
	m_fAspect( 800.0f / 600.0f ) ,
	m_fFov( static_cast< float >( SAND_PI ) / 4.0f ) ,
	m_fWidth( 800.0f ) ,
	m_fHeight( 600.0f )
{
				
}

MainCamera::~MainCamera()
{

}

void MainCamera::RenderFrame( Renderer* pRenderer )
{
	if ( m_pRenderView )
	{
		if( m_pScene )
		{
			m_pRenderView->SetScene( m_pScene );
		}

		// ���������λ��
		m_pViewPositionWriter->SetValue( GetRootNode()->GetTransformRef().GetWorldMatrix().GetTranslate() );

		// ��ʼ����Ⱦ������ֵ
		ParameterWriters.InitRenderParams();

		m_pRenderView->SetViewMatrix( m_pRoot->GetTransformRef().GetView() );

		// ������Ⱦ��ͼ���������б�
		m_pRenderView->QueuePreTasks( pRenderer );

		// ִ������
		pRenderer->ProcessTaskQueue();
	}
}

void MainCamera::SetPerspectiveProjectionParams( float Near , float Far , float Aspect , float Fov )
{
	m_fNear = Near;
	m_fFar = Far;
	m_fAspect = Aspect;
	m_fFov = Fov;

	ApplyPerspectiveProjectionParams();
}

void MainCamera::SetClipPlane( float Near , float Far )
{
	m_fNear = Near;

	m_fFar = Far;

	ApplyPerspectiveProjectionParams();
}

void MainCamera::SetAspect( float Aspect )
{
	m_fAspect = Aspect;

	ApplyPerspectiveProjectionParams();
}

void MainCamera::SetFieldOfView( float Fov )
{
	m_fFov = Fov;

	ApplyPerspectiveProjectionParams();
}

float MainCamera::GetNearClipPlane()
{
	return m_fNear;
}

float MainCamera::GetFarClipPlane()
{
	return m_fFar;
}

float MainCamera::GetAspect()
{
	return m_fAspect;
}

float MainCamera::GetFieldOfView()
{
	return m_fFov;
}

void MainCamera::ApplyPerspectiveProjectionParams()
{
	m_ProjMatrix = Matrix4f::PerspectiveFovLHMatrix( m_fFov , m_fAspect , m_fNear , m_fFar );

	if ( m_pRenderView )
	{
		m_pRenderView->SetProjMatrix( m_ProjMatrix );
	}
}