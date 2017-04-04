#include <Engine/PCH.h>
#include "EventMouseLButtonUp.h"

using namespace Sand;

EventMouseLButtonUp::EventMouseLButtonUp( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseLButtonUp::~EventMouseLButtonUp()
{

}

std::wstring EventMouseLButtonUp::GetEventName()
{
	return std::wstring( L"left_button_up" );
}

EventType EventMouseLButtonUp::GetEventType()
{
	return SYSTEM_LBUTTON_UP;
}