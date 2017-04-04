#ifndef Application_h
#define Application_h

#include "IWindowProc.h"

#include "Engine/Event/IEventListener.h"

// 键盘事件
#include "Engine/Event/Windows Message/Keyboard/EventKeyUp.h"
#include "Engine/Event/Windows Message/Keyboard/EventKeyDown.h"
#include "Engine/Event/Windows Message/Keyboard/EventChar.h"

// 鼠标事件
#include "Engine/Event/Windows Message/Mouse/EventMouseLButtonUp.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseLButtonDown.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseRButtonUp.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseRButtonDown.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseMButtonDown.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseMButtonUp.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseLeave.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseMove.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseWheel.h"


// 窗口resize事件
#include "Engine/Event/Windows Message/Window/EventWindowResize.h"

// message事件
#include "Engine/Event/Notification/EventInfoMessage.h"
#include "Engine/Event/Notification/EventErrorMessage.h"

// 事件管理器
#include "Engine/Event/EventManager.h"

#include "Engine/Object/Scene/Scene.h"

#include "Engine/Utility/Timer.h"

#include "Win32RenderWindow.h"
#include "Engine/Render/DXGI/Renderer.h"

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
		virtual bool ConfigureEngineComponents();
		virtual void ShutdownEngineComponents();
	
		// 框架函数
		virtual void Initialize();
		virtual void Update();
		virtual void Shutdown();
		virtual void MessageLoop();
		virtual void UpdateEditor();

		// 事件处理，处理一些我们感兴趣的事件
		virtual bool HandleEvent( EventPtr pEvent );

		// 继承自IWindowProc
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );
		virtual void BeforeRegisterWindowClass( WNDCLASSEX& wc );

		// 请求结束窗口
		void RequestTermination();

		// 截屏
		virtual void TakeScreenShot();

		// 应用程序名
		virtual std::wstring GetName();

		// 设置帧率到窗口
		void SetFrameRate( HWND hwnd );

		bool m_bSaveScreenShot;

		Scene* m_pScene;

		Timer* m_pTimer;

	protected:
		static Application* m_spApplication;

		POINT m_LastMousePos;

		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// 交换链
		int m_iSwapChain;

		// 渲染目标视图
		ResourceProxyPtr m_pRenderTarget;
		// 深度模板视图
		ResourceProxyPtr m_pDepthStencilTarget;
	};
};

#endif