#ifndef Application_h
#define Application_h

#include "IWindowProc.h"

#include "IEventListener.h"

// 键盘事件
#include "EventKeyUp.h"
#include "EventKeyDown.h"
#include "EventChar.h"

// message事件
#include "EventInfoMessage.h"
#include "EventErrorMessage.h"

// 应用程序框架类
namespace Sand
{
	class Application : public IEventListener , public IWindowProc
	{
	public:
		Application();
		virtual ~Application();

		static Application* GetApplication();

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


		bool m_bLoop;
		bool m_bSaveScreenShot;

	protected:
		static Application* m_spApplication;
	};
};

#endif