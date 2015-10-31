#ifndef EventMouseWheel_h
#define EventMouseWheel_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseWheel : public EventMouseMessage
	{
	public:
		EventMouseWheel( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseWheel();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseWheel> EventMouseWheelPtr;
}

#endif