#include "PCH.h"
#include "ComputeStage.h"
#include "Renderer.h"
#include "ComputeShader.h"

using namespace Sand;

ComputeStage::ComputeStage()
{

}

ComputeStage::~ComputeStage()
{

}

ShaderType ComputeStage::GetType()
{
	return ST_COMPUTE_SHADER;
}

void ComputeStage::BindConstantBuffers( ID3D11DeviceContext* pContext )
{
	pContext->CSSetConstantBuffers( DesiredState.ConstantBuffers.GetStartSlot() , DesiredState.ConstantBuffers.GetRange() , DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void ComputeStage::BindSamplerStates( ID3D11DeviceContext* pContext )
{
	pContext->CSSetSamplers( DesiredState.SamplerStates.GetStartSlot() , DesiredState.SamplerStates.GetRange() , DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void ComputeStage::BindShaderResourceViews( ID3D11DeviceContext* pContext )
{
	pContext->CSSetShaderResources( DesiredState.ShaderResourceViews.GetStartSlot() , DesiredState.ShaderResourceViews.GetRange() , DesiredState.ShaderResourceViews.GetFirstSlotLocation() );
}

void ComputeStage::BindUnorderedAccessViews( ID3D11DeviceContext* pContext )
{
	// UnorderedAccessView��Ҫ���µ�StartSlot��UAVInitialCount��Ҫ���µ�StartSlot��Сֵ
	unsigned int minStartSlot = min( DesiredState.UnorderedAccessViews.GetStartSlot() , DesiredState.UAVInitialCounts.GetStartSlot() );
	
	// ����������EndSlot
	unsigned int maxEndSlot = max( DesiredState.UnorderedAccessViews.GetEndSlot() , DesiredState.UAVInitialCounts.GetEndSlot() );

	pContext->CSSetUnorderedAccessViews( minStartSlot , maxEndSlot - minStartSlot + 1 , DesiredState.UnorderedAccessViews.GetSlotLocation( minStartSlot ) , DesiredState.UAVInitialCounts.GetSlotLocation( minStartSlot ) );
}

void ComputeStage::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	// ��ȡ��Ӧ��Shader����
	int ID = DesiredState.ShaderProgramID.GetState();

	Shader* pShader = Renderer::Get()->GetShader( ID );

	ID3D11ComputeShader* pComputeShader = nullptr;

	if( pShader )
	{
		pComputeShader = reinterpret_cast< ComputeShader* >( pShader )->m_pComputeShader;
	}

	pContext->CSSetShader( pComputeShader , nullptr , 0 );
}