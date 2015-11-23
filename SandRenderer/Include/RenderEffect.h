#ifndef RenderEffect_h
#define RenderEffect_h

#include "Shader.h"

namespace Sand
{
	class PipelineManager;
	class IParameterManager;

	class RenderEffect
	{
	public:
		RenderEffect();
		virtual ~RenderEffect();

		void SetVertexShader( int index );
		void SetHullShader( int index );
		void SetDomainShader( int index );
		void SetGeometryShader( int index );
		void SetPixelShader( int index );
		void SetComputeShader( int index );

		int GetVertexShader();
		int GetHullShader();
		int GetDomainShader();
		int GetGeometryShader();
		int GetPixelShader();
		int GetComputeShader();

		void ConfigurePipeline( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

		void SetBlendState( int index );
		void SetRasterizerState( int index );
		void SetDepthStencilState( int index );
		void SetStencilRef( unsigned int StencilRef );

	protected:
		int m_iBlendState;
		int m_iDepthStencilState;
		int m_iRasterizerState;
		UINT m_uStencilRef;

	protected:
		// 用于保存shader的index
		int m_aiIndcies[6];
		// 为每个阶段保存一个shader对象
		Shader* m_apShaders[6];

		std::vector<RenderParameter*> m_ConstantBuffers;

	protected:
		void UpdateConstantBufferList();
	};
}
#endif