#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineManager.h"

#include "Engine/Resource/ResourceView/ShaderResoruceView.h"
#include "Engine/Resource/ResourceView/DepthStencilView.h"
#include "Engine/Resource/ResourceView/RenderTargetView.h"
#include "Engine/Resource/ResourceView/UnorderedAccessView.h"

#include <wincodec.h>
#include <sstream>

#include "DirectXTK/Inc/ScreenGrab.h"		// 包含了SaveWICTextureToFile(...)

#include "Engine/Utility/Log.h"

#include "Engine/Parameter/Parameters/Object/ConstantBufferParameter.h"
#include "Engine/Parameter/Parameters/Object/ShaderResourceParameter.h"
#include "Engine/Parameter/Parameters/Object/UnorderedAccessParameter.h"
#include "Engine/Parameter/Parameters/Object/SamplerParameter.h"

#include <d3d9.h>
#pragma comment(lib , "d3d9.lib")

using namespace Sand;

PipelineManager::PipelineManager()
{
	ShaderStages[ST_VERTEX_SHADER] = &VertexShaderStage;
	ShaderStages[ST_HULL_SHADER] = &HullShaderStage;
	ShaderStages[ST_DOMAIN_SHADER] = &DomainShaderStage;
	ShaderStages[ST_GEOMETRY_SHADER] = &GeometryShaderStage;
	ShaderStages[ST_PIXEL_SHADER] = &PixelShaderStage;
	ShaderStages[ST_COMPUTE_SHADER] = &ComputeShaderStage;
}

PipelineManager::~PipelineManager()
{
	if( m_pContext ) m_pContext->ClearState();
}

void PipelineManager::SetDeviceContext( DeviceContextComPtr pContext , D3D_FEATURE_LEVEL FeatureLevel )
{
	m_pContext = pContext;
	m_FeatureLevel = FeatureLevel;

	// 可编程阶段SetFeatureLevel
	ShaderStages[ST_VERTEX_SHADER]->SetFeatureLevel( FeatureLevel );
	ShaderStages[ST_HULL_SHADER]->SetFeatureLevel( FeatureLevel );
	ShaderStages[ST_DOMAIN_SHADER]->SetFeatureLevel( FeatureLevel );
	ShaderStages[ST_GEOMETRY_SHADER]->SetFeatureLevel( FeatureLevel );
	ShaderStages[ST_PIXEL_SHADER]->SetFeatureLevel( FeatureLevel );
	ShaderStages[ST_COMPUTE_SHADER]->SetFeatureLevel( FeatureLevel );

	// 固定阶段调用SetFeatureLevel
	m_RasterizerStage.SetFeatureLevel( FeatureLevel );
	m_OutputMergeStage.SetFeatureLevel( FeatureLevel );
	m_InputAssemblerStage.SetFeatureLevel( FeatureLevel );
}

ID3D11DeviceContext* PipelineManager::GetDeviceContext()
{
	return m_pContext.Get();
}

void Sand::PipelineManager::ClearRenderTargets()
{
	m_OutputMergeStage.ClearDesiredState();
}

void Sand::PipelineManager::ApplyRenderTargets()
{
	// 应用更新后的Render Target View and Depth Stencil View
	m_OutputMergeStage.ApplyDesiredRenderTargetStates( m_pContext.Get() );
}

void Sand::PipelineManager::SaveTextureScreenShot( int ID , std::wstring filename )
{
	ID3D11Resource* pResource = Renderer::Get()->GetResourceByIndex( ID )->GetResource();

	if( pResource )
	{
		static int iScreenNum = 100000;
		iScreenNum++;

		std::wstringstream out;
		out << filename << iScreenNum << L".bmp";

		HRESULT hr = DirectX::SaveWICTextureToFile( m_pContext.Get() , pResource , GUID_ContainerFormatBmp , out.str().c_str() );
		// 未完成，swapchain对应的buffer是最先被保存的资源，索引为0，因此将索引为0的图像保存到file恰好能达到截图的作用
	}
}

void PipelineManager::Draw( RenderEffect& effect , ResourceProxyPtr VB , ResourceProxyPtr IB , int InputLayout , D3D11_PRIMITIVE_TOPOLOGY PrimitiveTye , UINT VertexStride , UINT NumIndices , IParameterManager* pParamManager )
{
	m_InputAssemblerStage.ClearDesiredState();

	m_InputAssemblerStage.DesiredState.PrimitiveTopology.SetState( PrimitiveTye );

	if( VB != nullptr )
	{
		m_InputAssemblerStage.DesiredState.VertexBuffers.SetState( 0 , VB->GetResourceID() );
		m_InputAssemblerStage.DesiredState.VertexBufferOffsets.SetState( 0 , 0 );
		m_InputAssemblerStage.DesiredState.VertexBufferStrides.SetState( 0 , VertexStride );

		m_InputAssemblerStage.DesiredState.InputLayout.SetState( InputLayout );
	}

	if( IB != nullptr )
	{
		m_InputAssemblerStage.DesiredState.IndexBuffers.SetState( IB->GetResourceID() );
		m_InputAssemblerStage.DesiredState.IndexBufferFormat.SetState( DXGI_FORMAT_R32_UINT );
	}

	m_InputAssemblerStage.ApplyDesiredState( m_pContext.Get() );

	ClearPipelineResource();
	effect.ConfigurePipeline( this , pParamManager );
	ApplyPipelineResource();

	m_pContext->DrawIndexed( NumIndices , 0 , 0 );
}

