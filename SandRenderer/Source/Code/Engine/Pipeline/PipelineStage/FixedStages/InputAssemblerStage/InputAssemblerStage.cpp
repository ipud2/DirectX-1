#include <Engine/PCH.h>
#include "Engine/Render/DXGI/Renderer.h"
#include "Engine/Utility/Log.h"
#include "Engine/Pipeline/PipelineStage/FixedStages/InputAssemblerStage/InputAssemblerStage.h"
#include "Engine/Resource/Buffer/VertexBuffer.h"
#include "Engine/Resource/Buffer/IndexBuffer.h"

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
		InputLayoutComPtr pLayout = pRenderer->GetInputLayout( DesiredState.InputLayout.GetState() );

		pContext->IASetInputLayout( pLayout.Get() );
	}

	if( DesiredState.PrimitiveTopology.IsUpdateNeeded() )
	{
		pContext->IASetPrimitiveTopology( DesiredState.PrimitiveTopology.GetState() );
	}

	if( DesiredState.VertexBuffers.IsUpdateNeed() || DesiredState.VertexBufferStrides.IsUpdateNeed() || DesiredState.VertexBufferOffsets.IsUpdateNeed() )
	{
		int MinSlot = min( DesiredState.VertexBuffers.GetStartSlot() , min( DesiredState.VertexBufferOffsets.GetStartSlot() , DesiredState.VertexBufferStrides.GetStartSlot() ) );
		int MaxSlot = max( DesiredState.VertexBuffers.GetEndSlot() , max( DesiredState.VertexBufferOffsets.GetEndSlot() , DesiredState.VertexBufferStrides.GetEndSlot() ) );

		ID3D11Buffer* pBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		for( unsigned int i = 0; i < DesiredState.GetAvaliableSlotCount(); i++ )
		{
			int index = DesiredState.VertexBuffers.GetState( i );

			VertexBuffer* pBuffer = pRenderer->GetVertexBufferByIndex( index );

			if( pBuffer )
			{
				pBuffers[i] = reinterpret_cast< ID3D11Buffer* >( pBuffer->GetResource() );
			}
		}

		pContext->IASetVertexBuffers( MinSlot , MaxSlot - MinSlot + 1 , &pBuffers[MinSlot] , DesiredState.VertexBufferStrides.GetSlotLocation( MinSlot ) , DesiredState.VertexBufferOffsets.GetSlotLocation( MinSlot ) );
	}

	if( DesiredState.IndexBuffers.IsUpdateNeeded() || DesiredState.IndexBufferFormat.IsUpdateNeeded() )
	{
		int index = DesiredState.IndexBuffers.GetState();

		IndexBuffer* pBuffer = pRenderer->GetIndexBufferByIndex( index );

		if( pBuffer )
		{
			ID3D11Buffer* pIndexBuffer = reinterpret_cast< ID3D11Buffer* >( pBuffer->GetResource() );
			pContext->IASetIndexBuffer( pIndexBuffer , DesiredState.IndexBufferFormat.GetState() , 0 );
		}
		else
		{
			pContext->IASetIndexBuffer( nullptr , DesiredState.IndexBufferFormat.GetState() , 0 );
		}
	}

	DesiredState.ResetUpdateFlags();
	CurrentState = DesiredState;
}

const InputAssemblerState& InputAssemblerStage::GetCurrentState() const
{
	return CurrentState;
}