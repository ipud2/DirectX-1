#ifndef EventWindowMessage_h
#define EventWindowMessage_h

#include <Engine/PCH.h>
#include "Engine/Event/IEvent.h"

namespace Sand
{
	class EventWindowMessage : public IEvent
	{
	public:
		EventWindowMessage( HWND hwnd , unsigned int wParam , long lParam );

		virtual ~EventWindowMessage();

		HWND GetWindowHandle();
		unsigned int GetwParam();
		long GetlParam();

	protected:
		HWND m_hwnd;
		unsigned int m_wParam;
		long m_lParam;
	};

	typedef std::shared_ptr<EventWindowMessage> EventWindowMessagePtr;
};

#endif