#include "Engine/PCH.h"
#include "Engine/Effect/Task/SceneRenderTask.h"
#include "Engine/Object/Scene/Entity.h"
#include "Engine/Object/Scene/Node.h"
#include "Engine/Utility/Log.h"

using namespace Sand;

SceneRenderTask::SceneRenderTask()
	:m_pScene( nullptr ) ,

	m_vColor() ,

	m_iViewPorts() ,
	m_uiViewPortCount( 1 ) ,

	ViewMatrix() ,
	ProjMatrix()
{

}

SceneRenderTask::~SceneRenderTask()
{

}

void SceneRenderTask::SetRenderParams( IParameterManager* pParamManager )
{
	// ÉèÖÃView MatrixºÍProj Matrix
	pParamManager->SetViewMatrixParameterData( &ViewMatrix );
	pParamManager->SetProjMatrixParameterData( &ProjMatrix );
}

void SceneRenderTask::SetUsageParams( IParameterManager* pParamManager )
{

}

void SceneRenderTask::SetScene( Scene* pScene )
{
	m_pScene = pScene;
}

Matrix4f SceneRenderTask::GetViewMatrix()
{
	return ViewMatrix;
}

Matrix4f SceneRenderTask::GetProjMatrix()
{
	return ProjMatrix;
}

void SceneRenderTask::SetViewMatrix( const Matrix4f& matrix )
{
	ViewMatrix = matrix;
}

void SceneRenderTask::SetProjMatrix( const Matrix4f& matrix )
{
	ProjMatrix = matrix;
}

void SceneRenderTask::SetViewPortID( int ViewPortID , unsigned int index /* = 0 */ )
{
	assert( index < D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE );

	m_iViewPorts[index] = ViewPortID;
}

void SceneRenderTask::SetViewPortCount( unsigned int count )
{
	assert( count < D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE );

	m_uiViewPortCount = count;
}

void SceneRenderTask::ConfigureViewPortsToRasterizerStage( PipelineManager* pPipelineManager )
{
	pPipelineManager->GetRasterizerStageRef().DesiredState.ViewportCount.SetState( m_uiViewPortCount );

	for( unsigned int i = 0; i < m_uiViewPortCount; i++ )
	{
		pPipelineManager->GetRasterizerStageRef().DesiredState.Viewports.SetState( i , m_iViewPorts[i] );
	}
}

const ViewPort& SceneRenderTask::GetViewPort( unsigned int slot )
{
	assert( slot < m_uiViewPortCount );

	return ( Renderer::Get()->GetViewPort( m_iViewPorts[slot] ) );
}

void SceneRenderTask::SetBackColor( const Vector4f& color )
{
	m_vColor = color;
}