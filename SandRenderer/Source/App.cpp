#include "App.h"
#include "Log.h"

#include "SwapChainConfig.h"

#include "Texture2DConfig.h"

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

	// 创建Device
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

}

void App::Shutdown()
{

}

void App::TakeScreenShot()
{

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