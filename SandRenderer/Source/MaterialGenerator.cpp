#include "PCH.h"
#include "MaterialGenerator.h"
#include "RasterizerStateConfig.h"
#include "DepthStencilStateConfig.h"
#include "BlendStateConfig.h"
#include "SamplerStateConfig.h"

using namespace Sand;

MaterialGenerator::MaterialGenerator()
{

}

MaterialPtr MaterialGenerator::GenerateWireFrame( Renderer& renderer )
{
	MaterialPtr pMaterial = MaterialPtr( new Material() );

	RenderEffect* pEffect = new RenderEffect;

	pEffect->SetVertexShader( renderer.LoadShader( ST_VERTEX_SHADER , std::wstring( L"BasicTessellation.hlsl" ) , std::wstring( L"VSMAIN" ) , std::wstring( L"vs_5_0" ) ) );

	pEffect->SetHullShader( renderer.LoadShader( ST_HULL_SHADER , std::wstring( L"BasicTessellation.hlsl" ) , std::wstring( L"HSMAIN" ) , std::wstring( L"hs_5_0" ) ) );

	pEffect->SetDomainShader( renderer.LoadShader( ST_DOMAIN_SHADER , std::wstring( L"BasicTessellation.hlsl" ) , std::wstring( L"DSMAIN" ) , std::wstring( L"ds_5_0" ) ) );

	pEffect->SetPixelShader( renderer.LoadShader( ST_PIXEL_SHADER , std::wstring( L"BasicTessellation.hlsl" ) , std::wstring( L"PSMAIN" ) , std::wstring( L"ps_5_0" ) ) );

	RasterizerStateConfig RS;
	RS.FillMode = D3D11_FILL_WIREFRAME;

	pEffect->SetRasterizerState( renderer.CreateRasterizerState( &RS ) );

	pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	return pMaterial;
}

MaterialPtr MaterialGenerator::GeneratePhong( Renderer& renderer )
{
	MaterialPtr pMaterial = MaterialPtr( new Material );

	RenderEffect* pEffect = new RenderEffect();

	pEffect->SetVertexShader( renderer.LoadShader( ST_VERTEX_SHADER , std::wstring( L"PhongingShading.hlsl" ) , std::wstring( L"VSMAIN" ) , std::wstring( L"vs_5_0" ) ) );

	pEffect->SetPixelShader( renderer.LoadShader( ST_PIXEL_SHADER , std::wstring( L"PhongShading.hlsl" ) , std::wstring( L"PSMAIN" ) , std::wstring( L"ps_5_0" ) ) );

	pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	return pMaterial;
}

MaterialPtr MaterialGenerator::GenerateSolidColor( Renderer& renderer )
{
	MaterialPtr pMaterial = MaterialPtr( new Material );

	RenderEffect* pEffect = new RenderEffect;

	pEffect->SetVertexShader( renderer.LoadShader( ST_VERTEX_SHADER , std::wstring( L"VertexColor.hlsl" ) , std::wstring( L"VSMAIN" ) , std::wstring( L"vs_5_0" ) ) );

	pEffect->SetPixelShader( renderer.LoadShader( ST_PIXEL_SHADER , std::wstring( L"VertexColor.hlsl" ) , std::wstring( L"PSMAIN" ) , std::wstring( L"ps_5_0" ) ) );

	DepthStencilStateConfig DS;
	DS.DepthEnable = false;

	pEffect->SetDepthStencilState( renderer.CreateDepthStencilState( &DS ) );

	pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	return pMaterial;
}

MaterialPtr MaterialGenerator::GenerateFromFile( Renderer& renderer , std::wstring& filename , unsigned int shaders )
{
	MaterialPtr pMaterial = MaterialPtr( new Material );

	RenderEffect* pEffect = new RenderEffect;

	if( shaders & SM_VERTEX_SHADER )
	{
		pEffect->SetVertexShader( renderer.LoadShader( ST_VERTEX_SHADER , filename , std::wstring( L"VSMAIN" ) , std::wstring( L"vs_5_0" ) , false ) );
	}

	if( shaders & SM_HULL_SHADER )
	{
		pEffect->SetHullShader( renderer.LoadShader( ST_HULL_SHADER , filename , std::wstring( L"HSMAIN" ) , std::wstring( L"hs_5_0" ) , false ) );
	}

	if( shaders & SM_DOMAIN_SHADER )
	{
		pEffect->SetDomainShader( renderer.LoadShader( ST_DOMAIN_SHADER , filename , std::wstring( L"DSMAIN" ) , std::wstring( L"ds_5_0" ) , false ) );
	}

	if( shaders & SM_GEOMETRY_SHADER )
	{
		pEffect->SetGeometryShader( renderer.LoadShader( ST_GEOMETRY_SHADER , filename , std::wstring( L"GSMAIN" ) , std::wstring( L"gs_5_0" ) , false ) );
	}


	if( shaders & SM_PIXEL_SHADER )
	{
		pEffect->SetPixelShader( renderer.LoadShader( ST_PIXEL_SHADER , filename , std::wstring( L"PSMAIN" ) , std::wstring( L"ps_5_0" ) , false ) );
	}

	if( shaders & SM_COMPUTE_SHADER )
	{
		pEffect->SetComputeShader( renderer.LoadShader( ST_COMPUTE_SHADER , filename , std::wstring( L"CSMAIN" ) , std::wstring( L"cs_5_0" ) , false ) );
	}

	pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	return pMaterial;
}

MaterialPtr MaterialGenerator::GenerateTexMaterial( Renderer& renderer )
{
	MaterialPtr pMaterial = MaterialPtr( new Material );

	RenderEffect* pEffect = new RenderEffect;

	pEffect->SetVertexShader( renderer.LoadShader( ST_VERTEX_SHADER , std::wstring( L"AlphaTestTexture.hlsl" ) , std::wstring( L"VSMAIN" ) , std::wstring( L"vs_5_0" ) ) );

	pEffect->SetPixelShader( renderer.LoadShader( ST_PIXEL_SHADER , std::wstring( L"AlphaTestTexture.hlsl" ) , std::wstring( L"PSMAIN" ) , std::wstring( L"ps_5_0" ) ) );

	// blend state config
	BlendStateConfig BlendConfig;
	BlendConfig.AlphaToCoverageEnable = false;
	BlendConfig.IndependentBlendEnable = false;
	for( int i = 0; i < 8; i++ )
	{
		BlendConfig.RenderTarget[i].BlendEnable = true;
		BlendConfig.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		BlendConfig.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BlendConfig.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BlendConfig.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendConfig.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		BlendConfig.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
		BlendConfig.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	pEffect->SetBlendState( renderer.CreateBlendState( &BlendConfig ) );

	pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;


	ResourceProxyPtr ColorTexture = renderer.LoadTexture( L"EyeOfHorus_128.png" );
	ShaderResourceParameterWriter* pShaderResourceParameterWriter = pMaterial->Parameters.GetShaderResourceParameterWriter( L"ColorTexture" );
	pShaderResourceParameterWriter->SetValue( ColorTexture );


	// 创建采样器对象
	SamplerStateConfig SamplerConfigure;
	SamplerConfigure.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerConfigure.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerConfigure.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerConfigure.MaxAnisotropy = 0;

	int LinearSampler = renderer.CreateSamplerState( &SamplerConfigure );
	SamplerParameterWriter* pSamplerParameterWriter = pMaterial->Parameters.GetSamplerParameterWriter( L"LinearSampler" );
	pSamplerParameterWriter->SetValue( LinearSampler );

	return pMaterial;
}