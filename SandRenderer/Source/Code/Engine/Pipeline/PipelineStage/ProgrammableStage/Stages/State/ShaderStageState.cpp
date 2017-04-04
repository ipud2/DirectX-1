#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/State/ShaderStageState.h"

using namespace Sand;

ShaderStageState::ShaderStageState()
	:ShaderProgramID( -1 ) ,
	ConstantBuffers( nullptr ) ,
	SamplerStates( nullptr ) ,
	UnorderedAccessViews( nullptr ) ,
	UAVInitialCounts( -1 ) ,
	ShaderResourceViews( nullptr ) ,

	m_pSisterState( nullptr ) ,
	m_FeatureLevel( D3D_FEATURE_LEVEL_9_1 )
{

}

ShaderStageState::~ShaderStageState()
{

}

void ShaderStageState::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;
}

void ShaderStageState::ClearState()
{
	ShaderProgramID.InitializeState();
	ConstantBuffers.InitializeStates();
	SamplerStates.InitializeStates();
	ShaderResourceViews.InitializeStates();
	UnorderedAccessViews.InitializeStates();
	UAVInitialCounts.InitializeStates();
}

void ShaderStageState::SetSister( ShaderStageState* pState )
{
	m_pSisterState = pState;

	ShaderProgramID.SetSister( &m_pSisterState->ShaderProgramID );
	ConstantBuffers.SetSister( &m_pSisterState->ConstantBuffers );
	SamplerStates.SetSister( &m_pSisterState->SamplerStates );
	ShaderResourceViews.SetSister( &m_pSisterState->ShaderResourceViews );
	UnorderedAccessViews.SetSister( &m_pSisterState->UnorderedAccessViews );
	UAVInitialCounts.SetSister( &m_pSisterState->UAVInitialCounts );
}

void ShaderStageState::ResetUpdateFlags()
{
	ShaderProgramID.ResetTracking();
	ConstantBuffers.ResetTracking();
	SamplerStates.ResetTracking();
	ShaderResourceViews.ResetTracking();
	UnorderedAccessViews.ResetTracking();
	UAVInitialCounts.ResetTracking();
}