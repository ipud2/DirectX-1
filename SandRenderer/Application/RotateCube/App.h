#ifndef App_h
#define App_h

#include "Application.h"

#include "Win32RenderWindow.h"
#include "Renderer.h"

#include "Camera.h"
#include "Scene.h"

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

		//----------------------------------------------------
		ResourceProxyPtr m_pVertexBuffer;
		ResourceProxyPtr m_pIndexBuffer;
		int m_InputLayout;

		RenderEffect m_Effect;

		Matrix4f m_WorldMatrix;
		Matrix4f m_ViewMatrix;
		Matrix4f m_ProjMatrix;
	};
};
#endif