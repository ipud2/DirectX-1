#include "PCH.h"
#include "IEventListener.h"
#include "EventManager.h"

using namespace Sand;

IEventListener::IEventListener()
{
	m_pEventManager = nullptr;
}

IEventListener::~IEventListener()
{
	SetEventManager( nullptr );
}

void IEventListener::RequestEvent( EventType e )
{
	bool bAlreadyRequest = false;

	// �������¼��Ƿ��Ѿ��������
	for( auto requestd : m_vRequestEventList )
	{
		if( requestd == e )
		{
			bAlreadyRequest = true;
			break;
		}
	}


	if( bAlreadyRequest == false )
	{
		m_vRequestEventList.push_back( e );

		if( m_pEventManager )
		{
			// Ϊ�����¼���Ӽ���
			m_pEventManager->AddEventListener( e , this );
		}
	}
}

void IEventListener::UnRequestEvent( EventType e )
{
	// ------------�ж��Ƿ��ڼ��������¼������ǣ����Ƴ�------------------
	for( std::vector<EventType>::iterator requested = m_vRequestEventList.begin(); requested != m_vRequestEventList.end(); requested++ )
	{
		if( *requested == e )
		{
			m_vRequestEventList.erase( requested );

			if( m_pEventManager )
			{
				m_pEventManager->DelEventListener( e , this );
			}
		}
	}
}

void IEventListener::SetEventManager( EventManager* pEventManager )
{
	m_pEventManager = pEventManager;
}