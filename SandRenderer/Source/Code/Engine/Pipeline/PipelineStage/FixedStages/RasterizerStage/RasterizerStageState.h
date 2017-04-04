#ifndef RasterizerState_h
#define RasterizerState_h

#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/Common/TStateMonitor.h"
#include "Engine/Pipeline/PipelineStage/Common/TStateArrayMonitor.h"

namespace Sand
{
	class RasterizerStageState
	{
	public:
		RasterizerStageState();
		virtual ~RasterizerStageState();

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );
		void ClearState();
		void SetSisterState( RasterizerStageState* pState );
		void ResetUpdateFlags();

		// ------------------¹âÕ¤»¯×´Ì¬---------------------
		TStateMonitor<int> RasterizerStates;

		// -------------------Viewport--------------------------
		TStateMonitor<int> ViewportCount;
		TStateArrayMonitor<int , D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> Viewports;

		// -----------------Scissor Rect----------------------------
		TStateMonitor<int> ScissorRectCount;
		TStateArrayMonitor<D3D11_RECT , D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> ScissorRects;

	protected:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		RasterizerStageState* m_pSisterState;
	};
}

#endif