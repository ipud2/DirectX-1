#ifndef IEvent_h
#define IEvent_h

#include "PCH.h"

namespace Sand
{
	// �����¼�����
	enum EventType
	{
		RENDER_FRAME_START ,

		// ---------���-----------
		SYSTEM_LBUTTON_UP ,
		SYSTEM_LBUTTON_DOWN ,

		// --------�Ҽ�--------------
		SYSTEM_RBUTTON_UP , 
		SYSTEM_RBUTTON_DOWN , 

		// --------�м�------------
		SYSTEM_MBUTTON_UP , 
		SYSTEM_MBUTTON_DOWN , 

		// -------����-----------
		SYSTEM_KEY_UP , 
		SYSTEM_KEY_DOWN , 
		SYSTEM_KEY_CHAR , 

		// ------���---------
		SYSTEM_MOUSE_MOVE , 
		SYSTEM_MOUSE_WHEEL , 
		SYSTEM_MOUSE_LEAVE , 

		// -------------------------
		WINDOW_RESIZE ,
		LOG_MESSAGE , 
		INFO_MESSAGE , 
		ERROR_MESSAGE , 

		// -----------�¼�����-----------
		NUM_EVENTS

	};


	class IEvent
	{
	public:
		virtual std::wstring GetEventName() = 0;
		virtual EventType GetEventType() = 0;
	};

	typedef std::shared_ptr<IEvent> EventPtr;
};

#endif //IEvent_h