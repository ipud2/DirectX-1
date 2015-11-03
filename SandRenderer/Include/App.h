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

		// ��������
		bool ConfigureEngineComponents();
		void ShutdownEngineComponents();

		// ��ܺ���
		void Initialize();
		void Update();
		void Shutdown();

		// ����
		void TakeScreenShot();

		virtual bool HandleEvent( EventPtr pEvent );

		// Ӧ�ó�����
		std::wstring GetName();

	protected:
		Win32RenderWindow* m_pWindow;

		int m_width;
		int m_height;
		bool m_bWindow;
	};
}

#endif