#ifndef EventChar_h
#define EventChar_h

#include "EventKeyboardMessage.h"

namespace Sand
{
	class EventChar : public EventKeyboardMessage
	{
	public:
		EventChar( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventChar();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventChar> EventCharPtr;
};
#endif