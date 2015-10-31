#ifndef EventMouseMove_h
#define EventMouseMove_h

#include "EventMouseMessage.h"

namespace Sand
{
	class EventMouseMove : public EventMouseMessage
	{
	public:
		EventMouseMove( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseMove();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventMouseMove> EventMouseMovePtr;
}

#endif