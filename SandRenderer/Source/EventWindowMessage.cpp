#include "PCH.h"
#include "EventWindowMessage.h"

using namespace Sand;

EventWindowMessage::EventWindowMessage( HWND hwnd , unsigned int wParam , long lParam )
{
	m_hwnd = hwnd;

	m_wParam = wParam;

	m_lParam = lParam;
}

EventWindowMessage::~EventWindowMessage()
{

}

HWND EventWindowMessage::GetWindowHandle()
{
	return m_hwnd;
}

unsigned int EventWindowMessage::GetwParam()
{
	return m_wParam;
}

long EventWindowMessage::GetlParam()
{
	return m_lParam;
}