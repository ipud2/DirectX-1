#include "PCH.h"
#include "RasterizerStage.h"
#include "Renderer.h"
#include "ViewPort.h"

using namespace Sand;


Sand::RasterizerStage::RasterizerStage()
{
	DesiredState.SetSisterState( &CurrentState );
}

Sand::RasterizerStage::~RasterizerStage()
{

}

void Sand::RasterizerStage::ClearCurrentState()
{
	CurrentState.ClearState();
}

void Sand::RasterizerStage::ClearDesiredState()
{
	DesiredState.ClearState();
}

void Sand::RasterizerStage::ApplyDesiredState( ID3D11DeviceContext* pContext )
{
	Renderer* pRenderer = Renderer::Get();

	if( DesiredState.RasterizerStates.IsUpdateNeeded() )
	{
		// 获取索引对应的状态对象
		RasterizerStateComPtr pRasterizerStateComPtr = pRenderer->GetRasterizerState( DesiredState.RasterizerStates.GetState() );

		if( pRasterizerStateComPtr )
		{
			ID3D11RasterizerState* pRasterizerState = pRasterizerStateComPtr.Get();

			pContext->RSSetState( pRasterizerState );
		}
	}

	if( DesiredState.ViewportCount.IsUpdateNeeded() || DesiredState.Viewports.IsUpdateNeed() )
	{
		D3D11_VIEWPORT viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

		for( int i = 0; i < DesiredState.ViewportCount.GetState(); i++ )
		{
			const ViewPort& view_port = pRenderer->GetViewPort( DesiredState.Viewports.GetState( i ) );

			viewports[i] = view_port.m_ViewPort;
		}

		pContext->RSSetViewports( DesiredState.ViewportCount.GetState() , viewports );
	}

	if( DesiredState.ScissorRectCount.IsUpdateNeeded() || DesiredState.ScissorRects.IsUpdateNeed() )
	{
		D3D11_RECT rects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

		for( int i = 0; i < DesiredState.ScissorRectCount.GetState(); i++ )
		{
			rects[i] = DesiredState.ScissorRects.GetState( i );
		}

		pContext->RSSetScissorRects( DesiredState.ScissorRectCount.GetState() , rects );
	}

	DesiredState.ResetUpdateFlags();
	DesiredState = CurrentState;
}

void Sand::RasterizerStage::SetFeatureLevel( D3D_FEATURE_LEVEL level )
{
	m_FeatureLevel = level;
}

const RasterizerStageState& Sand::RasterizerStage::GetCurrentState() const
{
	return CurrentState;
}
