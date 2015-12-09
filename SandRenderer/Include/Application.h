#ifndef Application_h
#define Application_h

#include "IWindowProc.h"

#include "IEventListener.h"

// �����¼�
#include "EventKeyUp.h"
#include "EventKeyDown.h"
#include "EventChar.h"

// ����¼�
#include "EventMouseLButtonUp.h"
#include "EventMouseLButtonDown.h"
#include "EventMouseRButtonUp.h"
#include "EventMouseRButtonDown.h"
#include "EventMouseMButtonDown.h"
#include "EventMouseMButtonUp.h"
#include "EventMouseLeave.h"
#include "EventMouseMove.h"
#include "EventMouseWheel.h"


// ����resize�¼�
#include "EventWindowResize.h"

// message�¼�
#include "EventInfoMessage.h"
#include "EventErrorMessage.h"

// �¼�������
#include "EventManager.h"

#include "Scene.h"

#include "Timer.h"

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

		// Ӧ�ó�����
		virtual std::wstring GetName() = 0;

		// ����֡�ʵ�����
		void SetFrameRate( HWND hwnd );

		/*
			�����Ӧ
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