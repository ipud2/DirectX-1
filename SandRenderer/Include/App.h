#ifndef App_h
#define App_h

#include "Application.h"
#include "Win32RenderWindow.h"

namespace Sand
{
	class App : public Application
	{
	public:
		App();
		virtual ~App();

		// 引擎配置
		bool ConfigureEngineComponents();
		void ShutdownEngineComponents();

		// 框架函数
		void Initialize();
		void Update();
		void Shutdown();

		// 截屏
		void TakeScreenShot();

		virtual bool HandleEvent( EventPtr pEvent );

		// 应用程序名
		std::wstring GetName();

	protected:
		Win32RenderWindow* m_pWindow;

		int m_width;
		int m_height;
		bool m_bWindow;
	};
}

#endif