#include "App.h"
#include "Log.h"

#include <sstream>

#include "SwapChainConfig.h"
#include "Texture2DConfig.h"
#include "RasterizerStateConfig.h"
#include "BufferConfig.h"
#include "EffectGenerator.h"

#include "IParameterManager.h"

#include "SamplerStateConfig.h"

#include "GeometryGenerator.h"

#include "EventFrameStart.h"

using namespace Sand;

App AppInstance;

App::App()
{
	m_pWindow = nullptr;
	m_pRenderer = nullptr;

	m_iSwapChain = -1;

	m_pRenderTarget = nullptr;
	m_pDepthStencilTarget = nullptr;

	m_pRenderView = nullptr;

	m_pActor = nullptr;
	m_pBox = nullptr;

	m_pBoxGeometry = nullptr;
	m_pBoxShaderEffect = nullptr;
	m_pBoxMaterial = nullptr;

	m_pGridShaderEffect = nullptr;

	m_pLight = nullptr;
	m_pCameras = nullptr;

	m_pBrickTexture = nullptr;
	m_iLinearSampler = -1;

	m_pSkyBox = nullptr;

	m_TexTransform.MakeIdentity();
}

App::~App()
{

}

bool App::ConfigureEngineComponents()
{
	// ����Win32RenderWindow�������ڴ������ڣ������ô�����Ϣ
	m_pWindow = new Win32RenderWindow;
	m_pWindow->SetSize( 1366 , 768 );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// ��������

	// ������Ⱦ��
	m_pRenderer = new Renderer;

	// ����Device & DeviceContext
	// ����Ĭ�ϵ�Rasterizer State �� Blend State and DepthStencilState
	if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_HARDWARE , D3D_FEATURE_LEVEL_11_0 ) )
	{
		Log::Get().Write( L"�޷�����Ӳ���豸�����Դ���reference�豸" );

		if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_REFERENCE , D3D_FEATURE_LEVEL_11_0 ) )
		{
			// ָ�����ڵ���ʾ״̬�� ����ָ��Ϊ����
			ShowWindow( m_pWindow->GetHandle() , SW_HIDE );
			MessageBox( m_pWindow->GetHandle() , L"�޷�����Ӳ��/���Direct3D 11�豸�����򽫻���ֹ" , L"SandRenderer" , MB_ICONEXCLAMATION | MB_SYSTEMMODAL );
			RequestTermination();

			return false;
		}
	}

	// ����������
	SwapChainConfig config;
	config.SetWidth( m_pWindow->GetWidth() );
	config.SetHeight( m_pWindow->GetHeight() );
	config.SetOutputWindow( m_pWindow->GetHandle() );
	m_iSwapChain = m_pRenderer->CreateSwapChain( &config );
	m_pWindow->SetSwapChain( m_iSwapChain );

	// ����һ����ȾĿ�������Ŀ���
	m_pRenderTarget = m_pRenderer->GetSwapChainResource( m_iSwapChain );

	// ������Ȼ��棬��Ϊ���������ģ����ͼ
	Texture2DConfig DepthConfig;
	DepthConfig.SetDepthBuffer( m_pWindow->GetWidth() , m_pWindow->GetHeight() );
	m_pDepthStencilTarget = m_pRenderer->CreateTexture2D( &DepthConfig , nullptr );

	// ����render target view �� depth stencil view
	m_pRenderer->GetPipelineManagerRef()->ClearRenderTargets();
	m_pRenderer->GetPipelineManagerRef()->GetOutputMergeStageRef().DesiredState.RenderTargetViews.SetState( 0 , m_pRenderTarget->GetRenderTargetViewID() );
	m_pRenderer->GetPipelineManagerRef()->GetOutputMergeStageRef().DesiredState.DepthStencilViews.SetState( m_pDepthStencilTarget->GetDepthStencilViewID() );
	m_pRenderer->GetPipelineManagerRef()->ApplyRenderTargets();


	// ����Viewport
	D3D11_VIEWPORT view_port;
	view_port.Width = m_pWindow->GetWidth();
	view_port.Height = m_pWindow->GetHeight();
	view_port.TopLeftX = 0.0f;
	view_port.TopLeftY = 0.0f;
	view_port.MinDepth = 0.0f;
	view_port.MaxDepth = 1.0f;


	int view_port_id = m_pRenderer->CreateViewPort( view_port );
	m_pRenderer->GetPipelineManagerRef()->GetRasterizerStageRef().DesiredState.ViewportCount.SetState( 1 );
	m_pRenderer->GetPipelineManagerRef()->GetRasterizerStageRef().DesiredState.Viewports.SetState( 0 , view_port_id );

	return true;
}

