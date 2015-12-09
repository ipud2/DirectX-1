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

#include "GeometryGenerator.h"

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
	m_pBoxMaterial = nullptr;
	m_pBoxSurfaceProperty = nullptr;

	m_pGridMaterial = nullptr;

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
	// 加载Box图元的数据
	m_pBoxGeometry = GeometryLoader::LoadOBJ( std::wstring( L"Cube.OBJ" ) );
	m_pBoxGeometry->LoadToBuffer();
	m_pBoxGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	// 创建Grid图元的数据
	m_pGridGeometry = GeometryGenerator::GeneratorGrid( 20.0f , 30.0f , 60 , 40 );
	m_pGridGeometry->LoadToBuffer();
	m_pGridGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// 创建Cylinder图元的数据
	m_pCylinderGeometry = GeometryGenerator::GeneratorCylinder( 0.5f , 0.3f , 3.0f , 20 , 20 );
	m_pCylinderGeometry->LoadToBuffer();
	m_pCylinderGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// 创建Sphere图元
	m_pSphereGeometry = GeometryGenerator::GeneratorSphere( 20 , 20 , 0.5f );
	m_pSphereGeometry->LoadToBuffer();
	m_pCylinderGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_pSkullGeometry = GeometryLoader::LoadOBJ( std::wstring( L"Skull.obj" ) );
	m_pSkullGeometry->LoadToBuffer();
	m_pSkullGeometry->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// create the material for use by the entities
	CreateMaterial();

	// -----------------------------SurfaceProperty---------------------------------
	CreateSurfaceProperty();

	// --------------------------------create render view object--------------------------------------------
	m_pRenderView = new ViewPerspective( *m_pRenderer , m_pRenderTarget , m_pDepthStencilTarget );
	m_pRenderView->SetBackColor( Vector4f( 0.69f , 0.77f , 0.87f , 1.0f ) );

	// -----------------------------------------Camera----------------------------------------------
	m_pCameras = new Camera();
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
	m_pBox->GetRenderableRef().SetMaterial( m_pBoxMaterial );
	m_pBox->GetRenderableRef().SetSurfaceProperty( m_pBoxSurfaceProperty );
	m_pBox->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.5f , 0.0f );
	m_pBox->GetTransformRef().GetScaleRef() = Vector3f( 3.0f , 1.0f , 3.0f );
	m_pActor->GetRootNode()->AttachChild( m_pBox );

	//
	// Grid
	//
	m_pGrid = new Entity;
	m_pGrid->GetRenderableRef().SetGeometry( m_pGridGeometry );
	m_pGrid->GetRenderableRef().SetMaterial( m_pGridMaterial );
	m_pGrid->GetRenderableRef().SetSurfaceProperty( m_pGridSurfaceProperty );
	m_pGrid->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 0.0f , 0.0f );
	m_pActor->GetRootNode()->AttachChild( m_pGrid );
	
	//
	// Cylinder
	//
	for ( int i = 0; i < 5; i++ )
	{
		m_pCylinder[2 * i + 0] = new Entity;
		m_pCylinder[2 * i + 0]->GetRenderableRef().SetGeometry( m_pCylinderGeometry );
		m_pCylinder[2 * i + 0]->GetRenderableRef().SetMaterial( m_pCylinderMaterial );
		m_pCylinder[2 * i + 0]->GetRenderableRef().SetSurfaceProperty( m_pCylinderSurfaceProperty );
		m_pCylinder[2 * i + 0]->GetTransformRef().GetPositionRef() = Vector3f( -5.0f , 1.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pCylinder[2 * i + 0] );

		m_pCylinder[2 * i + 1] = new Entity;
		m_pCylinder[2 * i + 1]->GetRenderableRef().SetGeometry( m_pCylinderGeometry );
		m_pCylinder[2 * i + 1]->GetRenderableRef().SetMaterial( m_pCylinderMaterial );
		m_pCylinder[2 * i + 1]->GetRenderableRef().SetSurfaceProperty( m_pCylinderSurfaceProperty );
		m_pCylinder[2 * i + 1]->GetTransformRef().GetPositionRef() = Vector3f( 5.0f , 1.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pCylinder[2 * i + 1] );
	}

	//
	// Sphere
	//
	for ( int i = 0; i < 5; i++ )
	{
		m_pSphere[2 * i + 0] = new Entity;
		m_pSphere[2 * i + 0]->GetRenderableRef().SetGeometry( m_pSphereGeometry );
		m_pSphere[2 * i + 0]->GetRenderableRef().SetMaterial( m_pSphereMaterial );
		m_pSphere[2 * i + 0]->GetRenderableRef().SetSurfaceProperty( m_pSphereSurfaceProperty );
		m_pSphere[2 * i + 0]->GetTransformRef().GetPositionRef() = Vector3f( -5.0f , 3.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pSphere[2 * i + 0] );

		m_pSphere[2 * i + 1] = new Entity;
		m_pSphere[2 * i + 1]->GetRenderableRef().SetGeometry( m_pSphereGeometry );
		m_pSphere[2 * i + 1]->GetRenderableRef().SetMaterial( m_pSphereMaterial );
		m_pSphere[2 * i + 1]->GetRenderableRef().SetSurfaceProperty( m_pSphereSurfaceProperty );
		m_pSphere[2 * i + 1]->GetTransformRef().GetPositionRef() = Vector3f( 5.0f , 3.5f , -10.0f + i * 5.0f );
		m_pActor->GetRootNode()->AttachChild( m_pSphere[2 * i + 1] );
	}

	m_pSkull = new Entity;
	m_pSkull->GetRenderableRef().SetGeometry( m_pSkullGeometry );
	m_pSkull->GetRenderableRef().SetMaterial( m_pSkullMaterial );
	m_pSkull->GetRenderableRef().SetSurfaceProperty( m_pSkullSurfaceProperty );
	m_pSkull->GetTransformRef().GetPositionRef() = Vector3f( 0.0f , 1.0f , 0.0f );
	m_pSkull->GetTransformRef().GetScaleRef() = Vector3f( 0.5f , 0.5f , 0.5f );
	m_pActor->GetRootNode()->AttachChild( m_pSkull );

	// ---------------------------------SkyBox----------------------------
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

