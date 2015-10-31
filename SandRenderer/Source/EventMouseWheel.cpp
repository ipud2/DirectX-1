#include "PCH.h"
#include "EventMouseWheel.h"

using namespace Sand;

EventMouseWheel::EventMouseWheel( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseWheel::~EventMouseWheel()
{

}

std::wstring EventMouseWheel::GetEventName()
{
	return std::wstring( L"mouse_wheel" );
}

EventType EventMouseWheel::GetEventType()
{
	return SYSTEM_MOUSE_WHEEL;
}