void App::ShutdownEngineComponents()
{
	if( m_pRenderer )
	{
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}

	if( m_pWindow )
	{
		m_pWindow->Shutdown();
		delete m_pWindow;
	}
}

void App::Initialize()
{
	// ����BoxͼԪ������
	m_pBoxGeometry = GeometryLoader::LoadOBJWithTexture( std::wstring( L"cube.obj" ) , true );
	m_pBoxGeometry->LoadToBuffer();
	m_pBoxGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	// ����GridͼԪ������
	m_pGridGeometry = GeometryGenerator::GeneratorGrid( 20.0f , 30.0f , 60 , 40 );
	m_pGridGeometry->LoadToBuffer();
	m_pGridGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST );

	// ����CylinderͼԪ������
	m_pCylinderGeometry = GeometryGenerator::GeneratorCylinder( 0.5f , 0.3f , 3.0f , 20 , 20 );
	m_pCylinderGeometry->LoadToBuffer();
	m_pCylinderGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST );

	// ����SphereͼԪ
	m_pSphereGeometry = GeometryGenerator::GeneratorSphere( 20 , 20 , 0.5f );
	m_pSphereGeometry->LoadToBuffer();
	m_pSphereGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_pSkullGeometry = GeometryLoader::LoadOBJWithTexture( std::wstring( L"Skull.obj" ) );
	m_pSkullGeometry->LoadToBuffer();
	m_pSkullGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// create the material for use by the entities
	CreateShaderEffect();

	// -----------------------------SurfaceMaterial---------------------------------
	CreateSurfaceMaterial();

	// --------------------------------create render view object--------------------------------------------
	m_pRenderView = new ViewPerspective( *m_pRenderer , m_pRenderTarget , m_pDepthStencilTarget );
	m_pRenderView->SetBackColor( Vector4f( 0.69f , 0.77f , 0.87f , 1.0f ) );

	// -----------------------------------------Camera----------------------------------------------
	m_pCameras = new MainCamera();
	// enable event listener
	m_pCameras->SetEventManager( &EventManager::Get() );
	// set camera position , so we can generate view matrix
	m_pCameras->Spatial().SetTranslation( Vector3f( 0.0f , 2.0f , -15.0f ) );
	// set render view into camera
	m_pCameras->SetRenderView( m_pRenderView );
	// set project matrix params , so we can generate project matrix
	m_pCameras->SetPerspectiveProjectionParams( 1.0f , 1000.0f , ( float )m_pWindow->GetWidth() / ( float )m_pWindow->GetHeight() , static_cast< float >( SAND_PI ) / 4.0f );

	// ---------------------------------------Light------------------------------------
	m_pLight = new DirectionalLight( 3 );
	m_pLight->SetDirectionalLight( Vector4f( 0.2f , 0.2f , 0.2f , 1.0f ) ,
								   Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) ,
								   Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) ,
								   Vector4f( 0.57735f , -0.57735f , 0.57735f , 1.0f ) ,
								   0 );
	m_pLight->SetDirectionalLight( Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) ,
								   Vector4f( 0.20f , 0.20f , 0.20f , 1.0f ) ,
								   Vector4f( 0.25f , 0.25f , 0.25f , 1.0f ) ,
								   Vector4f( -0.57735f , -0.57735f , 0.57735f , 1.0f ) ,
								   1 );
	m_pLight->SetDirectionalLight( Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) ,
								   Vector4f( 0.20f , 0.20f , 0.20f , 1.0f ) ,
								   Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) ,
								   Vector4f( 0.0f , -0.707f , -0.707f , 1.0f ) ,
								   2 );
	// ----------------------------------Actor and Entity------------------------------
	m_pActor = new Actor;
	
	//
	// Box
	//
	m_pBox = new Entity;
	m_pBox->GetRenderableRef().SetGeometry( m_pBoxGeometry );
	m_pBox->GetRenderableRef().SetEffect( m_pBoxShaderEffect );
	m_pBox->GetRenderableRef().SetMaterial( m_pBoxMaterial );
	m_pBox->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.5f , 0.0f );
	m_pBox->GetTransformRef().GetScaleRef() = Vector3f( 3.0f , 1.0f , 3.0f );
	m_pActor->GetRootNode()->AttachChild( m_pBox );

	//
	// Sphere
	//
	for ( int i = 0; i < 5; i++ )
	{
		m_pSphere[2 * i + 0] = new Entity;
		m_pSphere[2 * i + 0]->GetRenderableRef().SetGeometry( m_pSphereGeometry );
		m_pSphere[2 * i + 0]->GetRenderableRef().SetEffect( m_pSphereShaderEffect );
		m_pSphere[2 * i + 0]->GetRenderableRef().SetMaterial( m_pSphereMaterial );
		m_pSphere[2 * i + 0]->GetTransformRef().GetPositionRef() = Vector3f( -5.0f , 3.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pSphere[2 * i + 0] );

		m_pSphere[2 * i + 1] = new Entity;
		m_pSphere[2 * i + 1]->GetRenderableRef().SetGeometry( m_pSphereGeometry );
		m_pSphere[2 * i + 1]->GetRenderableRef().SetEffect( m_pSphereShaderEffect );
		m_pSphere[2 * i + 1]->GetRenderableRef().SetMaterial( m_pSphereMaterial );
		m_pSphere[2 * i + 1]->GetTransformRef().GetPositionRef() = Vector3f( 5.0f , 3.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pSphere[2 * i + 1] );
	}

	//
	// Grid
	//
	m_pGrid = new Entity;
	m_pGrid->GetRenderableRef().SetGeometry( m_pGridGeometry );
	m_pGrid->GetRenderableRef().SetEffect( m_pGridShaderEffect );
	m_pGrid->GetRenderableRef().SetMaterial( m_pGridMaterial );
	m_pGrid->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.0f , 0.0f );
	m_pActor->GetRootNode()->AttachChild( m_pGrid );
	
	//
	// Cylinder
	//
	for ( int i = 0; i < 5; i++ )
	{
		m_pCylinder[2 * i + 0] = new Entity;
		m_pCylinder[2 * i + 0]->GetRenderableRef().SetGeometry( m_pCylinderGeometry );
		m_pCylinder[2 * i + 0]->GetRenderableRef().SetEffect( m_pCylinderShaderEffect );
		m_pCylinder[2 * i + 0]->GetRenderableRef().SetMaterial( m_pCylinderMaterial );
		m_pCylinder[2 * i + 0]->GetTransformRef().GetPositionRef() = Vector3f( -5.0f , 1.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pCylinder[2 * i + 0] );

		m_pCylinder[2 * i + 1] = new Entity;
		m_pCylinder[2 * i + 1]->GetRenderableRef().SetGeometry( m_pCylinderGeometry );
		m_pCylinder[2 * i + 1]->GetRenderableRef().SetEffect( m_pCylinderShaderEffect );
		m_pCylinder[2 * i + 1]->GetRenderableRef().SetMaterial( m_pCylinderMaterial );
		m_pCylinder[2 * i + 1]->GetTransformRef().GetPositionRef() = Vector3f( 5.0f , 1.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pCylinder[2 * i + 1] );
	}

	m_pSkull = new Entity;
	m_pSkull->GetRenderableRef().SetGeometry( m_pSkullGeometry );
	m_pSkull->GetRenderableRef().SetEffect( m_pSkullShaderEffect );
	m_pSkull->GetRenderableRef().SetMaterial( m_pSkullMaterial );
	m_pSkull->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 1.0f , 0.0f );
	m_pSkull->GetTransformRef().GetScaleRef() = Vector3f( 0.5f , 0.5f , 0.5f );
	m_pActor->GetRootNode()->AttachChild( m_pSkull );

	// ---------------------------------SkyBox----------------------------
	m_pSkyBox = new Skybox( std::wstring( L"SnowCube.dds" ) , m_iLinearSampler );

	// -------------------Add to Scene-------------------
	m_pScene->AddActor( m_pActor );
	m_pScene->AddActor( m_pSkyBox );
	m_pScene->AddCamera( m_pCameras );
	m_pScene->AddLight( m_pLight );
}

