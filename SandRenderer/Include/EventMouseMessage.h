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

		// �ж��Ƿ���
		bool ControlKeyDown();
		bool LButtonDown();
		bool MButtonDown();
		bool RButtonDown();
		bool ShiftKeyDown();

		// ---------��ȡ���λ��---------------
		// m_wParam�ĵ�16λ
		int GetX();
		// m_lParam�ĸ�16λ
		int GetY();
	};

	typedef std::shared_ptr<EventMouseMessage> EventMouseMessagePtr;
};

#endif