#include "PCH.h"
#include "EventKeyUp.h"

using namespace Sand;

EventKeyUp::EventKeyUp( HWND hwnd , unsigned int wParam , long lParam )
	:EventKeyboardMessage( hwnd , wParam , lParam )
{

}

EventKeyUp::~EventKeyUp()
{

}

std::wstring EventKeyUp::GetEventName()
{
	return ( std::wstring( L"keyup" ) );
}

EventType EventKeyUp::GetEventType()
{
	return SYSTEM_KEY_UP;
}