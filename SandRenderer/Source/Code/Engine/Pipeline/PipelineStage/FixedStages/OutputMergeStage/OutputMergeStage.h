#ifndef OutputMergeStage_h
#define OutputMergeState_h

#include "OutputMergeStageState.h"

namespace Sand
{
	class OutputMergeStage
	{
	public:
		OutputMergeStage();
		virtual ~OutputMergeStage();

		void ClearCurrentState();
		void ClearDesiredState();
		void ApplyDesiredState( ID3D11DeviceContext* pContext );
		void ApplyDesiredRenderTargetStates( ID3D11DeviceContext* pContext );
		void ApplyDesiredBlendAndDepthStencilStates( ID3D11DeviceContext* pContext );

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );

		const OutputMergeStageState& GetCurrentState() const;

		OutputMergeStageState DesiredState;

	protected:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		OutputMergeStageState CurrentState;

		friend class Renderer;
	};
};
#endif