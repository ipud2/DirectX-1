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

		// �µĿ�� 
		// m_lParam�ĵ�16λ��������µĿ���16λ���µĸ߶�
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