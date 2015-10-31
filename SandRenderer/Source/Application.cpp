#include "PCH.h"
#include "Application.h"

using namespace Sand;

// 保持类只有一个实例
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

		// 更新
		Update();

		// 每帧都需要检查是否需要保存图像
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
			// 鼠标移动
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
		// 若是信息，弹窗提醒
		EventInfoMessagePtr pInfoMessage = std::static_pointer_cast< EventInfoMessage >( pEvent );
		MessageBox( 0 , pInfoMessage->GetInfoMessage().c_str() , L"Info Message" , MB_ICONINFORMATION | MB_SYSTEMMODAL );
	}
	else if( type == ERROR_MESSAGE )
	{
		// 若是错误信息,弹窗提醒并结束运行
		EventErrorMessagePtr pErrorMessage = std::static_pointer_cast< EventErrorMessage >( pEvent );
		MessageBox( 0 , pErrorMessage->GetErrorMessage().c_str() , L"Error Message" , MB_ICONERROR | MB_SYSTEMMODAL );
		RequestTermination();	// 结束运行
	}
	else if( type == SYSTEM_KEY_UP )
	{
		// ---------------键盘弹起，说明输入结束，根据按键的不同实现不同的功能------------------

		EventKeyUpPtr  pKeyUp = std::static_pointer_cast< EventKeyUp >( pEvent );

		// 判断按下的是哪个键
		unsigned int key = pKeyUp->GetCharacterCode();

		if( key == VK_ESCAPE )
		{
			// 按下的是Esc, 该键用于结束程序运行
			RequestTermination();
			return true;
		}
		else if( key == VK_SPACE )
		{
			// 按下空格，保存当前帧图像
			m_bSaveScreenShot = true;
			return true;
		}
	}
}