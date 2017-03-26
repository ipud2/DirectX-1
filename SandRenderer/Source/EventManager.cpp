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
	// 在对应类型的事件监听器列表中找到该监听器，若存在，则删除
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
	// 检测这是哪类事件，判断该事件的类型
	int EventID = pEvent->GetEventType();

	if( EventID >= NUM_EVENTS )
	{
		return false;
	}

	// 类型为EventID的事件发生，则对应类型的所有监听器开始执行操作
	int num = ( int )m_vEventListeners[EventID].size();
	
	bool bHandled = false;
	for( int i = 0; i < num; i++ )
	{
		bHandled = m_vEventListeners[EventID][i]->HandleEvent( pEvent );

		// 一旦有一个监听器操作执行成功，那便退出
		if( bHandled )
		{
			break;
		}
	}

	return bHandled;
}