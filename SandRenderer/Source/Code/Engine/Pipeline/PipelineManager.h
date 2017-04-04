#ifndef PipelineManager_h
#define PipelineManager_h

#include "Engine/Resource/Resource.h"

#include "Engine/Pipeline/PipelineStage/FixedStages/RasterizerStage/RasterizerStage.h"
#include "Engine/Pipeline/PipelineStage/FixedStages/OutputMergeStage/OutputMergeStage.h"
#include "Engine/Pipeline/PipelineStage/FixedStages/InputAssemblerStage/InputAssemblerStage.h"

#include "Engine/Math/Vector4f.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Reflection/ShaderStructure.h"

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/ShaderStage.h"

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/VertexStage.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/HullStage.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/DomainStage.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/GeometryStage.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/PixelStage.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/ComputeStage.h"

#include "Engine/Effect/RenderEffect.h"

namespace Sand
{
	/*
		�������ڹ�����ߵĸ����׶�
	*/
	class PipelineManager
	{
	public:
		PipelineManager();
		~PipelineManager();

		void SetDeviceContext( DeviceContextComPtr pContext , D3D_FEATURE_LEVEL FeatureLevel );
		ID3D11DeviceContext* GetDeviceContext();
		

		void ClearRenderTargets();
		void ApplyRenderTargets();

		//************************************
		// Method:    ClearBuffers
		// FullName:  Sand::PipelineManager::ClearBuffers
		// Access:    public 
		// Returns:   void
		// Qualifier: ����render target view �� depth stencil view�е�ֵ
		// Parameter: Vector4f & color
		// Parameter: float depth
		// Parameter: UINT stencil
		//************************************
		void ClearBuffers( Vector4f& color , float depth = 1.0f , UINT stencil = 0 );

		void ClearDepthStencilBuffer( float depth = 1.0f , UINT stencil = 0 );

		void SaveTextureScreenShot( int ID , std::wstring filename );

		//************************************
		// Method:    MapResource
		// FullName:  Sand::PipelineManager::MapResource
		// Access:    public 
		// Returns:   void
		// Qualifier: ��ȡ����subresource��Դ��ָ�룬���ҽ�ֹGPU������Դ��SubResource��ʾ����Դ��������0��ʾ���
		// Parameter: Resource * pResource
		// Parameter: UINT SubResource
		// Parameter: D3D11_MAP MapType
		// Parameter: UINT MapFlag
		// Parameter: D3D11_MAPPED_SUBRESOURCE * pMappedResource
		//************************************
		void MapResource( Resource* pResource , UINT SubResource , D3D11_MAP MapType , UINT MapFlag , D3D11_MAPPED_SUBRESOURCE* pMappedResource );

		//************************************
		// Method:    UnMapResource
		// FullName:  Sand::PipelineManager::UnMapResource
		// Access:    public 
		// Returns:   void
		// Qualifier: ʹָ��SubResource��Դ��ָ����Ч�����ָ�GPU������Դ�Ĵ�ȡ����
		// Parameter: Resource * pSandResource
		// Parameter: UINT SubResource
		//************************************
		void UnMapResource( Resource* pSandResource , UINT SubResource );


		// ------------------------Bind Resource To Shader Stage-----------------------------
		/*
			����Դ��ID���õ�ָ��Shader�׶ε���Ӧ��Դ��ָ��slot
			���ڸ���shader�׶ν�����Ӹ�����Դ�ĸ���slot�϶�Ӧ��Դ��ID�Ƿ��б仯���������ID��
			�Ӷ��ﵽ����Դ�󶨵�shader�׶ε�����
		*/
		void BindConstantBufferResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager );
		void BindSamplerResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager );
		void BindShaderResourceViewResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager );
		void BindUnorderedAccessViewResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager );

		void BindShader( ShaderType type , int ID , IParameterManager* pParameterManager );

		
		// --------------------------------------------------------------------------------------
		void ApplyPipelineResource();

		void ClearPipelineResource();

		void ApplyInputResource();

		// --------------------------Draw----------------------------
		void DrawIndexed( int IndexCount , int StartIndex , int VertexOffset );
		void Draw( RenderEffect& effect , ResourceProxyPtr VB , ResourceProxyPtr IB , int InputLayout , D3D11_PRIMITIVE_TOPOLOGY PrimitiveTye , UINT VertexStride , UINT NumIndices , IParameterManager* pParamManager );

	public:
		D3D_FEATURE_LEVEL m_FeatureLevel;

		DeviceContextComPtr m_pContext;

	protected:
		RasterizerStage m_RasterizerStage;
		OutputMergeStage m_OutputMergeStage;
		InputAssemblerStage m_InputAssemblerStage;

	public:
		RasterizerStage& GetRasterizerStageRef();
		OutputMergeStage& GetOutputMergeStageRef();
		InputAssemblerStage& GetInputAssemblerStageRef();

	public:
		ShaderStage* ShaderStages[6];

		VertexStage VertexShaderStage;
		HullStage HullShaderStage;
		DomainStage DomainShaderStage;
		GeometryStage GeometryShaderStage;
		PixelStage PixelShaderStage;
		ComputeStage ComputeShaderStage;
	};
}

#endif