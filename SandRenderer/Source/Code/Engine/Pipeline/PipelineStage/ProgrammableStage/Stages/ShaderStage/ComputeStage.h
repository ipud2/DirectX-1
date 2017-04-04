#ifndef ComputeStage_h
#define ComputeStage_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/ShaderStage.h"

namespace Sand
{
	class ComputeStage : public ShaderStage
	{
	public:
		ComputeStage();
		virtual ~ComputeStage();

	protected:
		ShaderType GetType();

		// ����Դ�󶨵���Ӧ��Shader�׶�
		virtual void BindShaderProgram( ID3D11DeviceContext* pContext );
		virtual void BindConstantBuffers( ID3D11DeviceContext* pContext );
		virtual void BindSamplerStates( ID3D11DeviceContext* pContext );
		virtual void BindShaderResourceViews( ID3D11DeviceContext* pContext );
		virtual void BindUnorderedAccessViews( ID3D11DeviceContext* pContext );

	};
};
#endif