void App::CreateMaterial()
{
	RenderEffect* pEffect = new RenderEffect;

	pEffect->SetVertexShader( m_pRenderer->LoadShader(	ST_VERTEX_SHADER , 
														std::wstring( L"BasicTexture.hlsl" ) , 
														std::wstring( L"VSMain" ) , 
														std::wstring( L"vs_5_0" ) ) );

	pEffect->SetPixelShader( m_pRenderer->LoadShader(	ST_PIXEL_SHADER ,
														std::wstring( L"BasicTexture.hlsl" ) ,
														std::wstring( L"PSMain" ) ,
														std::wstring( L"ps_5_0" ) ) );

	// --------------------------------------------------------------------Box------------------------------------------------------------
	m_pBoxMaterial = MaterialPtr( new Material );

	m_pBoxMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pBoxMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	// --------------------------------set texture-----------------------------
	m_pBrickTexture = m_pRenderer->LoadTexture( L"bricks.dds" );
	ShaderResourceParameterWriter* pShaderResourceWriter = m_pBoxMaterial->Parameters.GetShaderResourceParameterWriter( L"DiffuseTexture" );
	pShaderResourceWriter->SetValue( m_pBrickTexture );

	SamplerStateConfig config;
	m_iLinearSampler = m_pRenderer->CreateSamplerState( &config );
	SamplerParameterWriter* pSamplerWriter = m_pBoxMaterial->Parameters.GetSamplerParameterWriter( L"LinearSampler" );
	pSamplerWriter->SetValue( m_iLinearSampler );

	MatrixParameterWriter* pMatrixParameterWriter = m_pBoxMaterial->Parameters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	BoolParameterWriter* pBoolParameterWriter = m_pBoxMaterial->Parameters.GetBoolParameterWriter( std::wstring( L"bUseTexture" ) );
	pBoolParameterWriter->SetValue( true );

	// ----------------------------------------------------------------Grid-------------------------------------------------------------------------
	m_pGridMaterial = MaterialPtr( new Material );

	m_pGridMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pGridMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	// ---------------------Set Grid Texture-------------------------
	m_pFloorTexture = m_pRenderer->LoadTexture( L"floor.dds" );
	pShaderResourceWriter = m_pGridMaterial->Parameters.GetShaderResourceParameterWriter( L"DiffuseTexture" );
	pShaderResourceWriter->SetValue( m_pFloorTexture );

	pSamplerWriter = m_pGridMaterial->Parameters.GetSamplerParameterWriter( L"LinearSampler" );
	pSamplerWriter->SetValue( m_iLinearSampler );

	pMatrixParameterWriter = m_pGridMaterial->Parameters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.ScaleMatrixXYZ( 6.0f , 8.0f , 1.0f ) );

	pBoolParameterWriter = m_pGridMaterial->Parameters.GetBoolParameterWriter( std::wstring( L"bUseTexture" ) );
	pBoolParameterWriter->SetValue( true );

	// ---------------------------------------------------------------Cylinder-------------------------------------------------------------------
	m_pCylinderMaterial = MaterialPtr( new Material );

	m_pCylinderMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pCylinderMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	// -------------Set Cylinder Texture-----------
	pShaderResourceWriter = m_pCylinderMaterial->Parameters.GetShaderResourceParameterWriter( L"DiffuseTexture" );
	pShaderResourceWriter->SetValue( m_pBrickTexture );

	pSamplerWriter = m_pCylinderMaterial->Parameters.GetSamplerParameterWriter( L"LinearSampler" );
	pSamplerWriter->SetValue( m_iLinearSampler );

	pMatrixParameterWriter = m_pCylinderMaterial->Parameters.GetMatrixParameterWriter( std::wstring( L"TexTransformMatrix" ) );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	pBoolParameterWriter = m_pCylinderMaterial->Parameters.GetBoolParameterWriter( std::wstring( L"bUseTexture" ) );
	pBoolParameterWriter->SetValue( true );

	// ------------------------------------------------------Sphere-------------------------------------------------------------
	m_pSphereMaterial = MaterialPtr( new Material );

	m_pSphereMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pSphereMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	// ----------Set Sphere Texture----------------
	m_pStoneTexture = m_pRenderer->LoadTexture( L"Stone.dds" );
	pShaderResourceWriter = m_pSphereMaterial->Parameters.GetShaderResourceParameterWriter( L"DiffuseTexture" );
	pShaderResourceWriter->SetValue( m_pStoneTexture );

	pSamplerWriter = m_pSphereMaterial->Parameters.GetSamplerParameterWriter( L"LinearSampler" );
	pSamplerWriter->SetValue( m_iLinearSampler );

	pMatrixParameterWriter = m_pSphereMaterial->Parameters.GetMatrixParameterWriter( L"TexTransformMatrix" );
	pMatrixParameterWriter->SetValue( m_TexTransform.Identity() );

	pBoolParameterWriter = m_pSphereMaterial->Parameters.GetBoolParameterWriter( std::wstring( L"bUseTexture" ) );
	pBoolParameterWriter->SetValue( true );

	// -------------------------------------------------Skull-----------------------------------------------
	m_pSkullMaterial = MaterialPtr( new Material );

	m_pSkullMaterial->Params[VT_PERSPECTIVE].bRender = true;
	m_pSkullMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

	pBoolParameterWriter = m_pSkullMaterial->Parameters.GetBoolParameterWriter( std::wstring( L"bUseTexture" ) );
	pBoolParameterWriter->SetValue( false );

	pBoolParameterWriter = m_pSkullMaterial->Parameters.GetBoolParameterWriter( std::wstring( L"bEnableReflect" ) );
	pBoolParameterWriter->SetValue( true );

	m_pSkyTexture = m_pRenderer->LoadTexture( L"GrassCube.dds" );
	pShaderResourceWriter = m_pSkullMaterial->Parameters.GetShaderResourceParameterWriter( std::wstring( L"SkyboxTexture" ) );
	pShaderResourceWriter->SetValue( m_pSkyTexture );
}

