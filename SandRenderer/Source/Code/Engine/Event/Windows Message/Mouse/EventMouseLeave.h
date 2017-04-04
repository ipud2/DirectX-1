#ifndef EventMouseLeave_h
#define EventMouseLeave_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseLeave : public EventMouseMessage
	{
	public:
		EventMouseLeave( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseLeave();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseLeave> EventMouseLeavePtr;
}

#endif