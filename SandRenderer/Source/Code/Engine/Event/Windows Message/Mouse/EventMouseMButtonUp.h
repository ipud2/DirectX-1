#ifndef EventMouseMButtonUp_h
#define EventMouseMButtonUp_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseMButtonUp : public EventMouseMessage
	{
	public:
		EventMouseMButtonUp( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseMButtonUp();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseMButtonUp> EventMouseMButtonUpPtr;
}

#endif