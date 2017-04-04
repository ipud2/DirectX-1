#ifndef EventMouseLButtonDown_h
#define EventMouseLButtonDown_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseLButtonDown : public EventMouseMessage
	{
	public:
		EventMouseLButtonDown( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseLButtonDown();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseLButtonDown> EventMouseLButtonDownPtr;
}

#endif