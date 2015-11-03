#ifndef IEventListener_h
#define IEventListener_h

#include "PCH.h"
#include "IEvent.h"

// �����������ڼ���ĳһ�����¼��Ƿ���
// һ�������¼��������򴥷���Ӧ����
// Ҳ�����ֶ������������ͬһ���¼�
// �������¼�����ʱ����Щ������������ʼִ�д������
namespace Sand
{
	class EventManager;

	class IEventListener
	{
	public:
		IEventListener();
		~IEventListener();

		virtual bool HandleEvent( EventPtr pEvent ) = 0;

		// �����¼�
		void RequestEvent( EventType e );

		// ȡ���¼�����
		void UnRequestEvent( EventType e );

		// ���ù�����
		void SetEventManager( EventManager* pEventManager );

	protected:
		// �¼��б�
		std::vector<EventType> m_vRequestEventList;
		EventManager* m_pEventManager;
	};
};

#endif