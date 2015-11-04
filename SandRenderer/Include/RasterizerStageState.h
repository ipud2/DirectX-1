#ifndef RasterizerState_h
#define RasterizerState_h

#include "PCH.h"
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace Sand
{
	class RasterizerState
	{
	public:
		RasterizerState();
		virtual ~RasterizerState();

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );
		void ClearState();
		void SetSisterState( RasterizerState* pState );
		void ResetUpdateFlags();

		unsigned int GetAvaliableSlotCount();

		TStateMonitor<int> RasterizerStates;

		TStateMonitor<int> ViewportCount;
		TStateArrayMonitor<int , D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> Viewports;

		TStateMonitor<int> ScissorRectCount;
		TStateArrayMonitor<D3D11_RECT , D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> ScissorRects;

		// -------------------Index Buffer----------------------
		TStateMonitor<int> IndexBuffer;
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

		RasterizerState* m_pSisterState;

		unsigned int AvaliableSlotCount;
	};
}

#endif