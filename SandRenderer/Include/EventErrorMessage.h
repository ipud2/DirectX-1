#ifndef EventErrorMessage_h
#define EventErrorMessage_h

#include "IEvent.h"

namespace Sand
{
	class EventErrorMessage : public IEvent
	{
	public:
		EventErrorMessage( std::wstring& message );
		EventErrorMessage( const wchar_t* pMessage );
		virtual ~EventErrorMessage();

		std::wstring GetEventName();
		EventType GetEventType();

		std::wstring& GetErrorMessage();

	protected:
		// ´íÎóĞÅÏ¢
		std::wstring m_Message;
	};

	typedef std::shared_ptr<EventErrorMessage> EventErrorMessagePtr;
}

#endif