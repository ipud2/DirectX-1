#ifndef App_h
#define App_h

#include "Application.h"

#include "Win32RenderWindow.h"
#include "Renderer.h"

#include "Entity.h"
#include "Actor.h"
#include "ViewPerspective.h"

#include "MainCamera.h"
#include "Scene.h"

#include "Geometry.h"
#include "GeometryLoader.h"

namespace Sand
{
	class App : public Application
	{
	public:
		App();
		virtual ~App();

	public:
		// ��������
		virtual bool ConfigureEngineComponents();
		virtual void ShutdownEngineComponents();

		// ��ܺ���
		virtual void Initialize();
		virtual void Update();
		virtual void Shutdown();

		// ����
		virtual void TakeScreenShot();

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
		ResourceProxyPtr m_pDepthStencilTarget;

		ViewPerspective* m_pRenderView;
		Actor* m_pActor;
		Entity* m_pEntity[10];		// ʮ������

		GeometryPtr m_pGeometry;
		EffectPtr m_pWireEffect;

		Vector4f m_TessParams;

		MainCamera* m_pCameras;
	};
};
#endif