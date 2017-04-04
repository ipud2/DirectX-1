#ifndef EventKeyboardMessage_h
#define EventKeyboardMessage_h

#include "Engine/Event/Windows Message/EventWindowMessage.h"

namespace Sand
{
	class EventKeyboardMessage : public EventWindowMessage
	{
	public:
		EventKeyboardMessage( HWND hwnd , unsigned int wParam , long lParam );

		virtual ~EventKeyboardMessage();

		unsigned int GetCharacterCode();

		// ȡ0~15λ
		unsigned int GetRepeatCount();

		// ȡ16~23λ
		unsigned int GetScanCode();
		
		// 24 ~ 27λ,�ж��Ƿ����
		bool GetExtendedKey();

		// �ж�29λ�Ƿ����
		bool GetContextCode();

		// �ж�30λ�Ƿ����
		bool GetPreviousKeyState();

		// �ж�31λ�Ƿ����
		bool GetTransitionState();
	};

	typedef std::shared_ptr<EventKeyboardMessage> EventKeyboardMessagePtr;
}
#endif