void PipelineManager::ClearPipelineResource()
{
	VertexShaderStage.ClearDesiredState();
	HullShaderStage.ClearDesiredState();
	DomainShaderStage.ClearDesiredState();
	GeometryShaderStage.ClearDesiredState();
	PixelShaderStage.ClearDesiredState();
	ComputeShaderStage.ClearDesiredState();
}

void PipelineManager::BindConstantBufferResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager )
{
	// 首先判断参数是否为nullptr
	if( pRenderParameter != nullptr )
	{
		// 判断类型是否相符
		if( pRenderParameter->GetParameterType() == PT_CONSTANT_BUFFER )
		{
			// 强制转换为ConstantBufferParameter，以便我们可以调用GetValue获取资源的IDS
			ConstantBufferParameter* pConstantBufferParameter = reinterpret_cast< ConstantBufferParameter* >( pRenderParameter );
			int ID = pConstantBufferParameter->GetResourceID();

			ID3D11Buffer* pConstanBuffer = nullptr;

			if( ID >= 0 )
			{
				// ID >= 0 ： 资源存在
				
				// 获取资源
				Resource* pResource = Renderer::Get()->GetResourceByIndex( ID );

				if( pResource )
				{
					pConstanBuffer = ( ID3D11Buffer* )pResource->GetResource();
				}
			}

			ShaderStages[type]->DesiredState.ConstantBuffers.SetState( slot , pConstanBuffer );
		}
	}
}

void PipelineManager::BindSamplerResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager )
{
	if( pRenderParameter != nullptr )
	{
		if( pRenderParameter->GetParameterType() == PT_SAMPLER )
		{
			SamplerParameter* pSamplerParameter = reinterpret_cast< SamplerParameter* >( pRenderParameter );
			int index = pSamplerParameter->GetSamplerResourceID();

			ID3D11SamplerState* pSamplerState = nullptr;

			if( index >= 0 )
			{
				SamplerStateComPtr pState = Renderer::Get()->GetSamplerState( index );
				pSamplerState = pState.Get();
			}

			ShaderStages[type]->DesiredState.SamplerStates.SetState( slot , pSamplerState );
		}
	}
}

void PipelineManager::BindShaderResourceViewResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager )
{
	// 首先判断参数是否为nullptr
	if( pRenderParameter != nullptr )
	{
		// 判断类型是否相符
		if( pRenderParameter->GetParameterType() == PT_SHADER_RESOURCE )
		{
			// 强制转换为ConstantBufferParameter，以便我们可以调用GetValue获取资源的ID
			ShaderResourceParameter* pShaderResoruceParameter = reinterpret_cast< ShaderResourceParameter* >( pRenderParameter );
			int ID = pShaderResoruceParameter->GetResourceViewID();

			ShaderResourceView& pShaderResourceView = Renderer::Get()->GetShaderResourceViewByIndex( ID );

			ShaderStages[type]->DesiredState.ShaderResourceViews.SetState( slot , pShaderResourceView.Get() );
		}
	}
}

void PipelineManager::BindUnorderedAccessViewResourceToShaderStage( ShaderType type , RenderParameter* pRenderParameter , UINT slot , IParameterManager* pParameterManager )
{
	// 首先判断参数是否为nullptr
	if( pRenderParameter != nullptr )
	{
		// 判断类型是否相符
		if( pRenderParameter->GetParameterType() == PT_UNORDERED_ACCESS )
		{
			// 强制转换为ConstantBufferParameter，以便我们可以调用GetValue获取资源的IDS
			UnorderedAccessParameter* pUnorderedAccessParameter = reinterpret_cast< UnorderedAccessParameter* >( pRenderParameter );
			int ID = pUnorderedAccessParameter->GetResourceViewID();

			UnorderedAccessView& pUnorderedAccessView = Renderer::Get()->GetUnorderedAccessViewByIndex( ID );

			ShaderStages[type]->DesiredState.UnorderedAccessViews.SetState( slot , pUnorderedAccessView.Get() );
		}
	}
}

