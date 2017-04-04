#ifndef EventMouseRButtonDown_h
#define EventMouseRButtonDown_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseRButtonDown : public EventMouseMessage
	{
	public:
		EventMouseRButtonDown( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseRButtonDown();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseRButtonDown> EventMouseRButtonDownPtr;
}

#endif