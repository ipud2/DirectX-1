#include "PCH.h"
#include "EventMouseMove.h"

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