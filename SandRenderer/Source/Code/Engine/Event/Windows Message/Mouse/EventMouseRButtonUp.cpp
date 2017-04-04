#include <Engine/PCH.h>
#include "EventMouseRButtonUp.h"

using namespace Sand;

EventMouseRButtonUp::EventMouseRButtonUp( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseRButtonUp::~EventMouseRButtonUp()
{

}

std::wstring EventMouseRButtonUp::GetEventName()
{
	return std::wstring( L"right_button_up" );
}

EventType EventMouseRButtonUp::GetEventType()
{
	return SYSTEM_RBUTTON_UP;
}