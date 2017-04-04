#ifndef Application_h
#define Application_h

#include "IWindowProc.h"

#include "Engine/Event/IEventListener.h"

// �����¼�
#include "Engine/Event/Windows Message/Keyboard/EventKeyUp.h"
#include "Engine/Event/Windows Message/Keyboard/EventKeyDown.h"
#include "Engine/Event/Windows Message/Keyboard/EventChar.h"

// ����¼�
#include "Engine/Event/Windows Message/Mouse/EventMouseLButtonUp.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseLButtonDown.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseRButtonUp.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseRButtonDown.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseMButtonDown.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseMButtonUp.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseLeave.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseMove.h"
#include "Engine/Event/Windows Message/Mouse/EventMouseWheel.h"


// ����resize�¼�
#include "Engine/Event/Windows Message/Window/EventWindowResize.h"

// message�¼�
#include "Engine/Event/Notification/EventInfoMessage.h"
#include "Engine/Event/Notification/EventErrorMessage.h"

// �¼�������
#include "Engine/Event/EventManager.h"

#include "Engine/Object/Scene/Scene.h"

#include "Engine/Utility/Timer.h"

#include "Win32RenderWindow.h"
#include "Engine/Render/DXGI/Renderer.h"

// Ӧ�ó�������
namespace Sand
{
	class Application : public IEventListener , public IWindowProc
	{
	public:
		Application();
		virtual ~Application();

		static Application* Get();

		// ��������
		virtual bool ConfigureEngineComponents();
		virtual void ShutdownEngineComponents();
	
		// ��ܺ���
		virtual void Initialize();
		virtual void Update();
		virtual void Shutdown();
		virtual void MessageLoop();
		virtual void UpdateEditor();

		// �¼���������һЩ���Ǹ���Ȥ���¼�
		virtual bool HandleEvent( EventPtr pEvent );

		// �̳���IWindowProc
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );
		virtual void BeforeRegisterWindowClass( WNDCLASSEX& wc );

		// �����������
		void RequestTermination();

		// ����
		virtual void TakeScreenShot();

		// Ӧ�ó�����
		virtual std::wstring GetName();

		// ����֡�ʵ�����
		void SetFrameRate( HWND hwnd );

		bool m_bSaveScreenShot;

		Scene* m_pScene;

		Timer* m_pTimer;

	protected:
		static Application* m_spApplication;

		POINT m_LastMousePos;

		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// ������
		int m_iSwapChain;

		// ��ȾĿ����ͼ
		ResourceProxyPtr m_pRenderTarget;
		// ���ģ����ͼ
		ResourceProxyPtr m_pDepthStencilTarget;
	};
};

#endif