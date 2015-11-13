#ifndef ShaderReflection_h
#define ShaderReflection_h

#include "ShaderStructure.h"

namespace Sand
{
	class PipelineManager;
	class IParameterManager;

	class ShaderReflection
	{
	public:
		ShaderReflection();
		~ShaderReflection();

		/*
			为每个Constant Buffer创建一个常量缓存资源
			然后Constant Buffer参数对象记录该资源的ID
			然后为该资源填充信息
		*/
		void InitConstantBufferParameter( IParameterManager* pParameterManager );

		/*
			更新Shader的ConstantBuffer
		*/
		void UpdateConstantBufferParameter( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

		/*
			绑定shader中的资源：
			Textrue2d ,
			ConstantBuffer , 
			Sampler ,
			and so on
		*/
		void BindShaderInputResourceToShaderStage( ShaderType type , PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

	public:
		D3D11_SHADER_DESC ShaderDesc;													// shader顶层描述
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> InputSignatureParameterDesc;		// 输入字段描述
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> OutputSignatureParameterDesc;		// 输出字段描述
		std::vector<ConstantBufferDesc> ConstantBuffers;								// CBuffer描述
		std::vector<ShaderInputBindDesc> ResourceBindDesc;								// 绑定资源的描述
	};
};
#endif