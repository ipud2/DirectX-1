#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/DomainStage.h"
#include "Engine/Render/DXGI/Renderer.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/DomainShader.h"

using namespace Sand;

DomainStage::DomainStage()
{

}

DomainStage::~DomainStage()
{

}

ShaderType DomainStage::GetType()
{
	return ST_DOMAIN_SHADER;
}

void DomainStage::BindConstantBuffers( ID3D11DeviceContext* pContext )
{
	pContext->DSSetConstantBuffers( DesiredState.ConstantBuffers.GetStartSlot() , DesiredState.ConstantBuffers.GetRange() , DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void DomainStage::BindSamplerStates( ID3D11DeviceContext* pContext )
{
	pContext->DSSetSamplers( DesiredState.SamplerStates.GetStartSlot() , DesiredState.SamplerStates.GetRange() , DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void DomainStage::BindShaderResourceViews( ID3D11DeviceContext* pContext )
{
	pContext->DSSetShaderResources( DesiredState.ShaderResourceViews.GetStartSlot() , DesiredState.ShaderResourceViews.GetRange() , DesiredState.ShaderResourceViews.GetFirstSlotLocation() );
}

void DomainStage::BindUnorderedAccessViews( ID3D11DeviceContext* pContext )
{
	// 不支持
}

void DomainStage::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	// 获取相应的Shader对象
	int ID = DesiredState.ShaderProgramID.GetState();

	Shader* pShader = Renderer::Get()->GetShader( ID );

	ID3D11DomainShader* pDomainShader = nullptr;

	if( pShader )
	{
		pDomainShader = reinterpret_cast< DomainShader* >( pShader )->m_pDomainShader;
	}

	pContext->DSSetShader( pDomainShader , nullptr , 0 );
}