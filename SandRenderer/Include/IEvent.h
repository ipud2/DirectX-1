#ifndef IEvent_h
#define IEvent_h

#include "PCH.h"

namespace Sand
{
	// 定义事件类型
	enum EventType
	{
		RENDER_FRAME_START ,

		// ---------左键-----------
		SYSTEM_LBUTTON_UP ,
		SYSTEM_LBUTTON_DOWN ,

		// --------右键--------------
		SYSTEM_RBUTTON_UP , 
		SYSTEM_RBUTTON_DOWN , 

		// --------中键------------
		SYSTEM_MBUTTON_UP , 
		SYSTEM_MBUTTON_DOWN , 

		// -------键盘-----------
		SYSTEM_KEY_UP , 
		SYSTEM_KEY_DOWN , 
		SYSTEM_KEY_CHAR , 

		// ------鼠标---------
		SYSTEM_MOUSE_MOVE , 
		SYSTEM_MOUSE_WHEEL , 
		SYSTEM_MOUSE_LEAVE , 

		// -------------------------
		WINDOW_RESIZE ,
		LOG_MESSAGE , 
		INFO_MESSAGE , 
		ERROR_MESSAGE , 

		// -----------事件总数-----------
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