void App::CreateSurfaceProperty()
{
	// -----------------------------------Box表面属性----------------------------------------
	m_pBoxSurfaceProperty = new BasicSurfaceProperty;
	m_pBoxSurfaceProperty->SetSurfaceProperty( Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) ,
											   Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) ,
											   Vector4f( 0.8f , 0.8f , 0.8f , 16.0f ) ,
											   Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) );

	// ----------------------------------Grid表面属性----------------------------------------
	m_pGridSurfaceProperty = new BasicSurfaceProperty;
	m_pGridSurfaceProperty->SetSurfaceProperty( Vector4f( 0.8f , 0.8f , 0.8f , 1.0f ) ,
												Vector4f( 0.8f , 0.8f , 0.8f , 1.0f ) ,
												Vector4f( 0.8f , 0.8f , 0.8f , 16.0f ) ,
												Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) );

	// ----------------------------------Cylinder表面属性---------------------------
	m_pCylinderSurfaceProperty = new BasicSurfaceProperty;
	m_pCylinderSurfaceProperty->SetSurfaceProperty( Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) ,
													Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) ,
													Vector4f( 0.8f , 0.8f , 0.8f , 16.0f ) ,
													Vector4f( 0.0f , 0.0f , 0.0f , 1.0f ) );

	// -----------------------------------Sphere表面属性----------------------------------
	m_pSphereSurfaceProperty = new BasicSurfaceProperty;
	m_pSphereSurfaceProperty->SetSurfaceProperty( Vector4f( 0.2f , 0.3f , 0.4f , 1.0f ) ,
												  Vector4f( 0.2f , 0.3f , 0.4f , 1.0f ) ,
												  Vector4f( 0.9f , 0.9f , 0.9f , 16.0f ) ,
												  Vector4f( 0.4f , 0.4f , 0.4f , 1.0f ) );

	// -----------------------------------Skull表面属性-----------------------------
	m_pSkullSurfaceProperty = new BasicSurfaceProperty;
	m_pSkullSurfaceProperty->SetSurfaceProperty( Vector4f( 0.2f , 0.2f , 0.2f , 1.0f ) ,
												 Vector4f( 0.2f , 0.2f , 0.2f , 1.0f ) ,
												 Vector4f( 0.8f , 0.8f , 0.8f , 16.0f ) ,
												 Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) );
}