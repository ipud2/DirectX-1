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

#include "ShaderResourceViewConfig.h"

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

	m_iShadowSamplerState = -1;
	m_iTessShadowSamplerState = -1;

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
	m_pWindow->SetSize( 1366 , 768 );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// 创建窗口

	// 配置渲染器
	m_pRenderer = new Renderer;

	// 创建Device & DeviceContext
	// 配置默认的Rasterizer State 和 Blend State and DepthStencilState
	if ( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_HARDWARE , D3D_FEATURE_LEVEL_11_0 ) )
	{
		Log::Get().Write( L"无法创建硬件设备，尝试创建reference设备" );

		if ( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_REFERENCE , D3D_FEATURE_LEVEL_11_0 ) )
		{
			// 指定窗口的显示状态， 这里指定为隐藏
			ShowWindow( m_pWindow->GetHandle() , SW_HIDE );
			MessageBox( m_pWindow->GetHandle() , L"无法创建硬件/软件Direct3D 11设备，程序将会终止" , L"SandRenderer" , MB_ICONEXCLAMATION | MB_SYSTEMMODAL );
			RequestTermination();

			return false;
		}
	}

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
	if ( m_pRenderer )
	{
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}

	if ( m_pWindow )
	{
		m_pWindow->Shutdown();
		delete m_pWindow;
	}
}

void App::Initialize()
{
	// ---------------------Light-----------------------
	m_LightDir[0] = Vector3f( -0.57735f , -0.57735f , 0.57735f );
	m_LightDir[1] = Vector3f( 0.57735f , -0.57735f , 0.57735f );
	m_LightDir[2] = Vector3f( 0.0f , -0.707f , -0.707f );

	// ----------------------Shadow Map---------------------
	m_pShadowMap = new ShadowMap( m_pRenderer , 2048 , 2048 );
	m_pShadowMapView = new ViewShadowMap( *m_pRenderer , m_pShadowMap->GetShadowMap() , 2048 , 2048 );
	
	m_BoundSphereRadius = sqrtf( 10.0f * 10.0f + 15.0f * 15.0f );
	m_pShadowMapCamera = new ShadowMapCamera();
	m_pShadowMapCamera->SetBoundSphereRadius( m_BoundSphereRadius );
	m_pShadowMapCamera->SetRenderView( m_pShadowMapView );
	m_pShadowMapCamera->Spatial().SetTranslation( m_LightDir[0] * -2.0f * m_BoundSphereRadius );
	m_pShadowMapCamera->Orientation().SetLook( m_LightDir[0] );

	// 加载Box图元的数据
	m_pBoxGeometry = GeometryLoader::LoadOBJWithTexture( std::wstring( L"cube.obj" ) , true );
	m_pBoxGeometry->LoadToBuffer();
	m_pBoxGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// 创建Grid图元的数据
	m_pGridGeometry = GeometryGenerator::GeneratorGrid( 20.0f , 30.0f , 60 , 40 );
	m_pGridGeometry->LoadToBuffer();
	m_pGridGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST );

	// 创建Cylinder图元的数据
	m_pCylinderGeometry = GeometryGenerator::GeneratorCylinder( 0.5f , 0.3f , 3.0f , 20 , 20 );
	m_pCylinderGeometry->LoadToBuffer();
	m_pCylinderGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST );

	// 创建Sphere图元
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
								   Vector4f( m_LightDir[0] ) ,
								   0 );
	m_pLight->SetDirectionalLight( Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) ,
								   Vector4f( 0.20f , 0.20f , 0.20f , 1.0f ) ,
								   Vector4f( 0.25f , 0.25f , 0.25f , 1.0f ) ,
								   Vector4f( m_LightDir[1] ) ,
								   1 );
	m_pLight->SetDirectionalLight( Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) ,
								   Vector4f( 0.20f , 0.20f , 0.20f , 1.0f ) ,
								   Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) ,
								   Vector4f( m_LightDir[2] ) ,
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
	m_pScene->AddCamera( m_pShadowMapCamera );
	m_pScene->AddCamera( m_pCameras );
	m_pScene->AddLight( m_pLight );
}

