#ifndef InputAssemblerStage_h
#define InputAssemblerStage_h

#include "PCH.h"
#include "InputAssemblerState.h"

namespace Sand
{
	class InputAssemblerStage
	{
	public:
		InputAssemblerStage();
		virtual ~InputAssemblerStage();

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );

		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredState( ID3D11DeviceContext* pContext );

		const InputAssemblerState& GetCurrentState() const;

		// ���ǿ���ֱ�Ӷ�DesiredState�������ã�Ȼ�����ApplyDesiredState
		InputAssemblerState DesiredState;

	protected:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		InputAssemblerState CurrentState;
	};
}

#endif