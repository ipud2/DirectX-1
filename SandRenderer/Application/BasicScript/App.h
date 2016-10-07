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

#include "DirectionalLight.h"

#include "Skybox.h"

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

		// ---------------------------------------------
		void CreateShaderEffect();
		void CreateSurfaceMaterial();

	protected:
		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// ������
		int m_iSwapChain;

		int m_iViewport;

		// ��ȾĿ����ͼ
		ResourceProxyPtr m_pRenderTarget;
		// ���ģ����ͼ
		ResourceProxyPtr m_pDepthStencilTarget;

		Skybox* m_pSkyBox;

		MainCamera* m_pCameras;

		ViewPerspective* m_pRenderView;

		DirectionalLight* m_pLight;

		int m_iLinearSampler;

		ResourceProxyPtr m_pSkyTexture;

		Matrix4f m_TexTransform;
	};
};
#endif