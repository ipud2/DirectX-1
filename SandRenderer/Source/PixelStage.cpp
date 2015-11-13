#include "PCH.h"
#include "PixelStage.h"
#include "PixelShader.h"
#include "Renderer.h"

using namespace Sand;

PixelStage::PixelStage()
{

}

PixelStage::~PixelStage()
{

}

ShaderType PixelStage::GetType()
{
	return ST_PIXEL_SHADER;
}

void PixelStage::BindConstantBuffers( ID3D11DeviceContext* pContext )
{
	pContext->PSSetConstantBuffers( DesiredState.ConstantBuffers.GetStartSlot() , DesiredState.ConstantBuffers.GetRange() , DesiredState.ConstantBuffers.GetFirstSlotLocation() );
}

void PixelStage::BindSamplerStates( ID3D11DeviceContext* pContext )
{
	pContext->PSSetSamplers( DesiredState.SamplerStates.GetStartSlot() , DesiredState.SamplerStates.GetRange() , DesiredState.SamplerStates.GetFirstSlotLocation() );
}

void PixelStage::BindShaderResourceViews( ID3D11DeviceContext* pContext )
{
	pContext->PSSetShaderResources( DesiredState.ShaderResourceViews.GetStartSlot() , DesiredState.ShaderResourceViews.GetRange() , DesiredState.ShaderResourceViews.GetFirstSlotLocation() );
}

void PixelStage::BindUnorderedAccessViews( ID3D11DeviceContext* pContext )
{
	
}

void PixelStage::BindShaderProgram( ID3D11DeviceContext* pContext )
{
	// 获取相应的Shader对象

	int ID = DesiredState.ShaderProgramID.GetState();

	Shader* pShader = Renderer::Get()->GetShader( ID );

	ID3D11PixelShader* pPixelShader = nullptr;

	if( pShader )
	{
		pPixelShader = reinterpret_cast< PixelShader* >( pShader )->m_pPixelShader;
	}

	pContext->PSSetShader( pPixelShader , nullptr , 0 );
}