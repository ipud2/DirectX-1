#ifndef EventWindowResize_h
#define EventWindowResize_h

#include "Engine/Event/Windows Message/EventWindowMessage.h"

namespace Sand
{
	class EventWindowResize : public EventWindowMessage
	{
	public:
		EventWindowResize( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventWindowResize();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();

		// 新的宽高 
		// m_lParam的低16位保存的是新的宽，高16位是新的高度
		int NewWidth();
		int NewHeight();
		
		bool IsMaxHide();
		bool IsMaximized();
		bool IsMaxShow();
		bool IsMinimized();
		bool IsRestored();
	};

	typedef std::shared_ptr<EventWindowResize> EventWindowResizePtr;
};
#endif // EventWindowResize_h