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
		// ÿ���¼����ɴ��ڶ����������
		std::vector<IEventListener*> m_vEventListeners[NUM_EVENTS];

		// ����ֻ��һ��ʵ��
		
	protected:
		EventManager();
		EventManager( const EventManager& rhs );
	};
};

#endif