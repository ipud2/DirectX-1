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
		// 引擎配置
		virtual bool ConfigureEngineComponents();
		virtual void ShutdownEngineComponents();

		// 框架函数
		virtual void Initialize();
		virtual void Update();
		virtual void Shutdown();

		// 截屏
		virtual void TakeScreenShot();

		virtual bool HandleEvent( EventPtr pEvent );

		// 应用程序名
		std::wstring GetName();

		// ---------------------------------------------
		void CreateShaderEffect();
		void CreateSurfaceMaterial();

	protected:
		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// 交换链
		int m_iSwapChain;

		int m_iViewport;

		// 渲染目标视图
		ResourceProxyPtr m_pRenderTarget;
		// 深度模板视图
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