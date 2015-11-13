#ifndef ShaderStage_h
#define ShaderStage_h

#include "Shader.h"
#include "ShaderStageState.h"

namespace Sand
{
	class ShaderStage
	{
	public:
		ShaderStage();
		virtual ~ShaderStage();

		void SetFeatureLevel( D3D_FEATURE_LEVEL Level );
		
		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredState( ID3D11DeviceContext* pContext );

		virtual ShaderType GetType() = 0;

		// 将资源绑定到相应的Shader阶段
		virtual void BindShaderProgram( ID3D11DeviceContext* pContext ) = 0;
		virtual void BindConstantBuffers( ID3D11DeviceContext* pContext ) = 0;
		virtual void BindSamplerStates( ID3D11DeviceContext* pContext ) = 0;
		virtual void BindShaderResourceViews( ID3D11DeviceContext* pContext ) = 0;
		virtual void BindUnorderedAccessViews( ID3D11DeviceContext* pContext ) = 0;

		ShaderStageState DesiredState;

	protected:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		ShaderStageState CurrentState;
	};
};
#endif