void App::Update()
{
	m_pTimer->Update();

	EventManager::Get().ProcessEvent( EventFrameStartPtr( new EventFrameStart( m_pTimer->DeltaTime() ) ) );

	// ----------------设置帧率-----------------
	SetFrameRate( m_pWindow->GetHandle() );

	if ( GetAsyncKeyState( 'W' ) & 0x8000 )
	{
		m_pCameras->Spatial().MoveForward( m_pTimer->DeltaTime() * 6.0f );
	}
	else if ( GetAsyncKeyState( 'S' ) & 0x8000 )
	{
		m_pCameras->Spatial().MoveBackward( m_pTimer->DeltaTime() * 6.0f );
	}
	else if ( GetAsyncKeyState( 'A' ) & 0x8000 )
	{
		m_pCameras->Spatial().MoveLeft( m_pTimer->DeltaTime() * 6.0f );
	}
	else if ( GetAsyncKeyState( 'D' ) & 0x8000 )
	{
		m_pCameras->Spatial().MoveRight( m_pTimer->DeltaTime() * 6.0f );
	}

	m_pScene->Update( m_pTimer->DeltaTime() );

	// 将MainCamera的ViewPosition传给ShadowMapCamera
	// 必须在Update后，Render之前
	// 因为Update之后，各相机的WorldMatrix已经求出来了，因此可以得到相应的ViewPosition
	m_pShadowMapCamera->SetViewPosition( m_pCameras->GetViewPosition() );

	m_pScene->Render( m_pRenderer );

	m_pRenderer->Present( m_pWindow->GetSwapChain() );
}

void App::Shutdown()
{
	SAFE_DELETE( m_pBox );
}

