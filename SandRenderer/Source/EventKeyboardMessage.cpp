#include "PCH.h"
#include "EventKeyboardMessage.h"

using namespace Sand;

EventKeyboardMessage::EventKeyboardMessage( HWND hwnd , unsigned int wParam , long lParam )
	:EventWindowMessage( hwnd , wParam , lParam )
{

}

EventKeyboardMessage::~EventKeyboardMessage()
{

}

unsigned int EventKeyboardMessage::GetCharacterCode()
{
	return m_wParam;
}

unsigned int EventKeyboardMessage::GetRepeatCount()
{
	return ( 0xffff & m_lParam );
}

unsigned int EventKeyboardMessage::GetScanCode()
{
	return ( 0xf0000 & m_lParam ) >> 16;
}

bool EventKeyboardMessage::GetExtendedKey()
{
	return ( 0xf000000 & m_lParam ) > 0;
}

bool EventKeyboardMessage::GetContextCode()
{
	return ( 0x20000000 & m_lParam ) > 0;
}

bool EventKeyboardMessage::GetPreviousKeyState()
{
	return ( 0x40000000 & m_lParam ) > 0;
}

bool EventKeyboardMessage::GetTransitionState()
{
	return ( 0x80000000 & m_lParam ) > 0;
}