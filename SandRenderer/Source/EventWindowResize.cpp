#include "PCH.h"
#include "EventWindowResize.h"

using namespace Sand;

EventWindowResize::EventWindowResize( HWND hwnd , unsigned int wParam , long lParam )
	:EventWindowMessage( hwnd , wParam , lParam )
{

}

EventWindowResize::~EventWindowResize()
{

}

std::wstring EventWindowResize::GetEventName()
{
	return std::wstring( L"window_resize" );
}

EventType EventWindowResize::GetEventType()
{
	return WINDOW_RESIZE;
}

int EventWindowResize::NewWidth()
{
	return m_lParam & 0xffff;
}

int EventWindowResize::NewHeight()
{
	return ( m_lParam & 0xffff0000 ) >> 16;
}

bool EventWindowResize::IsMaxHide()
{
	if( m_wParam == SIZE_MAXHIDE )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 窗口最大化
bool EventWindowResize::IsMaximized()
{
	if( m_wParam == SIZE_MAXIMIZED )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventWindowResize::IsMaxShow()
{
	if( m_wParam == SIZE_MAXSHOW )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 窗口最小化
bool EventWindowResize::IsMinimized()
{
	if( m_wParam == SIZE_MINIMIZED )
	{
		return true;
	}
	else
	{
		return false;
	}
}

//bool EventWindowResize::IsRestored()
//{
//	if( m_wParam == SIZE_RESTORED )
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}