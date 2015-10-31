#ifndef EventKeyUp_h
#define EventKeyUp_h

#include "EventKeyboardMessage.h"

namespace Sand
{
	class EventKeyUp : public EventKeyboardMessage
	{
	public:
		EventKeyUp( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventKeyUp();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventKeyUp> EventKeyUpPtr;
};

#endif