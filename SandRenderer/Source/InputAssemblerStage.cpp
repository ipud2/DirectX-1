#include "PCH.h"
#include "Renderer.h"
#include "Log.h"
#include "InputAssemblerStage.h"

using namespace Sand;

InputAssemblerStage::InputAssemblerStage()
{
	DesiredState.SetSisterState( &CurrentState );
}

InputAssemblerStage::~InputAssemblerStage()
{

}

void InputAssemblerStage::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;

	CurrentState.SetFeatureLevel( Level );
	DesiredState.SetFeatureLevel( Level );
}

void InputAssemblerStage::ClearCurrentState()
{
	CurrentState.ClearState();
}

void InputAssemblerStage::ClearDesiredState()
{
	DesiredState.ClearState();
}

void InputAssemblerStage::ApplyDesiredState( ID3D11DeviceContext* pContext )
{
	Renderer* pRenderer = Renderer::Get();

	if( DesiredState.InputLayout.IsUpdateNeeded() )
	{	
		
	}

	if( DesiredState.PrimitiveTopology.IsUpdateNeeded() )
	{

	}

	if( DesiredState.VertexBuffers.IsUpdateNeed() || DesiredState.VertexBufferStrides.IsUpdateNeed() || DesiredState.VertexBufferOffsets.IsUpdateNeed() )
	{

	}

	if( DesiredState.IndexBuffer.IsUpdateNeeded() || DesiredState.IndexBufferFormat.IsUpdateNeeded() )
	{

	}
}

const InputAssemblerState& InputAssemblerStage::GetCurrentState() const
{
	return CurrentState;
}