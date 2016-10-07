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

#include "ScriptManager.h"
#include "LuaActor.h"
#include "LuaEffect.h"
#include "LuaMaterial.h"
#include "LuaGeometry.h"
#include "LuaEntity.h"

extern "C"
{
#include "Lua-5.3.3/src/lua.h"
#include "lua-5.3.3/src/lauxlib.h"
#include "lua-5.3.3/src/lualib.h"
}

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

	m_pLight = nullptr;
	m_pCameras = nullptr;

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
	if ( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_HARDWARE , D3D_FEATURE_LEVEL_11_0 ) )
	{
		Log::Get().Write( L"�޷�����Ӳ���豸�����Դ���reference�豸" );

		if ( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_REFERENCE , D3D_FEATURE_LEVEL_11_0 ) )
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
	ScriptManager ScriptMgr;

	LuaEffect* effect = new LuaEffect( m_pRenderer );
	effect->Register( ScriptMgr.GetState() );

	LuaGeometry geometry;
	geometry.Register( ScriptMgr.GetState() );

	LuaMaterial mat;
	mat.Register( ScriptMgr.GetState() );

	LuaEntity ent;
	ent.Register( ScriptMgr.GetState() );

	LuaActor actor;
	actor.Register( ScriptMgr.GetState() );

	if ( luaL_loadfile( ScriptMgr.GetState() , "../Data/Script/SceneTestScript.lua" ) || lua_pcall( ScriptMgr.GetState() , 0 , 0 , 0 ) )
	{
		const char* errormessage = lua_tostring( ScriptMgr.GetState() , -1 );

		Log::Get().Write( SandString::ToUnicode( std::string( errormessage ) ) );
	}

	for ( int i = 0; i < LuaActor::ActorList.size(); i++ )
	{
		m_pScene->AddActor( LuaActor::ActorList[i] );
	}

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

	// ---------------------------------SkyBox----------------------------
	m_pSkyBox = new Skybox( std::wstring( L"SnowCube.dds" ) , m_iLinearSampler );

	// -------------------Add to Scene-------------------
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
	return std::wstring( L"BasicScript" );
}