void PipelineManager::BindShader( ShaderType type , int ID , IParameterManager* pParameterManager )
{
	ShaderStages[type]->DesiredState.ShaderProgramID.SetState( ID );

	Shader* pShader = Renderer::Get()->GetShader( ID );

	if( pShader )
	{
		if( pShader->GetType() == type )
		{
			// 将该shader所有的绑定资源全部设置到相应shaderStage的slot上
			pShader->GetShaderReflection()->BindShaderInputResourceToShaderStage( type , this , pParameterManager );
		}
	}
}

void PipelineManager::UnMapResource( Resource* pSandResource , UINT SubResource )
{
	if( nullptr == pSandResource )
	{
		Log::Get().Error( L"Trying to Unmap a subresource doesn't exist!!" );
	}

	ID3D11Resource* pResource = pSandResource->GetResource();

	if( nullptr == pResource )
	{
		Log::Get().Error( L"Trying to unmap a subresource that has no native resource on it!!" );
	}

	m_pContext->Unmap( pResource , SubResource );
}

void PipelineManager::MapResource( Resource* pSandResource , UINT SubResource , D3D11_MAP MapType , UINT MapFlag , D3D11_MAPPED_SUBRESOURCE* pMappedResource )
{
	// 初始化MappedResource
	pMappedResource->pData = NULL;
	pMappedResource->DepthPitch = 0;
	pMappedResource->RowPitch = 0;

	if( pSandResource == nullptr )
	{
		Log::Get().Error( L"trying to map a subresource doesn't exist!" );
	}

	ID3D11Resource* pResource = pSandResource->GetResource();

	if( nullptr == pResource )
	{
		Log::Get().Error( L"Trying to map a subresource that has no native resource in it!! " );
	}

	HRESULT hr = m_pContext->Map( pResource , SubResource , MapType , MapFlag , pMappedResource );
	if( FAILED( hr ) )
	{
		Log::Get().Error( L"Failed to map resource!" );
	}
}

void PipelineManager::ClearBuffers( Vector4f& color , float depth , UINT stencil )
{
	ID3D11RenderTargetView* pRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
	ID3D11DepthStencilState* pDepthStencilView = nullptr;

	int count = m_OutputMergeStage.GetCurrentState().GetRenderTargetCount();

	// --------------------------Clear Render Target View--------------------------------
	for( int i = 0; i < count; i++ )
	{
		// 获取每个render target view的index
		int index = m_OutputMergeStage.GetCurrentState().RenderTargetViews.GetState( i );
		// 获取RenderTargetView对象
		RenderTargetView& RTV = Renderer::Get()->GetRenderTargetViewByIndex( index );

		pRenderTargetViews[i] = RTV.GetRenderTargetView();

		// 清除后的颜色
		const float clearColors[] = { color.x , color.y , color.z , color.w };
		m_pContext->ClearRenderTargetView( pRenderTargetViews[i] , clearColors );
	}


	// 获取depth stencil view的index
	UINT index = m_OutputMergeStage.GetCurrentState().DepthStencilViews.GetState();
	// 获取DepthStencilView对象
	DepthStencilView& DSV = Renderer::Get()->GetDepthStencilViewByIndex( index );

	m_pContext->ClearDepthStencilView( DSV.Get() , D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , depth , stencil );
}

void PipelineManager::ClearDepthStencilBuffer( float depth /* = 1.0f  */ , UINT stencil /* = 0 */ )
{
	// 获取DepthStencilView对象
	DepthStencilView& DSV = Renderer::Get()->GetDepthStencilViewByIndex( m_OutputMergeStage.GetCurrentState().DepthStencilViews.GetState() );

	m_pContext->ClearDepthStencilView( DSV.Get() , D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , depth , stencil );
}

RasterizerStage& PipelineManager::GetRasterizerStageRef()
{
	return m_RasterizerStage;
}

OutputMergeStage& PipelineManager::GetOutputMergeStageRef()
{
	return m_OutputMergeStage;
}

void PipelineManager::ApplyPipelineResource()
{
	VertexShaderStage.ApplyDesiredState( m_pContext.Get() );
	HullShaderStage.ApplyDesiredState( m_pContext.Get() );
	DomainShaderStage.ApplyDesiredState( m_pContext.Get() );
	GeometryShaderStage.ApplyDesiredState( m_pContext.Get() );
	PixelShaderStage.ApplyDesiredState( m_pContext.Get() );
	ComputeShaderStage.ApplyDesiredState( m_pContext.Get() );

	m_RasterizerStage.ApplyDesiredState( m_pContext.Get() );
	m_OutputMergeStage.ApplyDesiredBlendAndDepthStencilStates( m_pContext.Get() );
}

InputAssemblerStage& PipelineManager::GetInputAssemblerStageRef()
{
	return m_InputAssemblerStage;
}

void PipelineManager::ApplyInputResource()
{
	m_InputAssemblerStage.ApplyDesiredState( m_pContext.Get() );
}

void PipelineManager::DrawIndexed( int IndexCount , int StartIndex , int VertexOffset )
{
	m_pContext->DrawIndexed( IndexCount , StartIndex , VertexOffset );
}