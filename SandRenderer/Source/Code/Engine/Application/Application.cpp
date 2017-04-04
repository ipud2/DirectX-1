#include "Engine/PCH.h"
#include "Application.h"
#include "Engine/Utility/Log.h"
#include "Engine/Gui/EditorManager.h"
#include "Engine/Render/DXGI/SwapChainConfig.h"
#include "Engine/Resource/Texture/Texture2DConfig.h"

using namespace Sand;

// ������ֻ��һ��ʵ��
Application* Application::m_spApplication = nullptr;

Application::Application()
	:m_bSaveScreenShot( false )
{
	m_spApplication = this;

	m_pTimer = new Timer;
	m_pTimer->Update();

	Log::Get().Open();

	SetEventManager( &EventManager::Get() );

	// ��Ҫ���ӵ��¼�
	RequestEvent( SYSTEM_KEY_UP );
	RequestEvent( SYSTEM_KEY_DOWN );
	RequestEvent( SYSTEM_KEY_CHAR );
	RequestEvent( INFO_MESSAGE );
	RequestEvent( ERROR_MESSAGE );

	m_pScene = new Scene();
}

Application::~Application()
{
	Log::Get().Close();

	if( m_pScene != nullptr )
	{
		delete m_pScene;
	}

	if( m_pTimer != nullptr )
	{
		delete m_pTimer;
	}	
}

Application* Application::Get()
{
	if( !m_spApplication )	m_spApplication = new Application;

	return m_spApplication;
}

void Application::RequestTermination()
{
	PostQuitMessage( 0 );
}

