#include "PCH.h"
#include "OutputMergeStage.h"
#include "Renderer.h"

#include "RenderTargetView.h"
#include "DepthStencilView.h"

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

		std::vector<ID3D11RenderTargetView*> pRenderTargetViews;
		ID3D11DepthStencilView* pDepthStencilView = 0;

		// --------------------------Render Target View-------------------
		for( int i = 0; i < DesiredState.GetRenderTargetCount(); i++ )
		{
			RenderTargetView& rtv = pRenderer->GetRenderTargetViewByIndex( DesiredState.RenderTargetViews.GetState( i ) );

			pRenderTargetViews.push_back( rtv.GetRenderTargetView() );
		}


		//-------------------Depth Stencil View-----------------------
		DepthStencilView& DSV = pRenderer->GetDepthStencilViewByIndex( DesiredState.DepthStencilViews.GetState() );
		pDepthStencilView = DSV.Get();

		pContext->OMSetRenderTargets( DesiredState.GetRenderTargetCount() , &pRenderTargetViews[0] , pDepthStencilView );


		// ----------------将Desired State 拷贝给 Current State的方式------------------
		for( int i = 0; i < DesiredState.GetRenderTargetCount(); i++ )
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

const OutputMergeStageState& Sand::OutputMergeStage::GetCurrentState() const
{
	return CurrentState;
}
