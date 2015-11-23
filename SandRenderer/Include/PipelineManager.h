#ifndef PipelineManager_h
#define PipelineManager_h

#include "Resource.h"

#include "RasterizerStage.h"
#include "OutputMergeStage.h"
#include "InputAssemblerStage.h"

#include "Vector4f.h"
#include "ShaderStructure.h"

#include "ShaderStage.h"

#include "VertexStage.h"
#include "HullStage.h"
#include "DomainStage.h"
#include "GeometryStage.h"
#include "PixelStage.h"
#include "ComputeStage.h"

namespace Sand
{
	/*
		该类用于管理管线的各个阶段
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
		// Qualifier: 重置render target view 和 depth stencil view中的值
		// Parameter: Vector4f & color
		// Parameter: float depth
		// Parameter: UINT stencil
		//************************************
		void ClearBuffers( Vector4f& color , float depth = 1.0f , UINT stencil = 0 );


		void SaveTextureScreenShot( int ID , std::wstring filename );

		//************************************
		// Method:    MapResource
		// FullName:  Sand::PipelineManager::MapResource
		// Access:    public 
		// Returns:   void
		// Qualifier: 获取包含subresource资源的指针，并且禁止GPU访问资源，SubResource表示子资源的索引，0表示最顶层
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
		// Qualifier: 使指向SubResource资源的指针无效，并恢复GPU对于资源的存取能力
		// Parameter: Resource * pSandResource
		// Parameter: UINT SubResource
		//************************************
		void UnMapResource( Resource* pSandResource , UINT SubResource );


		// ------------------------Bind Resource To Shader Stage-----------------------------
		/*
			将资源的ID设置到指定Shader阶段的相应资源的指定slot
			由于各个shader阶段将会监视各类资源的各个slot上对应资源的ID是否有变化（保存的是ID）
			从而达到将资源绑定到shader阶段的作用
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