#ifndef VertexStage_h
#define VertexStage_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/ShaderStage.h"

namespace Sand
{
	class VertexStage : public ShaderStage
	{
	public:
		VertexStage();
		virtual ~VertexStage();

	protected:
		ShaderType GetType();

		// 将资源绑定到相应的Shader阶段
		virtual void BindShaderProgram( ID3D11DeviceContext* pContext );
		virtual void BindConstantBuffers( ID3D11DeviceContext* pContext );
		virtual void BindSamplerStates( ID3D11DeviceContext* pContext );
		virtual void BindShaderResourceViews( ID3D11DeviceContext* pContext );
		virtual void BindUnorderedAccessViews( ID3D11DeviceContext* pContext );

	};
}
#endif