#include "RasterizerStageState.h"

using namespace Sand;

Sand::RasterizerStageState::RasterizerStageState() :
RasterizerStates( -1 ) ,

	ViewportCount( 0 ) ,
	Viewports( -1 ) ,

	ScissorRectCount( 0 ) ,
	ScissorRects( D3D11_RECT() ) ,

	m_FeatureLevel( D3D_FEATURE_LEVEL_9_1 ) ,

	m_pSisterState( nullptr )
{
	ClearState();
}

Sand::RasterizerStageState::~RasterizerStageState()
{

}

void Sand::RasterizerStageState::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;
}

void Sand::RasterizerStageState::ClearState()
{
	RasterizerStates.InitializeState();

	ViewportCount.InitializeState();
	Viewports.InitializeStates();

	ScissorRectCount.InitializeState();
	ScissorRects.InitializeStates();
}

void Sand::RasterizerStageState::SetSisterState( RasterizerStageState* pState )
{
	m_pSisterState = pState;

	RasterizerStates.SetSister( &pState->RasterizerStates );

	ViewportCount.SetSister( &pState->ViewportCount );
	Viewports.SetSister( &pState->Viewports );

	ScissorRectCount.SetSister( &pState->ScissorRectCount );
	ScissorRects.SetSister( &pState->ScissorRects );
}

void Sand::RasterizerStageState::ResetUpdateFlags()
{
	RasterizerStates.ResetTracking();

	ViewportCount.ResetTracking();
	Viewports.ResetTracking();

	ScissorRectCount.ResetTracking();
	ScissorRects.ResetTracking();
}

