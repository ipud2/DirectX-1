#include "PCH.h"
#include "Application.h"

using namespace Sand;

// ������ֻ��һ��ʵ��
Application* Application::m_spApplication = nullptr;

Application::Application()
	:m_bSaveScreenShot( false ) ,
	m_bLoop( true )
{
	m_spApplication = this;
}

Application::~Application()
{
	
}

Application* Application::GetApplication()
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
			break;
		}

		// ---------------------LButton------------------------ 
		case WM_LBUTTONUP:
		{
			break;
		}

		case WM_LBUTTONDOWN:
		{
			break;
		}

		// ---------------------MButton------------------------------
		case WM_MBUTTONUP:
		{
			break;
		}

		case WM_MBUTTONDOWN:
		{
			break;
		}

		// ----------------------RButton-------------------------------
		case WM_RBUTTONUP:
		{
			break;
		}

		case WM_RBUTTONDOWN:
		{
			break;
		}

		// -----------------------MOUSE----------------------------------
		case WM_MOUSEMOVE:
		{
			// ����ƶ�
			break;
		}

		case WM_MOUSEWHEEL:
		{
			break;
		}
		
		// -----------------------Key-----------------------------------------
		case WM_KEYUP:
		{
			break;
		}


		case WM_KEYDOWN:
		{
			break;
		}


		case WM_CHAR:
		{
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
}