void Application::MessageLoop()
{
	MSG msg;

	while( true )
	{
		while( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT )
			{
				return;
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		// ����
		Update();

		// ÿ֡����Ҫ����Ƿ���Ҫ����ͼ��
		TakeScreenShot();
	}
}

LRESULT Application::WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
	switch( msg )
	{
		case WM_CREATE:
		{
			return 0;
			break;
		}

		case WM_PAINT:
		{
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
			break;
		}

		case WM_SIZE:
		{
			EventWindowResizePtr pEvent = EventWindowResizePtr( new EventWindowResize( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		// ---------------------LButton------------------------ 
		case WM_LBUTTONUP:
		{
			EventMouseLButtonUpPtr pEvent = EventMouseLButtonUpPtr( new EventMouseLButtonUp( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		case WM_LBUTTONDOWN:
		{
			EventMouseLButtonDownPtr pEvent = EventMouseLButtonDownPtr( new EventMouseLButtonDown( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		// ---------------------MButton------------------------------
		case WM_MBUTTONUP:
		{
			EventMouseMButtonUpPtr pEvent = EventMouseMButtonUpPtr( new EventMouseMButtonUp( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		case WM_MBUTTONDOWN:
		{
			EventMouseMButtonDownPtr pEvent = EventMouseMButtonDownPtr( new EventMouseMButtonDown( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		// ----------------------RButton-------------------------------
		case WM_RBUTTONUP:
		{
			EventMouseRButtonUpPtr pEvent = EventMouseRButtonUpPtr( new EventMouseRButtonUp( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		case WM_RBUTTONDOWN:
		{
			EventMouseRButtonDownPtr pEvent = EventMouseRButtonDownPtr( new EventMouseRButtonDown( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		// -----------------------MOUSE----------------------------------
		case WM_MOUSEMOVE:
		{
			// ����ƶ�
			EventMouseMovePtr pEvent = EventMouseMovePtr( new EventMouseMove( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}

		case WM_MOUSEWHEEL:
		{
			EventMouseWheelPtr pEvent = EventMouseWheelPtr( new EventMouseWheel( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}
		
		// -----------------------Key-----------------------------------------
		case WM_KEYUP:
		{
			EventKeyUpPtr pEvent = EventKeyUpPtr( new EventKeyUp( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}


		case WM_KEYDOWN:
		{
			EventKeyDownPtr pEvent = EventKeyDownPtr( new EventKeyDown( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}


		case WM_CHAR:
		{
			EventCharPtr pEvent = EventCharPtr( new EventChar( hwnd , wParam , lParam ) );
			EventManager::Get().ProcessEvent( pEvent );
			break;
		}
	}


	return DefWindowProc( hwnd , msg , wParam , lParam );
}


bool Application::HandleEvent( EventPtr pEvent )
{
	int type = pEvent->GetEventType();

	if( type == INFO_MESSAGE )
	{
		// ������Ϣ����������
		EventInfoMessagePtr pInfoMessage = std::static_pointer_cast< EventInfoMessage >( pEvent );
		MessageBox( 0 , pInfoMessage->GetInfoMessage().c_str() , L"Info Message" , MB_ICONINFORMATION | MB_SYSTEMMODAL );
	}
	else if( type == ERROR_MESSAGE )
	{
		// ���Ǵ�����Ϣ,�������Ѳ���������
		EventErrorMessagePtr pErrorMessage = std::static_pointer_cast< EventErrorMessage >( pEvent );
		MessageBox( 0 , pErrorMessage->GetErrorMessage().c_str() , L"Error Message" , MB_ICONERROR | MB_SYSTEMMODAL );
		RequestTermination();	// ��������
	}
	else if( type == SYSTEM_KEY_UP )
	{
		// ---------------���̵���˵��������������ݰ����Ĳ�ͬʵ�ֲ�ͬ�Ĺ���------------------

		EventKeyUpPtr  pKeyUp = std::static_pointer_cast< EventKeyUp >( pEvent );

		// �жϰ��µ����ĸ���
		unsigned int key = pKeyUp->GetCharacterCode();

		if( key == VK_ESCAPE )
		{
			// ���µ���Esc, �ü����ڽ�����������
			RequestTermination();
			return true;
		}
		else if( key == VK_SPACE )
		{
			// ���¿ո񣬱��浱ǰ֡ͼ��
			m_bSaveScreenShot = true;
			return true;
		}
	}

	return false;
}

void Sand::Application::ShutdownEngineComponents()
{
	if( m_pRenderer )
	{
		m_pRenderer->Shutdown();
		SAFE_DELETE( m_pRenderer );
	}

	if( m_pWindow )
	{
		m_pWindow->Shutdown();
		SAFE_DELETE( m_pWindow );
	}
}

void Sand::Application::Initialize()
{

}

void Sand::Application::Update()
{
	m_pTimer->Update();

	// ���ñ���
	m_pRenderer->GetPipelineManagerRef()->ClearBuffers( Vector4f( 0.0f , 0.0f , 0.0f , 0.0f ) , 1.0f );

	UpdateEditor();

	m_pRenderer->Present( m_pWindow->GetSwapChain() );
}

void Sand::Application::Shutdown()
{
	SAFE_DELETE( m_spApplication );
}

void Sand::Application::BeforeRegisterWindowClass( WNDCLASSEX& wc )
{

}

void Sand::Application::TakeScreenShot()
{
	if( m_bSaveScreenShot )
	{
		m_bSaveScreenShot = false;
		m_pRenderer->GetPipelineManagerRef()->SaveTextureScreenShot( 0 , GetName() );
	}
}

std::wstring Sand::Application::GetName()
{
	return L"SandRenderer";
}

void Application::SetFrameRate( HWND hwnd )
{
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;

	FrameCount++;
	if ( m_pTimer->TotalTime() - TimeElapsed >= 1.0f )
	{
		float fps = ( float )FrameCount;
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision( 6 );
		outs << GetName() << L" "
			<< L"FPS: " << fps << L" "
			<< L"Frame Time: " << mspf << L" (ms)";

		SetWindowText( hwnd , outs.str().c_str() );

		FrameCount = 0;
		TimeElapsed += 1.0f;
	}
}

void Application::UpdateEditor()
{
}

bool Application::ConfigureEngineComponents()
{
	// ����Win32RenderWindow�������ڴ������ڣ������ô�����Ϣ
	m_pWindow = new Win32RenderWindow;
	m_pWindow->SetSize( 1920 , 1080 );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// ��������
										
	m_pRenderer = new Renderer;			// ������Ⱦ��

	// ����Device & DeviceContext
	// ����Ĭ�ϵ�Rasterizer State �� Blend State and DepthStencilState
	if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_HARDWARE , D3D_FEATURE_LEVEL_11_0 ) )
	{
		Log::Get().Error( L"�޷�����Ӳ���豸�����Դ���reference�豸" );

		if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_REFERENCE , D3D_FEATURE_LEVEL_11_0 ) )
		{
			// ָ�����ڵ���ʾ״̬�� ����ָ��Ϊ����
			ShowWindow( m_pWindow->GetHandle() , SW_HIDE );
			MessageBox( m_pWindow->GetHandle() , L"�޷�����Ӳ��/���Direct3D 11�豸�����򽫻���ֹ" , L"SandRenderer" , MB_ICONEXCLAMATION | MB_SYSTEMMODAL );
			RequestTermination();

			return false;
		}

		m_pTimer->SetFixedTimeStep( 1.0f / 10.0f );
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
}