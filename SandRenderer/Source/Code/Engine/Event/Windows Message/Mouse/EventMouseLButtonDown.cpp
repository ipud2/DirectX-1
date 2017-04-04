#include <Engine/PCH.h>
#include "EventMouseLButtonDown.h"

using namespace Sand;

EventMouseLButtonDown::EventMouseLButtonDown( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseLButtonDown::~EventMouseLButtonDown()
{

}

std::wstring EventMouseLButtonDown::GetEventName()
{
	return std::wstring( L"left_button_down" );
}

EventType EventMouseLButtonDown::GetEventType()
{
	return SYSTEM_LBUTTON_DOWN;
}