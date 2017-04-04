#include <Engine/PCH.h>
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/Stages/ShaderStage/HullStage.h"
#include "Engine/Render/DXGI/Renderer.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/HullShader.h"

using namespace Sand;

HullStage::HullStage()
{

}

HullStage::~HullStage()
{

}

ShaderType HullStage::GetType()
{
	return ST_HULL_SHADER;
}

void HullStage::BindConstantBuffers( ID3D11DeviceContext* pContext )
{
	pContext->HSSetConstantBuffers( DesiredState.ConstantBuffers.GetStartSlot() , DesiredState.ConstantBuffers.GetRange() , DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void HullStage::BindSamplerStates( ID3D11DeviceContext* pContext )
{
	pContext->HSSetSamplers( DesiredState.SamplerStates.GetStartSlot() , DesiredState.SamplerStates.GetRange() , DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void HullStage::BindShaderResourceViews( ID3D11DeviceContext* pContext )
{
	pContext->HSSetShaderResources( DesiredState.ShaderResourceViews.GetStartSlot() , DesiredState.ShaderResourceViews.GetRange() , DesiredState.ShaderResourceViews.GetFirstSlotLocation() );
}

void HullStage::BindUnorderedAccessViews( ID3D11DeviceContext* pContext )
{
	// 不支持
}

void HullStage::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	// 获取相应的Shader对象

	int ID = DesiredState.ShaderProgramID.GetState();

	Shader* pShader = Renderer::Get()->GetShader( ID );

	ID3D11HullShader* pHullShader = nullptr;

	if( pShader )
	{
		pHullShader = reinterpret_cast< HullShader* >( pShader )->m_pHullShader;
	}

	pContext->HSSetShader( pHullShader , nullptr , 0 );
}