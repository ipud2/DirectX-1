#include <Engine/PCH.h>

#include "Engine/Event/Windows Message/Keyboard/EventKeyDown.h"

using namespace Sand;

EventKeyDown::EventKeyDown( HWND hwnd , unsigned int wParam , long lParam )
	:EventKeyboardMessage( hwnd , wParam , lParam )
{

}

EventKeyDown::~EventKeyDown()
{

}

std::wstring EventKeyDown::GetEventName()
{
	return std::wstring( L"key_down" );
}

EventType EventKeyDown::GetEventType()
{
	return SYSTEM_KEY_DOWN;
}