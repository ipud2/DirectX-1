#ifndef EventManager_h
#define EventManager_h

#include "Engine/Event/IEventListener.h"

namespace Sand
{
	class EventManager
	{
	public:
		//EventManager();
		virtual ~EventManager();

		bool AddEventListener( EventType e , IEventListener* pEventListener );
		bool DelEventListener( EventType e , IEventListener* pEventListener );

		bool ProcessEvent( EventPtr pEvent );

		static EventManager& Get();

	protected:
		// 每类事件都可存在多个监听对象
		std::vector<IEventListener*> m_vEventListeners[NUM_EVENTS];

		// 保持只有一个实例
		
	protected:
		EventManager();
		EventManager( const EventManager& rhs );
	};
};

#endif