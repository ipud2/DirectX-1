#ifndef EventManager_h
#define EventManager_h

#include "IEventListener.h"

namespace Sand
{
	class EventManager
	{
	public:
		EventManager();
		virtual ~EventManager();

		bool AddEventListener( EventType e , IEventListener* pEventListener );
		bool DelEventListener( EventType e , IEventListener* pEventListener );

		bool ProcessEvent( EventPtr pEvent );

		static EventManager* Get();

	protected:
		// ÿ���¼����ɴ��ڶ����������
		std::vector<IEventListener*> m_vEventListeners[NUM_EVENTS];

		// ����ֻ��һ��ʵ��
		static EventManager* m_spEventManager;
	};
};

#endif