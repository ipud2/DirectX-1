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

	// ����GeometryPtr
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
	DSStateConfig.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;		// ʹ����պ���Զ����󷽣���������հѱ�����嵲��
	pEffect->SetDepthStencilState( Renderer::Get()->CreateDepthStencilState( &DSStateConfig ) );

	/*
		���Ǵ�����պ��Ǵ�����һ����
		Ȼ�����������Դ����ⲿ�ĽǶ���������
		Ҳ����˵���ⲿ�������е������ζ���˳ʱ��
		Ȼ�����ǵĳ���ʵ������պ��ڲ�
		Ҳ����˵���ǿ�������պеı���
		������ﷴתһ�»���˳��
		Ҳ���Խ���դ��״̬��Ϊ���޳�
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