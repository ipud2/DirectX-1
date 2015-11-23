#ifndef App_h
#define App_h

#include "Application.h"

#include "Win32RenderWindow.h"

#include "Renderer.h"

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

		Renderer* m_pRenderer;

		// ������
		int m_iSwapChain;

		// ��ȾĿ����ͼ
		ResourceProxyPtr m_pRenderTarget;

		// ���ģ����ͼ
		ResourceProxyPtr m_pDepthStencil;
	};
};
#endif