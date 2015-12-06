#include "App.h"
#include "Log.h"

#include <sstream>

#include "SwapChainConfig.h"
#include "Texture2DConfig.h"
#include "RasterizerStateConfig.h"
#include "BufferConfig.h"
#include "MaterialGenerator.h"

#include "IParameterManager.h"

#include "SamplerStateConfig.h"

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
	m_pEntity = nullptr;

	m_pGeometry = nullptr;
	m_pMaterial = nullptr;
	m_pBoxSurfaceProperty = nullptr;

	m_pLight = nullptr;
	m_pCameras = nullptr;

	m_pWoodCrateTexture = nullptr;
	m_iLinearSampler = -1;

	m_pSkyBox = nullptr;

	m_TexTransform.MakeIdentity();
}

App::~App()
{

}

bool App::ConfigureEngineComponents()
{
	// 创建Win32RenderWindow对象，用于创建窗口，并设置窗口信息
	m_pWindow = new Win32RenderWindow;
	m_pWindow->SetSize( 800 , 600 );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// 创建窗口

	// 配置渲染器
	m_pRenderer = new Renderer;

	// 创建Device & DeviceContext
	// 配置默认的Rasterizer State 和 Blend State and DepthStencilState
	if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_HARDWARE , D3D_FEATURE_LEVEL_11_0 ) )
	{
		Log::Get().Write( L"无法创建硬件设备，尝试创建reference设备" );

		if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_REFERENCE , D3D_FEATURE_LEVEL_11_0 ) )
		{
			// 指定窗口的显示状态， 这里指定为隐藏
			ShowWindow( m_pWindow->GetHandle() , SW_HIDE );
			MessageBox( m_pWindow->GetHandle() , L"无法创建硬件/软件Direct3D 11设备，程序将会终止" , L"SandRenderer" , MB_ICONEXCLAMATION | MB_SYSTEMMODAL );
			RequestTermination();

			return false;
		}

		m_pTimer->SetFixedTimeStep( 1.0f / 10.0f );
	}

	m_pTimer->SetFixedTimeStep( 1.0f / 400.0f );

	// 创建交换链
	SwapChainConfig config;
	config.SetWidth( m_pWindow->GetWidth() );
	config.SetHeight( m_pWindow->GetHeight() );
	config.SetOutputWindow( m_pWindow->GetHandle() );
	m_iSwapChain = m_pRenderer->CreateSwapChain( &config );
	m_pWindow->SetSwapChain( m_iSwapChain );

	// 保存一份渲染目标索引的拷贝
	m_pRenderTarget = m_pRenderer->GetSwapChainResource( m_iSwapChain );

	// 创建深度缓存，并为其生成深度模板视图
	Texture2DConfig DepthConfig;
	DepthConfig.SetDepthBuffer( m_pWindow->GetWidth() , m_pWindow->GetHeight() );
	m_pDepthStencilTarget = m_pRenderer->CreateTexture2D( &DepthConfig , nullptr );

	// 设置render target view 和 depth stencil view
	m_pRenderer->GetPipelineManagerRef()->ClearRenderTargets();
	m_pRenderer->GetPipelineManagerRef()->GetOutputMergeStageRef().DesiredState.RenderTargetViews.SetState( 0 , m_pRenderTarget->GetRenderTargetViewID() );
	m_pRenderer->GetPipelineManagerRef()->GetOutputMergeStageRef().DesiredState.DepthStencilViews.SetState( m_pDepthStencilTarget->GetDepthStencilViewID() );
	m_pRenderer->GetPipelineManagerRef()->ApplyRenderTargets();


	// 设置Viewport
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
	// create GeometryPtr Object
	m_pGeometry = GeometryLoader::LoadOBJ( std::wstring( L"Cube.OBJ" ) );
	m_pGeometry->LoadToBuffer();
	m_pGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_TexTransform.MakeIdentity();
	m_pRenderer->GetParameterManagerRef()->SetMatrixParameterData( std::wstring( L"TexTransform" ) , &m_TexTransform );

	// create the material for use by the entities
	CreateMaterial();

	// -----------------------------SurfaceProperty---------------------------------
	m_pBoxSurfaceProperty = new BasicSurfaceProperty;
	m_pBoxSurfaceProperty->SetSurfaceProperty( Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) ,
											   Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) ,
											   Vector4f( 0.6f , 0.6f , 0.6f , 16.0f ) );

	// --------------------------------create render view object--------------------------------------------
	m_pRenderView = new ViewPerspective( *m_pRenderer , m_pRenderTarget , m_pDepthStencilTarget );
	m_pRenderView->SetBackColor( Vector4f( 0.69f , 0.77f , 0.87f , 1.0f ) );

	// ---------------------------------------Camera----------------------------------------------
	m_pCameras = new Camera();
	// set camera position , so we can generate view matrix
	m_pCameras->Spatial().SetTranslation( Vector3f( 0.0f , 0.0f , -4.0f ) );
	// set render view into camera
	m_pCameras->SetRenderView( m_pRenderView );
	// set project matrix params , so we can generate project matrix
	m_pCameras->SetPerspectiveProjectionParams( 1.0f , 100.0f , ( float )m_pWindow->GetWidth() / ( float )m_pWindow->GetHeight() , static_cast< float >( SAND_PI ) / 4.0f );

	// ---------------------------------Directional Light---------------------------------
	m_pLight = new DirectionalLight( 2 );
	m_pLight->SetDirectionalLight( Vector4f( 0.25f , 0.25f , 0.25f , 0.25f ) ,
								   Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) ,
								   Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) ,
								   Vector4f( 0.707f , -0.707f , 0.0f , 1.0f ) ,
								   0 );
	m_pLight->SetDirectionalLight( Vector4f( 0.2f , 0.2f , 0.2f , 1.0f ) ,
								   Vector4f( 1.4f , 1.4f , 1.4f , 1.0f ) ,
								   Vector4f( 0.3f , 0.3f , 0.3f , 16.0f ) ,
								   Vector4f( -0.707f , 0.0f , 0.707f , 1.0f ) ,
								   1 );

	// --------------------------------Actor and Entity------------------------------
	m_pActor = new Actor;
	m_pActor->GetRootNode()->SetName( std::wstring( L"Cube" ) );
	m_pEntity = new Entity;
	m_pEntity->GetRenderableRef().SetGeometry( m_pGeometry );
	m_pEntity->GetRenderableRef().SetMaterial( m_pMaterial );
	m_pEntity->GetRenderableRef().SetSurfaceProperty( m_pBoxSurfaceProperty );
	// relative to parent node
	m_pEntity->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.0f , 0.0f );

	// add to root node
	m_pActor->GetRootNode()->AttachChild( m_pEntity );

	// -----------------------------SkyBox-----------------------
	m_pSkyBox = new Skybox( std::wstring( L"GrassCube.dds" ) , m_iLinearSampler );

	// -------------------Add to Scene-------------------
	m_pScene->AddActor( m_pActor );
	m_pScene->AddActor( m_pSkyBox );
	m_pScene->AddCamera( m_pCameras );
	m_pScene->AddLight( m_pLight );
}

