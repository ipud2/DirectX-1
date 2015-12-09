#include "PCH.h"
#include "Skybox.h"
#include "DepthStencilStateConfig.h"
#include "RasterizerStateConfig.h"
#include "GeometryGenerator.h"

using namespace Sand;

Skybox::Skybox( std::wstring& filename , int sampler , float Radius /* = 1000.0f */ )
	:m_pMaterial( nullptr ) ,
	m_pGeometry( nullptr ) ,
	m_iSamplerState( sampler ) ,
	m_Radius( Radius )
{
	GetRootNode()->SetName( std::wstring( L"Skybox" ) );

	// 创建GeometryPtr
	m_pGeometry = GeometryGenerator::GeneratorSkyBox( 30 , 30 , Radius );
	m_pGeometry->LoadToBuffer();
	m_pGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_pMaterial = MaterialPtr( new Material );
	RenderEffect* pEffect = new RenderEffect;

	pEffect->SetVertexShader( Renderer::Get()->LoadShader( ST_VERTEX_SHADER ,
														   std::wstring( L"Skybox.hlsl" ) ,
														   std::wstring( L"VSMain" ) ,
														   std::wstring( L"vs_5_0" ) ) );
	pEffect->SetPixelShader( Renderer::Get()->LoadShader( ST_PIXEL_SHADER ,
														  std::wstring( L"Skybox.hlsl" ) ,
														  std::wstring( L"PSMain" ) ,
														  std::wstring( L"ps_5_0" ) ) );

	DepthStencilStateConfig DSStateConfig;
	DSStateConfig.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;		// 使得天空盒永远在最后方，不至于天空把别的物体挡了
	pEffect->SetDepthStencilState( Renderer::Get()->CreateDepthStencilState( &DSStateConfig ) );

	/*
		我们创建天空盒是创建了一个球
		然而，我们是以从球外部的角度来创建的
		也就是说从外部看，所有的三角形都是顺时针
		然而我们的场景实际在天空盒内部
		也就是说我们看到的天空盒的背面
		因此这里反转一下环绕顺序
		也可以将光栅化状态设为不剔除
	*/
	RasterizerStateConfig RSConfig;
	RSConfig.FrontCounterClockwise = true;
	pEffect->SetRasterizerState( Renderer::Get()->CreateRasterizerState( &RSConfig ) );

	m_pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	m_pSkybox = new Entity;
	m_pSkybox->GetRenderableRef().SetMaterial( m_pMaterial );
	m_pSkybox->GetRenderableRef().SetGeometry( m_pGeometry );
	m_pSkybox->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.0f , 0.0f );

	GetRootNode()->AttachChild( m_pSkybox );

	ResourceProxyPtr SkyboxTexture = Renderer::Get()->LoadTexture( filename );
	ShaderResourceParameterWriter* pShaderResourceWriter = m_pMaterial->Parameters.GetShaderResourceParameterWriter( L"SkyboxTexture" );
	pShaderResourceWriter->SetValue( SkyboxTexture );

	SamplerParameterWriter* pSamplerParameterWriter = m_pMaterial->Parameters.GetSamplerParameterWriter( L"SkyboxSampler" );
	pSamplerParameterWriter->SetValue( sampler );
}

Skybox::~Skybox()
{

}