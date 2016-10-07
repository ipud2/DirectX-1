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

	protected:
		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// 交换链
		int m_iSwapChain;

		// 渲染目标视图
		ResourceProxyPtr m_pRenderTarget;
		// 深度模板视图
		ResourceProxyPtr m_pDepthStencilTarget;

		ViewPerspective* m_pRenderView;
		Actor* m_pActor;
		Entity* m_pEntity[10];		// 十个物体

		GeometryPtr m_pGeometry;
		EffectPtr m_pWireEffect;

		Vector4f m_TessParams;

		MainCamera* m_pCameras;
	};
};
#endif