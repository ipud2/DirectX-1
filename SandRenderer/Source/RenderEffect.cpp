#include "PCH.h"
#include "RenderEffect.h"
#include "Renderer.h"
#include "Log.h"
#include "PipelineManager.h"
#include "IParameterManager.h"
#include "ConstantBufferParameterWriter.h"
#include "ConstantBuffer.h"

using namespace Sand;

RenderEffect::RenderEffect()
{
	// ����Ĭ��ֵ
	for( int i = 0; i < 6; i++ )
	{
		m_aiIndcies[i] = -1;
		m_apShaders[i] = nullptr;
	}

	m_iBlendState = -1;
	m_iDepthStencilState = -1;
	m_iRasterizerState = -1;
	m_uStencilRef = 0;
}

RenderEffect::~RenderEffect()
{

}

void RenderEffect::SetVertexShader( int index )
{
	m_aiIndcies[ST_VERTEX_SHADER] = index;
	m_apShaders[ST_VERTEX_SHADER] = Renderer::Get()->GetShader( index );

	if( m_apShaders[ST_VERTEX_SHADER] != nullptr )
	{
		// ���shader�������Ƿ����ΪVertexShader
		if( m_apShaders[ST_VERTEX_SHADER]->GetType() != ST_VERTEX_SHADER )
		{
			Log::Get().Write( L"��ͼ���Ƕ�����ɫ���󶨵�������ɫ����" );
		}
	}

	// ����������Vertex Shader�����ConstantBuffer List���ܻ��иı�
	UpdateConstantBufferList();
}

void RenderEffect::SetHullShader( int index )
{
	m_aiIndcies[ST_HULL_SHADER] = index;
	m_apShaders[ST_HULL_SHADER] = Renderer::Get()->GetShader( index );

	if( nullptr != m_apShaders[ST_HULL_SHADER] )
	{
		if( m_apShaders[ST_HULL_SHADER]->GetType() != ST_HULL_SHADER )
		{
			Log::Get().Write( L"��ͼ����HullShader�󶨵�HullShader" );
		}
	}

	// �����������µ�Hull Shader�� ����ConstantBuffer List�п��ܻᷢ���ı�
	UpdateConstantBufferList();
}

void RenderEffect::SetDomainShader( int index )
{
	m_aiIndcies[ST_DOMAIN_SHADER] = index;
	m_apShaders[ST_DOMAIN_SHADER] = Renderer::Get()->GetShader( index );

	if( nullptr != m_apShaders[ST_DOMAIN_SHADER] )
	{
		if( m_apShaders[ST_DOMAIN_SHADER]->GetType() != ST_DOMAIN_SHADER )
		{
			Log::Get().Write( L"��ͼ����DomainShader�󶨵�DomainShader��" );
		}
	}

	// �����������µ�DomainShader ,����ConstantBuffer List�п��ܻᷢ���ı�
	UpdateConstantBufferList();
}

void RenderEffect::SetGeometryShader( int index )
{
	m_aiIndcies[ST_GEOMETRY_SHADER] = index;
	m_apShaders[ST_GEOMETRY_SHADER] = Renderer::Get()->GetShader( index );

	if( nullptr != m_apShaders[ST_GEOMETRY_SHADER] )
	{
		if( m_apShaders[ST_GEOMETRY_SHADER]->GetType() != ST_GEOMETRY_SHADER )
		{
			Log::Get().Write( L"��ͼ����GeometryShader�󶨵�GeometryShader��" );
		}
	}
	
	// �����������µ�Geometry Shader������ConstantBuffer List�п��ܻᷢ���ı�
	UpdateConstantBufferList();
}

void RenderEffect::SetPixelShader( int index )
{
	m_aiIndcies[ST_PIXEL_SHADER] = index;
	m_apShaders[ST_PIXEL_SHADER] = Renderer::Get()->GetShader( index );

	if( nullptr != m_apShaders[ST_PIXEL_SHADER] )
	{
		if( m_apShaders[ST_PIXEL_SHADER]->GetType() != ST_PIXEL_SHADER )
		{
			Log::Get().Write( L"��ͼ����PixelShader�󶨵�PixelShader��" );
		}
	}

	// �����������µ�Pixel Shader,����ConstantBuffer List�п��ܻᷢ���仯
	UpdateConstantBufferList();
}

void RenderEffect::SetComputeShader( int index )
{
	m_aiIndcies[ST_COMPUTE_SHADER] = index;
	m_apShaders[ST_COMPUTE_SHADER] = Renderer::Get()->GetShader( index );

	if( nullptr != m_apShaders[ST_COMPUTE_SHADER] )
	{
		if( m_apShaders[ST_COMPUTE_SHADER]->GetType() != ST_COMPUTE_SHADER )
		{
			Log::Get().Write( L"��ͼ����ComputeShader�󶨵�ComputeShader��" );
		}
	}

	// �����������µ�Compute Shader������Constant Buffer List�п��ܻᷢ���仯
	UpdateConstantBufferList();
}

