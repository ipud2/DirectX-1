#include <Engine/PCH.h>
#include "ViewShadowMap.h"
#include "Engine/Object/Scene/Node.h"
#include "Engine/Object/Scene/Scene.h"

using namespace Sand;

ViewShadowMap::ViewShadowMap( Renderer& renderer , ResourceProxyPtr DepthTarget , int ViewPortWidth , int ViewPortHeight )
{
	m_DepthTarget = DepthTarget;

	D3D11_VIEWPORT  ViewPort;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.Width = static_cast< float >( ViewPortWidth );
	ViewPort.Height = static_cast< float >( ViewPortHeight );
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;

	int ViewPortID = renderer.CreateViewPort( ViewPort );

	SetViewPortID( ViewPortID );
}

ViewShadowMap::~ViewShadowMap()
{

}

void ViewShadowMap::Update( float fTime )
{

}

void ViewShadowMap::QueuePreTasks( Renderer* pRenderer )
{
	pRenderer->QueueTask( this );
}

void ViewShadowMap::ExecuteTask( PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	if ( m_pScene )
	{
		// 设置RTV和DSV
		pPipelineManager->ClearRenderTargets();
		pPipelineManager->GetOutputMergeStageRef().DesiredState.RenderTargetViews.SetState( 0 , 0 );
		pPipelineManager->GetOutputMergeStageRef().DesiredState.DepthStencilViews.SetState( m_DepthTarget->GetDepthStencilViewID() );
		pPipelineManager->ApplyRenderTargets();

		// 清除DepthStencilBuffer中的值
		pPipelineManager->ClearDepthStencilBuffer( );

		// ----------------Configure View Port---------------------
		ConfigureViewPortsToRasterizerStage( pPipelineManager );

		// ----------------Update View and Proj Matrix---------------
		SetRenderParams( pParameterManager );

		// 清除管线资源
		pPipelineManager->ClearPipelineResource();

		// 遍历场景图绘制所有物体
		m_pScene->GetRootNode()->Render( pPipelineManager , pParameterManager , VT_SHADOW_MAP );
	}
}

std::wstring ViewShadowMap::GetName()
{
	return std::wstring( L"ViewShadowMap" );
}