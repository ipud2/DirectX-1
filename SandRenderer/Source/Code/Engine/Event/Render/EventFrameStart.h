#ifndef EventFrameStart_h
#define EventFrameStart_h

#include "Engine/Event/IEvent.h"

namespace Sand
{
	class EventFrameStart : public IEvent
	{
	public:
		EventFrameStart( float dt );
		virtual ~EventFrameStart();

		virtual std::wstring GetEventName();
		virtual EventType GetEventType();

		float GetElapsed();

	protected:
		float m_fDelta;
	};

	typedef std::shared_ptr<EventFrameStart> EventFrameStartPtr;
}

#endif