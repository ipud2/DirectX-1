#include "PCH.h"
#include "EventManager.h"

using namespace Sand;

EventManager::EventManager()
{

}

EventManager& EventManager::Get()
{
	static EventManager m_spEventManager;
	return m_spEventManager;
}

EventManager::~EventManager()
{
	for( unsigned int id = 0; id < NUM_EVENTS; id++ )
	{
		for( unsigned int i = 0; i < m_vEventListeners[id].size(); i++ )
		{
			m_vEventListeners[id][i]->SetEventManager( nullptr );
		}
	}
}

bool EventManager::AddEventListener( EventType e , IEventListener* pEventListener )
{
	if( e >= NUM_EVENTS )
	{
		return false;
	}

	m_vEventListeners[e].push_back( pEventListener );

	return true;
}

bool EventManager::DelEventListener( EventType e , IEventListener* pEventListener )
{
	// �ڶ�Ӧ���͵��¼��������б����ҵ��ü������������ڣ���ɾ��
	if( e >= NUM_EVENTS )
	{
		return false;
	}

	bool bResult = false;

	int index = -1;
	for ( std::vector<IEventListener*>::iterator it = m_vEventListeners[e].begin(); it != m_vEventListeners[e].end(); it++ )
	{
		if( *it == pEventListener )
		{
			m_vEventListeners[e].erase( it );
			bResult = true;
			break;
		}
	}

	return bResult;
}

bool EventManager::ProcessEvent( EventPtr pEvent )
{
	// ������������¼����жϸ��¼�������
	int EventID = pEvent->GetEventType();

	if( EventID >= NUM_EVENTS )
	{
		return false;
	}

	// ����ΪEventID���¼����������Ӧ���͵����м�������ʼִ�в���
	int num = ( int )m_vEventListeners[EventID].size();
	
	bool bHandled = false;
	for( int i = 0; i < num; i++ )
	{
		bHandled = m_vEventListeners[EventID][i]->HandleEvent( pEvent );

		// һ����һ������������ִ�гɹ����Ǳ��˳�
		if( bHandled )
		{
			break;
		}
	}

	return bHandled;
}