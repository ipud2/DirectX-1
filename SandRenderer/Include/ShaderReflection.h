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
			Ϊÿ��Constant Buffer����һ������������Դ
			Ȼ��Constant Buffer���������¼����Դ��ID
			Ȼ��Ϊ����Դ�����Ϣ
		*/
		void InitConstantBufferParameter( IParameterManager* pParameterManager );

		/*
			����Shader��ConstantBuffer
		*/
		void UpdateConstantBufferParameter( PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

		/*
			��shader�е���Դ��
			Textrue2d ,
			ConstantBuffer , 
			Sampler ,
			and so on
		*/
		void BindShaderInputResourceToShaderStage( ShaderType type , PipelineManager* pPipelineManager , IParameterManager* pParameterManager );

	public:
		D3D11_SHADER_DESC ShaderDesc;													// shader��������
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> InputSignatureParameterDesc;		// �����ֶ�����
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> OutputSignatureParameterDesc;		// ����ֶ�����
		std::vector<ConstantBufferDesc> ConstantBuffers;								// CBuffer����
		std::vector<ShaderInputBindDesc> ResourceBindDesc;								// ����Դ������
	};
};
#endif