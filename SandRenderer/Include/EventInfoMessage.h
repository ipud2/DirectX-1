#ifndef EventInfoMessage_h
#define EventInfoMessage_h

#include "IEvent.h"

namespace Sand
{
	class EventInfoMessage : IEvent
	{
	public:
		EventInfoMessage( std::wstring& message );
		EventInfoMessage( const wchar_t* message );
		virtual ~EventInfoMessage();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();

		std::wstring& GetInfoMessage();

	protected:
		std::wstring m_Message;
	};

	typedef std::shared_ptr<EventInfoMessage> EventInfoMessagePtr;
};

#endif