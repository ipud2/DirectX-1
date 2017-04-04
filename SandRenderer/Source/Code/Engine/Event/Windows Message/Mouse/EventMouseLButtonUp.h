#ifndef EventMouseLButtonUp_h
#define EventMouseLButtonUp_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseLButtonUp : public EventMouseMessage
	{
	public:
		EventMouseLButtonUp( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseLButtonUp();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseLButtonUp> EventMouseLButtonUpPtr;
}

#endif