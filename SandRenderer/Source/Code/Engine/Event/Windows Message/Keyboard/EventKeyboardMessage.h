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

		// 取0~15位
		unsigned int GetRepeatCount();

		// 取16~23位
		unsigned int GetScanCode();
		
		// 24 ~ 27位,判断是否存在
		bool GetExtendedKey();

		// 判断29位是否存在
		bool GetContextCode();

		// 判断30位是否存在
		bool GetPreviousKeyState();

		// 判断31位是否存在
		bool GetTransitionState();
	};

	typedef std::shared_ptr<EventKeyboardMessage> EventKeyboardMessagePtr;
}
#endif