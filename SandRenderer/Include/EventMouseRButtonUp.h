#ifndef EventMouseRButtonUp_h
#define EventMouseRButtonUp_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseRButtonUp : public EventMouseMessage
	{
	public:
		EventMouseRButtonUp( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseRButtonUp();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseRButtonUp> EventMouseRButtonUpPtr;
}

#endif