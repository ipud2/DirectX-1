#include "OutputMergeStage.h"
#include "Renderer.h"

using namespace Sand;

OutputMergeStage::OutputMergeStage()
{
	DesiredState.SetSisterState( &CurrentState );
}

OutputMergeStage::~OutputMergeStage()
{

}

void OutputMergeStage::ClearCurrentState()
{
	CurrentState.ClearState();
}

void OutputMergeStage::ClearDesiredState()
{
	DesiredState.ClearState();
}

void OutputMergeStage::ApplyDesiredState( ID3D11DeviceContext* pContext )
{
	ApplyDesiredRenderTargetStates( pContext );
	ApplyDesiredBlendAndDepthStencilStates( pContext );
}

void OutputMergeStage::ApplyDesiredRenderTargetStates( ID3D11DeviceContext* pContext )
{
	if( DesiredState.RenderTargetViews.IsUpdateNeed() || DesiredState.DepthStencilViews.IsUpdateNeeded() )
	{
		Renderer* pRenderer = Renderer::Get();

		ID3D11RenderTargetView* pRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		ID3D11DepthStencilView* pDepthStencilView = 0;

		// --------------------------Render Target View-------------------
		for( int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++ )
		{
			RenderTargetView& rtv = pRenderer->GetRenderTargetViewByIndex( DesiredState.RenderTargetViews.GetState( i ) );

			pRenderTargetViews[i] = rtv.m_RenderTargetView.Get();
		}


		//-------------------Depth Stencil View-----------------------
		DepthStencilView& DSV = pRenderer->GetDepthStencilViewByIndex( DesiredState.DepthStencilViews.GetState() );
		pDepthStencilView = DSV.m_DepthStencilView.Get();

		pContext->OMSetRenderTargets( D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT , pRenderTargetViews , pDepthStencilView );


		// ----------------一种更好的将Desired State 拷贝给 Current State的方式------------------
		for( int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++ )
		{
			CurrentState.RenderTargetViews.SetState( i , DesiredState.RenderTargetViews.GetState( i ) );
		}

		CurrentState.DepthStencilViews.SetState( DesiredState.DepthStencilViews.GetState() );

		DesiredState.RenderTargetViews.ResetTracking();
		DesiredState.DepthStencilViews.ResetTracking();
	}
}

void OutputMergeStage::ApplyDesiredBlendAndDepthStencilStates( ID3D11DeviceContext* pContext )
{
	Renderer* pRenderer = Renderer::Get();

	if( DesiredState.BlendStates.IsUpdateNeeded() )
	{
		BlendStateComPtr pBlendStateComPtr = pRenderer->GetBlendState( DesiredState.BlendStates.GetState() );

		if( pBlendStateComPtr )
		{
			ID3D11BlendState* pBlendState = pBlendStateComPtr.Get();

			if( pBlendState )
			{
				float BlendFactors[] = { 1.0f , 1.0f , 1.0f , 1.0f };

				pContext->OMSetBlendState( pBlendState , BlendFactors , 0xffffffff );
			}	

			CurrentState.BlendStates.SetState( DesiredState.BlendStates.GetState() );

			DesiredState.BlendStates.ResetTracking();
		}
		
	}

	if( DesiredState.DepthStencilStates.IsUpdateNeeded() || DesiredState.StencilRef.IsUpdateNeeded() )
	{
		DepthStencilStateComPtr pDepthStencilStateComPtr = pRenderer->GetDepthStencilState( DesiredState.DepthStencilStates.GetState() );

		if( pDepthStencilStateComPtr )
		{
			ID3D11DepthStencilState* pDepthStencilState = pDepthStencilStateComPtr.Get();

			if( pDepthStencilState )
			{
				pContext->OMSetDepthStencilState( pDepthStencilState , DesiredState.StencilRef.GetState() );
			}

			CurrentState.DepthStencilStates.SetState( DesiredState.DepthStencilStates.GetState() );
			CurrentState.StencilRef.SetState( DesiredState.StencilRef.GetState() );

			DesiredState.DepthStencilStates.ResetTracking();
			DesiredState.StencilRef.ResetTracking();
		}
	}
}

void OutputMergeStage::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;
}