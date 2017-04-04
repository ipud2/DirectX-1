#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/GeometryStage.h"
#include "Engine/Render/DXGI/Renderer.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/GeometryShader.h"

using namespace Sand;

GeometryStage::GeometryStage()
{

}

GeometryStage::~GeometryStage()
{

}

ShaderType GeometryStage::GetType()
{
	return ST_GEOMETRY_SHADER;
}

void GeometryStage::BindConstantBuffers( ID3D11DeviceContext* pContext )
{
	pContext->GSSetConstantBuffers( DesiredState.ConstantBuffers.GetStartSlot() , DesiredState.ConstantBuffers.GetRange() , DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void GeometryStage::BindSamplerStates( ID3D11DeviceContext* pContext )
{
	pContext->GSSetSamplers( DesiredState.SamplerStates.GetStartSlot() , DesiredState.SamplerStates.GetRange() , DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void GeometryStage::BindShaderResourceViews( ID3D11DeviceContext* pContext )
{
	pContext->GSSetShaderResources( DesiredState.ShaderResourceViews.GetStartSlot() , DesiredState.ShaderResourceViews.GetRange() , DesiredState.ShaderResourceViews.GetFirstSlotLocation() );
}

void GeometryStage::BindUnorderedAccessViews( ID3D11DeviceContext* pContext )
{
	// 不支持
}

void GeometryStage::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	// 获取相应的Shader对象
	int ID = DesiredState.ShaderProgramID.GetState();

	Shader* pShader = Renderer::Get()->GetShader( ID );

	ID3D11GeometryShader* pGeometryShader = nullptr;

	if( pShader )
	{
		pGeometryShader = reinterpret_cast< GeometryShader* >( pShader )->m_pGeometryShader;
	}

	pContext->GSSetShader( pGeometryShader , nullptr , 0 );
}