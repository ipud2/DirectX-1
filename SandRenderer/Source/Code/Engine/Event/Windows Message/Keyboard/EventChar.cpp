#include <Engine/PCH.h>
#include "EventChar.h"

using namespace Sand;

EventChar::EventChar( HWND hwnd , unsigned int wParam , long lParam )
	:EventKeyboardMessage( hwnd , wParam , lParam )
{

}

EventChar::~EventChar()
{

}

std::wstring EventChar::GetEventName()
{
	return std::wstring( L"key_char" );
}

EventType EventChar::GetEventType()
{
	return SYSTEM_KEY_CHAR;
}