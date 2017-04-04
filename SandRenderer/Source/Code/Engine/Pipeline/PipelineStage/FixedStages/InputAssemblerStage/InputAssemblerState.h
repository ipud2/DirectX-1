#ifndef InputAssemblerState_h
#define InputAssemblerState_h

#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/Common/TStateMonitor.h"
#include "Engine/Pipeline/PipelineStage/Common/TStateArrayMonitor.h"

namespace Sand
{
	class InputAssemblerState
	{
	public:
		InputAssemblerState();
		virtual ~InputAssemblerState();

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );
		void ClearState();
		void SetSisterState( InputAssemblerState* pState );
		void ResetUpdateFlags();

		unsigned int GetAvaliableSlotCount();

		// -------------------Index Buffer----------------------
		TStateMonitor<int> IndexBuffers;
		TStateMonitor<DXGI_FORMAT> IndexBufferFormat;

		// --------------------Vertex Buffer-------------------
		TStateArrayMonitor<int , D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT> VertexBuffers;
		TStateArrayMonitor<unsigned int , D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT> VertexBufferStrides;
		TStateArrayMonitor<unsigned int , D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferOffsets;

		// ---------------Input Layout---------------------
		TStateMonitor<int> InputLayout;
		
		// -------------------Primitive Topology--------------------
		TStateMonitor<D3D11_PRIMITIVE_TOPOLOGY> PrimitiveTopology;

	protected:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		InputAssemblerState* m_pSisterState;

		unsigned int AvaliableSlotCount;
	};
}

#endif