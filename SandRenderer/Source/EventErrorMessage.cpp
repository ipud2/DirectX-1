#include "PCH.h"
#include "EventErrorMessage.h"

using namespace Sand;

EventErrorMessage::EventErrorMessage( std::wstring& message )
{
	m_Message = message;
}

EventErrorMessage::EventErrorMessage( const wchar_t* pMessage )
{
	m_Message = std::wstring( pMessage );
}

EventErrorMessage::~EventErrorMessage()
{
	
}

std::wstring EventErrorMessage::GetEventName()
{
	return std::wstring( L"error_message" );
}

EventType EventErrorMessage::GetEventType()
{
	return ERROR_MESSAGE;
}

std::wstring& EventErrorMessage::GetErrorMessage()
{
	return m_Message;
}