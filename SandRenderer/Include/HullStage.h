#ifndef HullStage_h
#define HullStage_h

#include "ShaderStage.h"

namespace Sand
{
	class HullStage : public ShaderStage
	{
	public:
		HullStage();
		virtual ~HullStage();

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