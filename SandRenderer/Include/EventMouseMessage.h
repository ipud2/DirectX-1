#ifndef EventMouseMessage_h
#define EventMouseMessage_h

#include "EventWindowMessage.h"

namespace Sand
{
	class EventMouseMessage : public EventWindowMessage
	{
	public:
		EventMouseMessage( HWND hwnd , unsigned int wParam , long lParam );
		virtual ~EventMouseMessage();

		// 判断是否按下
		bool ControlKeyDown();
		bool LButtonDown();
		bool MButtonDown();
		bool RButtonDown();
		bool ShiftKeyDown();

		// ---------获取鼠标位置---------------
		// m_wParam的低16位
		int GetX();
		// m_lParam的高16位
		int GetY();
	};

	typedef std::shared_ptr<EventMouseMessage> EventMouseMessagePtr;
};

#endif