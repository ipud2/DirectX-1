#ifndef OutputMergeStageState_h
#define OutputMergeStageState_h

#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/Common/TStateMonitor.h"
#include "Engine/Pipeline/PipelineStage/Common/TStateArrayMonitor.h"

namespace Sand
{
	class OutputMergeStageState
	{
	public:
		OutputMergeStageState();
		virtual ~OutputMergeStageState();

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );
		void ClearState();
		void SetSisterState( OutputMergeStageState* pState );
		void ResetUpdateFlags();

		int GetRenderTargetCount() const;

		// Blend State
		TStateMonitor<int> BlendStates;

		// Depth Stencil State
		TStateMonitor<int> DepthStencilStates;
		TStateMonitor<unsigned int> StencilRef;

		// Render Target View and Depth Stencil View
		TStateArrayMonitor<int , D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> RenderTargetViews;
		TStateMonitor<int> DepthStencilViews;

	protected:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		OutputMergeStageState* m_pSisterState;
	};
}

#endif