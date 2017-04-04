#include <Engine/PCH.h>
#include "Engine/Event/Windows Message/Mouse/EventMouseMove.h"

using namespace Sand;

EventMouseMove::EventMouseMove( HWND hwnd , unsigned int wParam , long lParam )
	:EventMouseMessage( hwnd , wParam , lParam )
{

}

EventMouseMove::~EventMouseMove()
{

}

std::wstring EventMouseMove::GetEventName()
{
	return std::wstring( L"mouse_move" );
}

EventType EventMouseMove::GetEventType()
{
	return SYSTEM_MOUSE_MOVE;
}