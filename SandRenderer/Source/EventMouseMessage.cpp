#include "PCH.h"
#include "EventMouseMessage.h"

using namespace Sand;

EventMouseMessage::EventMouseMessage( HWND hwnd , unsigned int wParam , long lParam )
	:EventWindowMessage( hwnd , wParam , lParam )
{

}

EventMouseMessage::~EventMouseMessage()
{

}

bool EventMouseMessage::ControlKeyDown()
{
	return ( ( MK_CONTROL & m_wParam ) > 0 );
}

bool EventMouseMessage::LButtonDown()
{
	return ( MK_LBUTTON & m_wParam ) > 0;
}

bool EventMouseMessage::RButtonDown()
{
	return (MK_RBUTTON & m_wParam ) > 0;
}

bool EventMouseMessage::ShiftKeyDown()
{
	return ( MK_SHIFT & m_wParam ) > 0;
}

bool EventMouseMessage::MButtonDown()
{
	return ( MK_MBUTTON & m_wParam ) > 0;
}

int EventMouseMessage::GetX()
{
	return ( 0xffff & m_wParam );
}

int EventMouseMessage::GetY()
{
	return ( 0xffff0000 & m_wParam ) >> 16;
}