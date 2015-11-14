#include "PCH.h"
#include "InputAssemblerState.h"

using namespace Sand;


InputAssemblerState::InputAssemblerState() :
	IndexBuffers( -1 ) ,
	IndexBufferFormat( DXGI_FORMAT_R32_UINT ) ,

	VertexBuffers( -1 ) ,
	VertexBufferStrides( 0 ) ,
	VertexBufferOffsets( 0 ) ,

	InputLayout( -1 ) ,

	PrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED ) ,

	m_FeatureLevel( D3D_FEATURE_LEVEL_9_1 ) ,

	m_pSisterState( nullptr ) ,

	AvaliableSlotCount( 0 )
{
	ClearState();
}

InputAssemblerState::~InputAssemblerState()
{

}

void InputAssemblerState::SetFeatureLevel( D3D_FEATURE_LEVEL Level )
{
	m_FeatureLevel = Level;

	// 不同的特征级别，InputAssembler阶段可用的slot数不同
	if( m_FeatureLevel == D3D_FEATURE_LEVEL_11_0 )
	{
		AvaliableSlotCount = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	}
	else
	{
		AvaliableSlotCount = D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	}
}

void InputAssemblerState::ClearState()
{
	IndexBuffers.InitializeState();
	IndexBufferFormat.InitializeState();

	VertexBuffers.InitializeStates();
	VertexBufferOffsets.InitializeStates();
	VertexBufferStrides.InitializeStates();

	InputLayout.InitializeState();

	PrimitiveTopology.InitializeState();
}

void InputAssemblerState::SetSisterState( InputAssemblerState* pState )
{
	m_pSisterState = pState;

	IndexBuffers.SetSister( &pState->IndexBuffers );
	IndexBufferFormat.SetSister( &pState->IndexBufferFormat );
	
	VertexBuffers.SetSister( &pState->VertexBuffers );
	VertexBufferStrides.SetSister( &pState->VertexBufferStrides );
	VertexBufferOffsets.SetSister( &pState->VertexBufferOffsets );

	InputLayout.SetSister( &pState->InputLayout );

	PrimitiveTopology.SetSister( &pState->PrimitiveTopology );
}

void InputAssemblerState::ResetUpdateFlags()
{
	IndexBuffers.ResetTracking();
	IndexBufferFormat.ResetTracking();

	VertexBuffers.ResetTracking();
	VertexBufferOffsets.ResetTracking();
	VertexBufferStrides.ResetTracking();

	InputLayout.ResetTracking();

	PrimitiveTopology.ResetTracking();
}

unsigned int InputAssemblerState::GetAvaliableSlotCount()
{
	return AvaliableSlotCount;
}
