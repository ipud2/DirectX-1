#ifndef IEventListener_h
#define IEventListener_h

#include "PCH.h"
#include "IEvent.h"

// 监听器是用于监听某一个类事件是否发生
// 一旦该类事件发生，则触发相应操作
// 也许会出现多个监听器监听同一类事件
// 当该类事件触发时，这些监听器都将开始执行处理操作
namespace Sand
{
	class EventManager;

	class IEventListener
	{
	public:
		IEventListener();
		~IEventListener();

		virtual bool HandleEvent( EventPtr pEvent ) = 0;

		// 请求事件
		void RequestEvent( EventType e );

		// 取消事件请求
		void UnRequestEvent( EventType e );

		// 设置管理器
		void SetEventManager( EventManager* pEventManager );

	protected:
		// 事件列表
		std::vector<EventType> m_vRequestEventList;
		EventManager* m_pEventManager;
	};
};

#endif