int RenderEffect::GetVertexShader()
{
	return m_aiIndcies[ST_VERTEX_SHADER];
}

int RenderEffect::GetHullShader()
{
	return m_aiIndcies[ST_HULL_SHADER];
}

int RenderEffect::GetDomainShader()
{
	return m_aiIndcies[ST_DOMAIN_SHADER];
}

int RenderEffect::GetGeometryShader()
{
	return m_aiIndcies[ST_GEOMETRY_SHADER];
}

int RenderEffect::GetPixelShader()
{
	return m_aiIndcies[ST_PIXEL_SHADER];
}

int RenderEffect::GetComputeShader()
{
	return m_aiIndcies[ST_COMPUTE_SHADER];
}

void RenderEffect::ConfigurePipeline( PipelineManager* pPipelineManager , IParameterManager* pParameterManager )
{
	if( -1 != m_iBlendState )
	{
		pPipelineManager->GetOutputMergeStageRef().DesiredState.BlendStates.SetState( m_iBlendState );
	}
	else
	{
		// ����Ĭ�ϵ�״̬
		pPipelineManager->GetOutputMergeStageRef().DesiredState.BlendStates.SetState( 0 );
	}

	if( -1 != m_iRasterizerState )
	{
		pPipelineManager->GetRasterizerStageRef().DesiredState.RasterizerStates.SetState( m_iRasterizerState );
	}
	else
	{
		pPipelineManager->GetRasterizerStageRef().DesiredState.RasterizerStates.SetState( 0 );
	}

	if( -1 != m_iDepthStencilState )
	{
		pPipelineManager->GetOutputMergeStageRef().DesiredState.DepthStencilStates.SetState( m_iDepthStencilState );
		pPipelineManager->GetOutputMergeStageRef().DesiredState.StencilRef.SetState( m_uStencilRef );
	}
	else
	{
		pPipelineManager->GetOutputMergeStageRef().DesiredState.DepthStencilStates.SetState( 0 );
	}

	// ����ConstantBuffer
	for( auto pParameter : m_ConstantBuffers )
	{
		ConstantBuffer* cbuffer = Renderer::Get()->GetConstantBufferByIndex( pParameterManager->GetConstantBufferParameterData( pParameter ) );
		cbuffer->EvaluateElements( pPipelineManager , pParameterManager );
	}

	pPipelineManager->BindShader( ST_VERTEX_SHADER ,	m_aiIndcies[ST_VERTEX_SHADER] ,		pParameterManager );
	pPipelineManager->BindShader( ST_HULL_SHADER ,		m_aiIndcies[ST_HULL_SHADER] ,		pParameterManager );
	pPipelineManager->BindShader( ST_DOMAIN_SHADER ,	m_aiIndcies[ST_DOMAIN_SHADER] ,		pParameterManager );
	pPipelineManager->BindShader( ST_GEOMETRY_SHADER ,	m_aiIndcies[ST_GEOMETRY_SHADER] ,	pParameterManager );
	pPipelineManager->BindShader( ST_PIXEL_SHADER ,		m_aiIndcies[ST_PIXEL_SHADER] ,		pParameterManager );
	pPipelineManager->BindShader( ST_COMPUTE_SHADER ,	m_aiIndcies[ST_COMPUTE_SHADER] ,	pParameterManager );
}

void RenderEffect::UpdateConstantBufferList()
{
	m_ConstantBuffers.empty();

	for( int stage = 0; stage < 6; stage++ )
	{
		Shader* pShader = m_apShaders[stage];

		if( pShader != nullptr )
		{
			ShaderReflection* pReflection = pShader->GetShaderReflection();

			for( unsigned int i = 0; i < pReflection->ConstantBuffers.size(); i++ )
			{
				RenderParameter* pParameter = pReflection->ConstantBuffers[i].pParamRef;

				// �жϸò����Ƿ��Ѿ�����
				bool bAlreadThere = false;
				for( auto pExistParameter : m_ConstantBuffers )
				{
					if( pExistParameter == pParameter )
					{
						bAlreadThere = true;
						break;
					}
				}


				// �����ڣ�����ӵ��б���
				if( false == bAlreadThere )
				{
					m_ConstantBuffers.push_back( pParameter );
				}
				else
				{
					Log::Get().Write( L"��constant buffer�����Ѿ����ڣ�����!!" );
				}
			}
		}
	}
}

void RenderEffect::SetBlendState( int index )
{
	m_iBlendState = index;
}

void RenderEffect::SetRasterizerState( int index )
{
	m_iRasterizerState = index;
}

void RenderEffect::SetDepthStencilState( int index )
{
	m_iDepthStencilState = index;
}

void RenderEffect::SetStencilRef( unsigned int StencilRef )
{
	m_uStencilRef = StencilRef;
}