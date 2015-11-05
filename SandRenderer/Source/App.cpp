#include "App.h"
#include "Log.h"

#include "SwapChainConfig.h"

#include "Texture2DConfig.h"

#include "PipelineManager.h"

using namespace Sand;

App AppInstance;

App::App()
{

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
	m_pDepthStencil = m_pRenderer->CreateTexture2D( &DepthConfig , 0 );

	// 设置render target view 和 depth stencil view
	m_pRenderer->m_pPipelineManager->ClearRenderTargets();
	m_pRenderer->m_pPipelineManager->m_OutputMergeStage.DesiredState.RenderTargetViews.SetState( 0 , m_pRenderTarget->m_RenderTargetViewID );
	m_pRenderer->m_pPipelineManager->m_OutputMergeStage.DesiredState.DepthStencilViews.SetState( m_pDepthStencil->m_DepthStencilViewID );
	m_pRenderer->m_pPipelineManager->ApplyRenderTargets();


	// 设置Viewport
	D3D11_VIEWPORT view_port;
	view_port.Width = m_pWindow->GetWidth();
	view_port.Height = m_pWindow->GetHeight();
	view_port.TopLeftX = m_pWindow->GetLeft();
	view_port.TopLeftY = m_pWindow->GetTop();
	view_port.MinDepth = 0.0f;
	view_port.MaxDepth = 1.0f;


	int view_port_id = m_pRenderer->CreateViewPort( view_port );
	m_pRenderer->m_pPipelineManager->m_RasterizerStage.DesiredState.ViewportCount.SetState( 1 );
	m_pRenderer->m_pPipelineManager->m_RasterizerStage.DesiredState.Viewports.SetState( 0 , view_port_id );

	return true;
}

void App::ShutdownEngineComponents()
{
	// 销毁Renderer
	if( m_pRenderer )
	{
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}

	// 销毁窗口
	if( m_pWindow )
	{
		m_pWindow->Shutdown();
		delete m_pWindow;
	}
}

void App::Initialize()
{

}

void App::Update()
{
	m_pRenderer->m_pPipelineManager->ClearBuffers( Vector4f( 0.0f , 0.0f , 0.0f , 0.0f ) , 1.0f , 0 );
	m_pRenderer->Present( m_pWindow->GetSwapChain() );
}

void App::Shutdown()
{
	
}

void App::TakeScreenShot()
{
	if( m_bSaveScreenShot )
	{
		m_bSaveScreenShot = false;
		m_pRenderer->m_pPipelineManager->SaveTextureScreenShot()
	}
}

bool App::HandleEvent( EventPtr pEvent )
{
	EventType e = pEvent->GetEventType();

	if( e == SYSTEM_KEY_DOWN )
	{

	}
	else if( e == SYSTEM_KEY_UP )
	{

	}

	return Application::HandleEvent( pEvent );
}

std::wstring App::GetName()
{
	return std::wstring( L"SandRenderer" );
}