void App::Update()
{
	m_pTimer->Update();

	EventManager::Get().ProcessEvent( EventFrameStartPtr( new EventFrameStart( m_pTimer->DeltaTime() ) ) );

	// ----------------����֡��-----------------
	SetFrameRate( m_pWindow->GetHandle() );

	m_pScene->Update( m_pTimer->DeltaTime() );
	m_pScene->Render( m_pRenderer );

	m_pRenderer->Present( m_pWindow->GetSwapChain() );
}

void App::Shutdown()
{
	SAFE_DELETE( m_pBox );
}

void App::TakeScreenShot()
{
	if( m_bSaveScreenShot )
	{
		m_bSaveScreenShot = false;
		m_pRenderer->GetPipelineManagerRef()->SaveTextureScreenShot( 0 , GetName() );
	}
}

bool App::HandleEvent( EventPtr pEvent )
{
	return Application::HandleEvent( pEvent );
}

std::wstring App::GetName()
{
	return std::wstring( L"NormalMap" );
}

void App::CreateShaderEffect()
{
	RenderEffect* pBasicEffect = new RenderEffect;

	pBasicEffect->SetVertexShader( m_pRenderer->LoadShader(	ST_VERTEX_SHADER , 
														std::wstring( L"BasicTexture.hlsl" ) , 
														std::wstring( L"VSMain" ) , 
														std::wstring( L"vs_5_0" ) ) );

	pBasicEffect->SetPixelShader( m_pRenderer->LoadShader(	ST_PIXEL_SHADER ,
														std::wstring( L"BasicTexture.hlsl" ) ,
														std::wstring( L"PSMain" ) ,
														std::wstring( L"ps_5_0" ) ) );

	RenderEffect* pNormalMapEffect = new RenderEffect;

	pNormalMapEffect->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
																std::wstring( L"NormalMap.hlsl" ) ,
																std::wstring( L"VSMain" ) ,
																std::wstring( L"vs_5_0" ) ) );

	pNormalMapEffect->SetPixelShader( m_pRenderer->LoadShader(	ST_PIXEL_SHADER ,
																std::wstring( L"NormalMap.hlsl" ) ,
																std::wstring( L"PSMain" ) ,
																std::wstring( L"ps_5_0" ) ) );

	RenderEffect* pDisplacementMapEffect = new RenderEffect;
	pDisplacementMapEffect->SetVertexShader( m_pRenderer->LoadShader(	ST_VERTEX_SHADER ,
																		std::wstring( L"DisplacementMap.hlsl" ) ,
																		std::wstring( L"VSMain" ) ,
																		std::wstring( L"vs_5_0" ) ) );
	pDisplacementMapEffect->SetHullShader( m_pRenderer->LoadShader( ST_HULL_SHADER ,
																	std::wstring( L"DisplacementMap.hlsl" ) ,
																	std::wstring( L"HSMain" ) ,
																	std::wstring( L"hs_5_0" ) ) );
	pDisplacementMapEffect->SetDomainShader( m_pRenderer->LoadShader(	ST_DOMAIN_SHADER ,
																		std::wstring( L"DisplacementMap.hlsl" ) ,
																		std::wstring( L"DSMain" ) ,
																		std::wstring( L"ds_5_0" ) ) );
	pDisplacementMapEffect->SetPixelShader( m_pRenderer->LoadShader(	ST_PIXEL_SHADER ,
																		std::wstring( L"DisplacementMap.hlsl" ) ,
																		std::wstring( L"PSMain" ) ,
																		std::wstring( L"ps_5_0" ) ) );
	// --------------------------------------------------------------------Box------------------------------------------------------------
	m_pBoxShaderEffect = EffectPtr( new Effect );

	m_pBoxShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pBoxShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pNormalMapEffect;

	MatrixParameterWriter* pMatrixParameterWriter = m_pBoxShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	// ------------------------------------------------------Sphere-------------------------------------------------------------
	m_pSphereShaderEffect = EffectPtr( new Effect );

	m_pSphereShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pSphereShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pNormalMapEffect;

	pMatrixParameterWriter = m_pSphereShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	// ----------------------------------------------------------------Grid-------------------------------------------------------------------------
	m_pGridShaderEffect = EffectPtr( new Effect );

	m_pGridShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pGridShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pDisplacementMapEffect;

	// ����任����
	pMatrixParameterWriter = m_pGridShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.ScaleMatrixXYZ( 6.0f , 8.0f , 1.0f ) );

	// ---------------------------------------------------------------Cylinder-------------------------------------------------------------------
	m_pCylinderShaderEffect = EffectPtr( new Effect );

	m_pCylinderShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pCylinderShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pDisplacementMapEffect;

	pMatrixParameterWriter = m_pCylinderShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	// -------------------------------------------------Skull-----------------------------------------------
	m_pSkullShaderEffect = EffectPtr( new Effect );

	m_pSkullShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pSkullShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pBasicEffect;

	pMatrixParameterWriter = m_pSkullShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );
}

void App::CreateSurfaceMaterial()
{
	m_pBoxMaterial      = new Material( "BoxMaterial.lua" );
	m_pGridMaterial     = new Material( "GridMaterial.lua" );
	m_pCylinderMaterial = new Material( "CylinderMaterial.lua" );
	m_pSphereMaterial   = new Material( "SphereMaterial.lua" );
	m_pSkullMaterial	= new Material( "SkullMaterial.lua" );
}