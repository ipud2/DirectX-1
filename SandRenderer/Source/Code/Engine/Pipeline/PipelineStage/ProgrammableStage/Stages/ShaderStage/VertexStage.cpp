#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/VertexStage.h"
#include "Engine/Render/DXGI/Renderer.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/VertexShader.h"

using namespace Sand;

VertexStage::VertexStage()
{

}

VertexStage::~VertexStage()
{

}

ShaderType VertexStage::GetType()
{
	return ST_VERTEX_SHADER;
}

void VertexStage::BindConstantBuffers( ID3D11DeviceContext* pContext )
{
	pContext->VSSetConstantBuffers( DesiredState.ConstantBuffers.GetStartSlot() , DesiredState.ConstantBuffers.GetRange() , DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void VertexStage::BindSamplerStates( ID3D11DeviceContext* pContext )
{
	pContext->VSSetSamplers( DesiredState.SamplerStates.GetStartSlot() , DesiredState.SamplerStates.GetRange() , DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void VertexStage::BindShaderResourceViews( ID3D11DeviceContext* pContext )
{
	pContext->VSSetShaderResources( DesiredState.ShaderResourceViews.GetStartSlot() , DesiredState.ShaderResourceViews.GetRange() , DesiredState.ShaderResourceViews.GetFirstSlotLocation() );
}

void VertexStage::BindUnorderedAccessViews( ID3D11DeviceContext* pContext )
{
	// 不支持
}

void VertexStage::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	// 获取相应的Shader对象
	int ID = DesiredState.ShaderProgramID.GetState();

	Shader* pShader = Renderer::Get()->GetShader( ID );

	ID3D11VertexShader* pVertexShader = nullptr;

	if( pShader )
	{
		pVertexShader = reinterpret_cast< VertexShader* >( pShader )->m_pVertexShader;
	}

	pContext->VSSetShader( pVertexShader , nullptr , 0 );
}