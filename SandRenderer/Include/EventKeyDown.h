#ifndef EventKeyDown_h
#define EventKeyDown_h

#include "EventKeyboardMessage.h"

namespace Sand
{
	class EventKeyDown : public EventKeyboardMessage
	{
	public:
		EventKeyDown( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventKeyDown();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();
	};

	typedef std::shared_ptr<EventKeyDown> EventKeyDownPtr;
};

#endif