void App::Update()
{
	m_pTimer->Update();

	// rotate node
	Matrix3f rotation;
	rotation.RotationY( m_pTimer->Elapsed() * 0.1f );
	m_pActor->GetRootNode()->GetTransformRef().GetRotationRef() *= rotation;

	m_pScene->Update( m_pTimer->Elapsed() );
	m_pScene->Render( m_pRenderer );

	m_pRenderer->Present( m_pWindow->GetSwapChain() );
}

void App::Shutdown()
{
	SAFE_DELETE( m_pEntity );

	std::wstringstream out;
	out << L"Max FPS: " << m_pTimer->MaxFramerate();
	Log::Get().Write( out.str().c_str() );
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
	return std::wstring( L"BoxWithTexture" );
}

void App::CreateMaterial()
{
	m_pMaterial = MaterialPtr( new Material );

	RenderEffect* pEffect = new RenderEffect;

	pEffect->SetVertexShader( m_pRenderer->LoadShader(	ST_VERTEX_SHADER , 
														std::wstring( L"BasicTexture.hlsl" ) , 
														std::wstring( L"VSMain" ) , 
														std::wstring( L"vs_5_0" ) ) );

	pEffect->SetPixelShader( m_pRenderer->LoadShader(	ST_PIXEL_SHADER ,
														std::wstring( L"BasicTexture.hlsl" ) ,
														std::wstring( L"PSMain" ) ,
														std::wstring( L"ps_5_0" ) ) );

	m_pMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	// --------------------------------set texture-----------------------------
	m_pWoodCrateTexture = m_pRenderer->LoadTexture( L"WoodCrate01.dds" );
	ShaderResourceParameterWriter* pShaderResourceWriter = m_pMaterial->Parameters.GetShaderResourceParameterWriter( L"WoodCrateTexture" );
	pShaderResourceWriter->SetValue( m_pWoodCrateTexture );

	SamplerStateConfig config;
	m_iLinearSampler = m_pRenderer->CreateSamplerState( &config );
	SamplerParameterWriter* pSamplerWriter = m_pMaterial->Parameters.GetSamplerParameterWriter( L"LinearSampler" );
	pSamplerWriter->SetValue( m_iLinearSampler );
}