void App::TakeScreenShot()
{
	if ( m_bSaveScreenShot )
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

void App::OnMouseDown( WPARAM buttonState , int x , int y )
{
	m_LastMousePos.x = x;
	m_LastMousePos.y = y;

	SetCapture( m_pWindow->GetHandle() );
}

void App::OnMouseUp( WPARAM buttonState , int x , int y )
{
	ReleaseCapture();
}

void App::OnMouseMove( WPARAM buttonState , int x , int y )
{
	if ( ( buttonState & MK_LBUTTON ) != 0 )
	{
		float dx = ConvertToRadius( 0.25f * static_cast< float >( x - m_LastMousePos.x ) );
		float dy = ConvertToRadius( 0.25f * static_cast< float >( y - m_LastMousePos.y ) );

		m_pCameras->Orientation().Pitch( dy );
		m_pCameras->Orientation().RotateY( dx );
	}

	m_LastMousePos.x = x;
	m_LastMousePos.y = y;
}

void App::CreateShaderEffect()
{
	//
	// Basic Effect
	//
	RenderEffect* pBasicEffect = new RenderEffect;
	pBasicEffect->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
		std::wstring( L"BasicTexture.hlsl" ) ,
		std::wstring( L"VSMain" ) ,
		std::wstring( L"vs_5_0" ) ) );

	pBasicEffect->SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER ,
		std::wstring( L"BasicTexture.hlsl" ) ,
		std::wstring( L"PSMain" ) ,
		std::wstring( L"ps_5_0" ) ) );

	//
	// Normal Map Effect
	//
	RenderEffect* pNormalMapEffect = new RenderEffect;
	pNormalMapEffect->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
		std::wstring( L"NormalMap.hlsl" ) ,
		std::wstring( L"VSMain" ) ,
		std::wstring( L"vs_5_0" ) ) );

	pNormalMapEffect->SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER ,
		std::wstring( L"NormalMap.hlsl" ) ,
		std::wstring( L"PSMain" ) ,
		std::wstring( L"ps_5_0" ) ) );

	//
	// Displacement Map Effect
	//
	RenderEffect* pDisplacementMapEffect = new RenderEffect;
	pDisplacementMapEffect->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
		std::wstring( L"DisplacementMap.hlsl" ) ,
		std::wstring( L"VSMain" ) ,
		std::wstring( L"vs_5_0" ) ) );
	pDisplacementMapEffect->SetHullShader( m_pRenderer->LoadShader( ST_HULL_SHADER ,
		std::wstring( L"DisplacementMap.hlsl" ) ,
		std::wstring( L"HSMain" ) ,
		std::wstring( L"hs_5_0" ) ) );
	pDisplacementMapEffect->SetDomainShader( m_pRenderer->LoadShader( ST_DOMAIN_SHADER ,
		std::wstring( L"DisplacementMap.hlsl" ) ,
		std::wstring( L"DSMain" ) ,
		std::wstring( L"ds_5_0" ) ) );
	pDisplacementMapEffect->SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER ,
		std::wstring( L"DisplacementMap.hlsl" ) ,
		std::wstring( L"PSMain" ) ,
		std::wstring( L"ps_5_0" ) ) );

	// -------------------------------Shadow Map---------------------------
	RasterizerStateConfig RasterizerStateConfigure;
	RasterizerStateConfigure.FillMode = D3D11_FILL_SOLID;
	RasterizerStateConfigure.CullMode = D3D11_CULL_NONE;
	RasterizerStateConfigure.FrontCounterClockwise = false;
	RasterizerStateConfigure.DepthClipEnable = true;

	RasterizerStateConfigure.DepthBias = 100000;
	RasterizerStateConfigure.DepthBiasClamp = 0.0f;
	RasterizerStateConfigure.SlopeScaledDepthBias = 1.0f;

	m_iRasterizerState = m_pRenderer->CreateRasterizerState( &RasterizerStateConfigure );

	//
	// Tess Shadow Map Effect
	//
	RenderEffect* pTessShadowMapEffect = new RenderEffect;
	pTessShadowMapEffect->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
		std::wstring( L"TessShadowMap.hlsl" ) ,
		std::wstring( L"VSMain" ) ,
		std::wstring( L"vs_5_0" ) ) );
	pTessShadowMapEffect->SetHullShader( m_pRenderer->LoadShader( ST_HULL_SHADER ,
		std::wstring( L"TessShadowMap.hlsl" ) ,
		std::wstring( L"HSMain" ) ,
		std::wstring( L"hs_5_0" ) ) );
	pTessShadowMapEffect->SetDomainShader( m_pRenderer->LoadShader( ST_DOMAIN_SHADER ,
		std::wstring( L"TessShadowMap.hlsl" ) ,
		std::wstring( L"DSMain" ) ,
		std::wstring( L"ds_5_0" ) ) );
	pTessShadowMapEffect->SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER ,
		std::wstring( L"TessShadowMap.hlsl" ) ,
		std::wstring( L"PSMain" ) ,
		std::wstring( L"ps_5_0" ) ) );
	pTessShadowMapEffect->SetRasterizerState( m_iRasterizerState );


	// Shadow Map Effect
	RenderEffect* pShadowMapEffect = new RenderEffect;
	pShadowMapEffect->SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER ,
		std::wstring( L"ShadowMap.hlsl" ) ,
		std::wstring( L"VSMain" ) ,
		std::wstring( L"vs_5_0" ) ) );

	pShadowMapEffect->SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER ,
		std::wstring( L"ShadowMap.hlsl" ) ,
		std::wstring( L"PSMain" ) ,
		std::wstring( L"ps_5_0" ) ) );
	pShadowMapEffect->SetRasterizerState( m_iRasterizerState );
	

	SamplerStateConfig ShadowSamplerStateConfigure;
	ShadowSamplerStateConfigure.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	ShadowSamplerStateConfigure.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	ShadowSamplerStateConfigure.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	ShadowSamplerStateConfigure.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	ShadowSamplerStateConfigure.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	m_iShadowSamplerState = m_pRenderer->CreateSamplerState( &ShadowSamplerStateConfigure );

	SamplerStateConfig TessShadowSamplerStateConfigure;
	TessShadowSamplerStateConfigure.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	TessShadowSamplerStateConfigure.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	TessShadowSamplerStateConfigure.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	TessShadowSamplerStateConfigure.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	TessShadowSamplerStateConfigure.ComparisonFunc = D3D11_COMPARISON_LESS;
	m_iTessShadowSamplerState = m_pRenderer->CreateSamplerState( &TessShadowSamplerStateConfigure );
	// --------------------------------------------------------------------Box------------------------------------------------------------
	m_pBoxShaderEffect = EffectPtr( new Effect );

	m_pBoxShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pBoxShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pNormalMapEffect;
	m_pBoxShaderEffect->Schemes[VT_SHADOW_MAP].bRender = true;
	m_pBoxShaderEffect->Schemes[VT_SHADOW_MAP].pEffect = pShadowMapEffect;

	MatrixParameterWriter* pMatrixParameterWriter = m_pBoxShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	ShaderResourceParameterWriter* pShaderResourceWriter = m_pBoxShaderEffect->ParameterWriters.GetShaderResourceParameterWriter( L"ShadowMap" );
	pShaderResourceWriter->SetValue( m_pShadowMap->GetShadowMap() );

	SamplerParameterWriter* pSamplerWriter = m_pBoxShaderEffect->ParameterWriters.GetSamplerParameterWriter( L"ShadowSampler" );
	pSamplerWriter->SetValue( m_iShadowSamplerState );

	// ------------------------------------------------------Sphere-------------------------------------------------------------
	m_pSphereShaderEffect = EffectPtr( new Effect );

	m_pSphereShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pSphereShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pNormalMapEffect;
	m_pSphereShaderEffect->Schemes[VT_SHADOW_MAP].bRender = true;
	m_pSphereShaderEffect->Schemes[VT_SHADOW_MAP].pEffect = pShadowMapEffect;

	pMatrixParameterWriter = m_pSphereShaderEffect->ParameterWriters.GetMatrixParameterWriter( L"TexTransformMatrix" );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	pShaderResourceWriter = m_pSphereShaderEffect->ParameterWriters.GetShaderResourceParameterWriter( L"ShadowMap" );
	pShaderResourceWriter->SetValue( m_pShadowMap->GetShadowMap() );

	pSamplerWriter = m_pSphereShaderEffect->ParameterWriters.GetSamplerParameterWriter( L"ShadowSampler" );
	pSamplerWriter->SetValue( m_iShadowSamplerState );

	// ----------------------------------------------------------------Grid-------------------------------------------------------------------------
	m_pGridShaderEffect = EffectPtr( new Effect );

	m_pGridShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pGridShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pDisplacementMapEffect;
	m_pGridShaderEffect->Schemes[VT_SHADOW_MAP].bRender = true;
	m_pGridShaderEffect->Schemes[VT_SHADOW_MAP].pEffect = pTessShadowMapEffect;

	// 纹理变换矩阵
	pMatrixParameterWriter = m_pGridShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.ScaleMatrixXYZ( 6.0f , 8.0f , 1.0f ) );

	pShaderResourceWriter = m_pGridShaderEffect->ParameterWriters.GetShaderResourceParameterWriter( L"ShadowMap" );
	pShaderResourceWriter->SetValue( m_pShadowMap->GetShadowMap() );

	pSamplerWriter = m_pGridShaderEffect->ParameterWriters.GetSamplerParameterWriter( L"ShadowSampler" );
	pSamplerWriter->SetValue( m_iTessShadowSamplerState );

	// ---------------------------------------------------------------Cylinder-------------------------------------------------------------------
	m_pCylinderShaderEffect = EffectPtr( new Effect );

	m_pCylinderShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pCylinderShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pDisplacementMapEffect;
	m_pCylinderShaderEffect->Schemes[VT_SHADOW_MAP].bRender = true;
	m_pCylinderShaderEffect->Schemes[VT_SHADOW_MAP].pEffect = pTessShadowMapEffect;

	pMatrixParameterWriter = m_pCylinderShaderEffect->ParameterWriters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	pShaderResourceWriter = m_pCylinderShaderEffect->ParameterWriters.GetShaderResourceParameterWriter( L"ShadowMap" );
	pShaderResourceWriter->SetValue( m_pShadowMap->GetShadowMap() );

	pSamplerWriter = m_pCylinderShaderEffect->ParameterWriters.GetSamplerParameterWriter( L"ShadowSampler" );
	pSamplerWriter->SetValue( m_iTessShadowSamplerState );

	// -------------------------------------------------Skull-----------------------------------------------
	m_pSkullShaderEffect = EffectPtr( new Effect );

	m_pSkullShaderEffect->Schemes[VT_PERSPECTIVE].bRender = true;
	m_pSkullShaderEffect->Schemes[VT_PERSPECTIVE].pEffect = pBasicEffect;
	m_pSkullShaderEffect->Schemes[VT_SHADOW_MAP].bRender = true;
	m_pSkullShaderEffect->Schemes[VT_SHADOW_MAP].pEffect = pShadowMapEffect;

	pShaderResourceWriter = m_pSkullShaderEffect->ParameterWriters.GetShaderResourceParameterWriter( L"ShadowMap" );
	pShaderResourceWriter->SetValue( m_pShadowMap->GetShadowMap() );

	pSamplerWriter = m_pSkullShaderEffect->ParameterWriters.GetSamplerParameterWriter( L"ShadowSampler" );
	pSamplerWriter->SetValue( m_iShadowSamplerState );
}

void App::CreateSurfaceMaterial()
{
	m_pBoxMaterial      = new Material( "BoxMaterial.lua" );
	m_pGridMaterial     = new Material( "GridMaterial.lua" );
	m_pCylinderMaterial = new Material( "CylinderMaterial.lua" );
	m_pSphereMaterial   = new Material( "SphereMaterial.lua" );
	m_pSkullMaterial    = new Material( "SkullMaterial.lua" );
}