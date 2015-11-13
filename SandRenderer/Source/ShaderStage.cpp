#include "PCH.h"
#include "ShaderStage.h"

using namespace Sand;

ShaderStage::ShaderStage()
{
	DesiredState.SetSister( &CurrentState );
}

ShaderStage::~ShaderStage()
{

}

void ShaderStage::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;
}

void ShaderStage::ClearDesiredState()
{
	DesiredState.ClearState();
}

void ShaderStage::ClearCurrentState()
{
	CurrentState.ClearState();
}

void ShaderStage::ApplyDesiredState( ID3D11DeviceContext* pContext )
{
	if( DesiredState.ShaderProgramID.IsUpdateNeeded() )
	{
		BindShaderProgram( pContext );
	}

	if( DesiredState.ConstantBuffers.IsUpdateNeed() )
	{
		BindConstantBuffers( pContext );
	}

	if( DesiredState.SamplerStates.IsUpdateNeed() )
	{
		BindSamplerStates( pContext );
	}

	if( DesiredState.ShaderResourceViews.IsUpdateNeed() )
	{
		BindShaderResourceViews( pContext );
	}

	if( DesiredState.UnorderedAccessViews.IsUpdateNeed() || DesiredState.UAVInitialCounts.IsUpdateNeed() )
	{
		BindUnorderedAccessViews( pContext );
	}

	DesiredState.ResetUpdateFlags();
	CurrentState = DesiredState;
}