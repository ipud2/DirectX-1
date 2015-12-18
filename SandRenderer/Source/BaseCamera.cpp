#include "PCH.h"
#include "BaseCamera.h"

using namespace Sand;

BaseCamera::BaseCamera()
	:
	m_pRenderView( nullptr ) ,
	m_pScene( nullptr ) ,
	m_pViewPositionWriter( nullptr ) ,
	m_pSpatialController( nullptr ) ,
	m_pOrientationController( nullptr ) ,
	m_ProjMatrix()
{
	m_pSpatialController = new SpatialController < Node >();
	GetRootNode()->GetControllersRef().Attach( m_pSpatialController );

	m_pOrientationController = new OrientationController<Node>();
	GetRootNode()->GetControllersRef().Attach( m_pOrientationController );

	m_ProjMatrix.MakeIdentity();

	m_pViewPositionWriter = ParameterWriters.GetVector3fParameterWriter( L"ViewPosition" );
	m_pViewPositionWriter->SetValue( Vector3f( 0.0f , 0.0f , 0.0f ) );
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