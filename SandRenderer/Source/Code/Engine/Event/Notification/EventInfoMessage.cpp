#include <Engine/PCH.h>
#include "Engine/Event/Notification/EventInfoMessage.h"

using namespace Sand;

EventInfoMessage::EventInfoMessage( std::wstring& message )
{
	m_Message = message;
}

EventInfoMessage::EventInfoMessage( const wchar_t* message )
{
	m_Message = std::wstring( message );
}

EventInfoMessage::~EventInfoMessage()
{

}

std::wstring EventInfoMessage::GetEventName()
{
	return std::wstring( L"info_message" );
}

EventType EventInfoMessage::GetEventType()
{
	return INFO_MESSAGE;
}

std::wstring& EventInfoMessage::GetInfoMessage()
{
	return m_Message;
}