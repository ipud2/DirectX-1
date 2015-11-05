#ifndef RasterizerStage_h
#define RaterizerStage_h

#include "RasterizerStageState.h"

namespace Sand
{
	class RasterizerStage
	{
	public:
		RasterizerStage();
		virtual ~RasterizerStage();

		void ClearCurrentState();
		void ClearDesiredState();
		void ApplyDesiredState( ID3D11DeviceContext* pContext );

		void SetFeatureLevel( D3D_FEATURE_LEVEL level );

		const RasterizerStageState& GetCurrentState() const;

		RasterizerStageState DesiredState;

	protected:
		RasterizerStageState CurrentState;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		friend class Renderer;
	};
}

#endif