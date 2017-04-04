#include <Engine/PCH.h>
#include "Engine/Event/Windows Message/Mouse/EventMouseRButtonDown.h"

using namespace Sand;

EventMouseRButtonDown::EventMouseRButtonDown( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseRButtonDown::~EventMouseRButtonDown()
{

}

std::wstring EventMouseRButtonDown::GetEventName()
{
	return std::wstring( L"right_button_down" );
}

EventType EventMouseRButtonDown::GetEventType()
{
	return SYSTEM_RBUTTON_DOWN;
}