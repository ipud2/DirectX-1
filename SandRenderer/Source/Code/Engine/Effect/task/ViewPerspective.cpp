#include <Engine/PCH.h>
#include "ViewPerspective.h"
#include "Engine/Object/Scene/Entity.h"
#include "Engine/Resource/Texture/Texture2D.h"
#include "Engine/Resource/Texture/Texture2DConfig.h"
#include "Engine/Object/Scene/Scene.h"

using namespace Sand;

ViewPerspective::ViewPerspective( Renderer& renderer , ResourceProxyPtr RenderTarget , ResourceProxyPtr DepthTarget /* = nullptr */ )
{
	SetRenderTargets( RenderTarget , DepthTarget );
}

ViewPerspective::~ViewPerspective()
{

}

void ViewPerspective::Update( float fTime )
{

}

void ViewPerspective::QueuePreTasks( Renderer* pRenderer )
{
	pRenderer->QueueTask( this );
}

void ViewPerspective::ExecuteTask( PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	if( m_pScene )
	{
		// 设置render target view and depth stencil view
		pPipelineManager->ClearRenderTargets();
		pPipelineManager->GetOutputMergeStageRef().DesiredState.RenderTargetViews.SetState( 0 , m_RenderTarget->GetRenderTargetViewID() );
		pPipelineManager->GetOutputMergeStageRef().DesiredState.DepthStencilViews.SetState( m_DepthTarget->GetDepthStencilViewID() );
		pPipelineManager->ApplyRenderTargets();

		// set background colors
		pPipelineManager->ClearBuffers( m_vColor , 1.0f );

		
		// ----------------Configure View Port---------------------
		ConfigureViewPortsToRasterizerStage( pPipelineManager );

		// ----------------Update View and Proj Matrix---------------
		SetRenderParams( pParameterManager );

		// ----------------Light-------------------------------
		if( m_pScene->GetLightCount() > 0 )
		{
			// 设置灯光参数，只支持0号灯光
			m_pScene->GetLight( 0 )->UpdateRenderParams( pParameterManager );
		}

		// 清除管线资源
		pPipelineManager->ClearPipelineResource();

		// 遍历场景图绘制所有物体
		m_pScene->GetRootNode()->Render( pPipelineManager , pParameterManager , VT_PERSPECTIVE );
	}
}

std::wstring ViewPerspective::GetName()
{
	return std::wstring( L"ViewPerspective" );
}

void ViewPerspective::SetRenderTargets( ResourceProxyPtr RenderTarget , ResourceProxyPtr DepthTarget )
{
	m_RenderTarget = RenderTarget;

	// 删除原depth target
	if( nullptr != m_DepthTarget )
	{
		Renderer::Get()->DeleteResource( m_DepthTarget );
		m_DepthTarget = nullptr;
	}

	if( nullptr != m_RenderTarget )
	{
		Resource* pResource = Renderer::Get()->GetResourceByIndex( RenderTarget->GetResourceID() );

		if( pResource->GetType() == RT_TEXTURE2D )
		{
			Texture2D* pTexture = ( Texture2D* )pResource;
			D3D11_TEXTURE2D_DESC Desc = pTexture->GetActualDescription();

			if( DepthTarget != nullptr )
			{
				m_DepthTarget = DepthTarget;
			}
			else
			{
				Texture2DConfig DepthConfig;
				DepthConfig.SetDepthBuffer( Desc.Width , Desc.Height );
				m_DepthTarget = Renderer::Get()->CreateTexture2D( &DepthConfig , 0 );
			}
		}
	}

	// 设置默认的视图
	SetViewPortID( 0 );
}