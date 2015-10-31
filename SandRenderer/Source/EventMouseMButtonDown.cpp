#include "PCH.h"
#include "EventMouseMButtonDown.h"

using namespace Sand;

EventMouseMButtonDown::EventMouseMButtonDown( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseMButtonDown::~EventMouseMButtonDown()
{

}

std::wstring EventMouseMButtonDown::GetEventName()
{
	return std::wstring( L"mid_button_down" );
}

EventType EventMouseMButtonDown::GetEventType()
{
	return SYSTEM_MBUTTON_DOWN;
}