#include <Engine/PCH.h>
#include "OutputMergeStageState.h"

using namespace Sand;

Sand::OutputMergeStageState::OutputMergeStageState() :
BlendStates( -1 ) ,

	DepthStencilStates( -1 ) ,
	StencilRef( 0 ) ,

	RenderTargetViews( -1 ) ,
	DepthStencilViews( -1 ) ,

	m_FeatureLevel( D3D_FEATURE_LEVEL_9_1 ) ,

	m_pSisterState( nullptr )
{
	ClearState();
}

Sand::OutputMergeStageState::~OutputMergeStageState()
{

}

void Sand::OutputMergeStageState::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;
}

void Sand::OutputMergeStageState::ClearState()
{
	BlendStates.InitializeState();

	DepthStencilStates.InitializeState();
	StencilRef.InitializeState();

	RenderTargetViews.InitializeStates();
	DepthStencilViews.InitializeState();
}

void Sand::OutputMergeStageState::SetSisterState( OutputMergeStageState* pState )
{
	m_pSisterState = pState;

	BlendStates.SetSister( &pState->BlendStates );

	DepthStencilStates.SetSister( &pState->DepthStencilStates );
	StencilRef.SetSister( &pState->StencilRef );

	RenderTargetViews.SetSister( &pState->RenderTargetViews );
	DepthStencilViews.SetSister( &pState->DepthStencilViews );
}

void Sand::OutputMergeStageState::ResetUpdateFlags()
{
	BlendStates.ResetTracking();

	DepthStencilStates.ResetTracking();
	StencilRef.ResetTracking();

	RenderTargetViews.ResetTracking();
	DepthStencilViews.ResetTracking();
}

int OutputMergeStageState::GetRenderTargetCount() const
{
	unsigned int count = 0;

	for( int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++ )
	{
		if( RenderTargetViews.GetState( i ) != -1 )
		{
			count++;
		}
	}

	return count;
}