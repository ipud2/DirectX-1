#include "PCH.h"
#include "EventMouseLeave.h"

using namespace Sand;

EventMouseLeave::EventMouseLeave( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseLeave::~EventMouseLeave()
{

}

std::wstring EventMouseLeave::GetEventName()
{
	return std::wstring( L"mouse_leave" );
}

EventType EventMouseLeave::GetEventType()
{
	return SYSTEM_MOUSE_LEAVE;
}