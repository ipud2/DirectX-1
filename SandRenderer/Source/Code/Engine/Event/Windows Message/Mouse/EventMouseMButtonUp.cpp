#include <Engine/PCH.h>
#include "EventMouseMButtonUp.h"

using namespace Sand;

EventMouseMButtonUp::EventMouseMButtonUp( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseMButtonUp::~EventMouseMButtonUp()
{

}

std::wstring EventMouseMButtonUp::GetEventName()
{
	return std::wstring( L"mid_button_up" );
}

EventType EventMouseMButtonUp::GetEventType()
{
	return SYSTEM_MBUTTON_UP;
}