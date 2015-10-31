#ifndef EventMouseMButtonDown_h
#define EventMouseMButtonDown_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseMButtonDown : public EventMouseMessage
	{
	public:
		EventMouseMButtonDown( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseMButtonDown();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseMButtonDown> EventMouseMButtonDownPtr;
}

#endif