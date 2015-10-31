#ifndef Application_h
#define Application_h

#include "IWindowProc.h"

#include "IEventListener.h"

// �����¼�
#include "EventKeyUp.h"
#include "EventKeyDown.h"
#include "EventChar.h"

// message�¼�
#include "EventInfoMessage.h"
#include "EventErrorMessage.h"

// Ӧ�ó�������
namespace Sand
{
	class Application : public IEventListener , public IWindowProc
	{
	public:
		Application();
		virtual ~Application();

		static Application* GetApplication();

		// ��������
		virtual bool ConfigureEngineComponents() = 0;
		virtual void ShutdownEngineComponents() = 0;
	
		// ��ܺ���
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
		virtual void MessageLoop();

		// �¼���������һЩ���Ǹ���Ȥ���¼�
		virtual bool HandleEvent( EventPtr pEvent );

		// �̳���IWindowProc
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );
		virtual void BeforeRegisterWindowClass( WNDCLASSEX& wc );

		// �����������
		void RequestTermination();

		// ����
		virtual void TakeScreenShot() = 0;


		bool m_bLoop;
		bool m_bSaveScreenShot;

	protected:
		static Application* m_spApplication;
	};
};

#endif