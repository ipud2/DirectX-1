#ifndef Application_h
#define Application_h

#include "IWindowProc.h"

#include "IEventListener.h"

// 键盘事件
#include "EventKeyUp.h"
#include "EventKeyDown.h"
#include "EventChar.h"

// 鼠标事件
#include "EventMouseLButtonUp.h"
#include "EventMouseLButtonDown.h"
#include "EventMouseRButtonUp.h"
#include "EventMouseRButtonDown.h"
#include "EventMouseMButtonDown.h"
#include "EventMouseMButtonUp.h"
#include "EventMouseLeave.h"
#include "EventMouseMove.h"
#include "EventMouseWheel.h"


// 窗口resize事件
#include "EventWindowResize.h"

// message事件
#include "EventInfoMessage.h"
#include "EventErrorMessage.h"

// 事件管理器
#include "EventManager.h"

#include "Scene.h"

#include "Timer.h"

// 应用程序框架类
namespace Sand
{
	class Application : public IEventListener , public IWindowProc
	{
	public:
		Application();
		virtual ~Application();

		static Application* Get();

		// 引擎配置
		virtual bool ConfigureEngineComponents() = 0;
		virtual void ShutdownEngineComponents() = 0;
	
		// 框架函数
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
		virtual void MessageLoop();

		// 事件处理，处理一些我们感兴趣的事件
		virtual bool HandleEvent( EventPtr pEvent );

		// 继承自IWindowProc
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );
		virtual void BeforeRegisterWindowClass( WNDCLASSEX& wc );

		// 请求结束窗口
		void RequestTermination();

		// 截屏
		virtual void TakeScreenShot() = 0;

		// 应用程序名
		virtual std::wstring GetName() = 0;

		// 设置帧率到窗口
		void SetFrameRate( HWND hwnd );

		/*
			鼠标响应
		*/
		virtual void OnMouseDown( WPARAM buttonState , int x , int y );
		virtual void OnMouseUp( WPARAM buttonState , int x , int y );
		virtual void OnMouseMove( WPARAM buttonState , int x , int y );

		bool m_bLoop;
		bool m_bSaveScreenShot;

		EventManager m_EventManager;

		Scene* m_pScene;

		Timer* m_pTimer;

	protected:
		static Application* m_spApplication;

		POINT m_LastMousePos;
	};
};

#endif