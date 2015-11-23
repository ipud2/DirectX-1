#include "PCH.h"

#include "Application.h"
#include "Log.h"

using namespace Sand;

// ������ֻ��һ��ʵ��
Application* Application::m_spApplication = nullptr;

Application::Application()
	:m_bSaveScreenShot( false ) ,
	m_bLoop( true )
{
	m_spApplication = this;

	SetEventManager( &m_EventManager );

	// ��Ҫ���ӵ��¼�
	RequestEvent( SYSTEM_KEY_UP );
	RequestEvent( SYSTEM_KEY_DOWN );
	RequestEvent( SYSTEM_KEY_CHAR );
	RequestEvent( INFO_MESSAGE );
	RequestEvent( ERROR_MESSAGE );

	m_pScene = new Scene();

	m_pTimer = new Timer;
	m_pTimer->Update();
}

Application::~Application()
{
	if( m_pScene != nullptr )
	{
		delete m_pScene;
	}

	Log::Get().Close();
}

Application* Application::Get()
{
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
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		// ---------------------LButton------------------------ 
		case WM_LBUTTONUP:
		{
			EventMouseLButtonUpPtr pEvent = EventMouseLButtonUpPtr( new EventMouseLButtonUp( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		case WM_LBUTTONDOWN:
		{
			EventMouseLButtonDownPtr pEvent = EventMouseLButtonDownPtr( new EventMouseLButtonDown( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		// ---------------------MButton------------------------------
		case WM_MBUTTONUP:
		{
			EventMouseMButtonUpPtr pEvent = EventMouseMButtonUpPtr( new EventMouseMButtonUp( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		case WM_MBUTTONDOWN:
		{
			EventMouseMButtonDownPtr pEvent = EventMouseMButtonDownPtr( new EventMouseMButtonDown( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		// ----------------------RButton-------------------------------
		case WM_RBUTTONUP:
		{
			EventMouseRButtonUpPtr pEvent = EventMouseRButtonUpPtr( new EventMouseRButtonUp( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		case WM_RBUTTONDOWN:
		{
			EventMouseRButtonDownPtr pEvent = EventMouseRButtonDownPtr( new EventMouseRButtonDown( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		// -----------------------MOUSE----------------------------------
		case WM_MOUSEMOVE:
		{
			// ����ƶ�
			EventMouseMovePtr pEvent = EventMouseMovePtr( new EventMouseMove( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}

		case WM_MOUSEWHEEL:
		{
			EventMouseWheelPtr pEvent = EventMouseWheelPtr( new EventMouseWheel( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}
		
		// -----------------------Key-----------------------------------------
		case WM_KEYUP:
		{
			EventKeyUpPtr pEvent = EventKeyUpPtr( new EventKeyUp( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}


		case WM_KEYDOWN:
		{
			EventKeyDownPtr pEvent = EventKeyDownPtr( new EventKeyDown( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
			break;
		}


		case WM_CHAR:
		{
			EventCharPtr pEvent = EventCharPtr( new EventChar( hwnd , wParam , lParam ) );
			m_EventManager.ProcessEvent( pEvent );
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

void Sand::Application::BeforeRegisterWindowClass( WNDCLASSEX& wc )
{

}
