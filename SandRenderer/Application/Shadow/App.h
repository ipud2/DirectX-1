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

#include "SurfaceMaterial.h"

#include "DirectionalLight.h"

#include "BasicMaterial.h"

#include "Skybox.h"

#include "ShadowMapCamera.h"
#include "ViewShadowMap.h"
#include "ShadowMap.h"

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

		virtual void OnMouseDown( WPARAM buttonState , int x , int y );
		virtual void OnMouseUp( WPARAM buttonState , int x , int y );
		virtual void OnMouseMove( WPARAM buttonState , int x , int y );

		// ---------------------------------------------
		void CreateShaderEffect();
		void CreateSurfaceMaterial();

	protected:
		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// 交换链
		int m_iSwapChain;

		// 渲染目标视图
		ResourceProxyPtr m_pRenderTarget;
		// 深度模板视图
		ResourceProxyPtr m_pDepthStencilTarget;

		// 主相机
		MainCamera* m_pCameras;

		ViewPerspective* m_pRenderView;

		// ----------Sky------------
		Skybox* m_pSkyBox;

		// ---------Scene Object------------
		Actor* m_pActor;
		Entity* m_pBox;				// 盒子
		Entity* m_pGrid;			// 平面
		Entity*	m_pCylinder[10];	// 圆柱
		Entity* m_pSphere[10];		// 球
		Entity* m_pSkull;			// 头骨

		// -----------Geometry-------------
		GeometryPtr m_pBoxGeometry;
		GeometryPtr m_pGridGeometry;
		GeometryPtr m_pCylinderGeometry;
		GeometryPtr m_pSphereGeometry;
		GeometryPtr m_pSkullGeometry;

		// -----------Effect--------------
		EffectPtr m_pBoxShaderEffect;
		EffectPtr m_pGridShaderEffect;
		EffectPtr m_pCylinderShaderEffect;
		EffectPtr m_pSphereShaderEffect;
		EffectPtr m_pSkullShaderEffect;

		// ----------Material--------------
		BasicMaterial* m_pBoxMaterial;
		BasicMaterial* m_pGridMaterial;
		BasicMaterial* m_pCylinderMaterial;
		BasicMaterial* m_pSphereMaterial;
		BasicMaterial* m_pSkullMaterial;

		// ---------Texture-----------
		ResourceProxyPtr m_pBrickTexture;
		ResourceProxyPtr m_pFloorTexture;
		ResourceProxyPtr m_pStoneTexture;
		int m_iLinearSampler;

		ResourceProxyPtr m_pSkyTexture;

		Matrix4f m_TexTransform;

		// ------Light---------
		DirectionalLight* m_pLight;
		Vector4f m_AmbientLight[3];
		Vector4f m_DiffuseLight[3];
		Vector4f m_SpecularLight[3];
		Vector3f m_LightDir[3];

		// -----------------------Shadow Map相关---------------------------------
		ShadowMap* m_pShadowMap;
		ShadowMapCamera* m_pShadowMapCamera;
		ViewShadowMap* m_pShadowMapView;

		float m_BoundSphereRadius;

		int m_iShadowSamplerState;
		int m_iTessShadowSamplerState;

		int m_iRasterizerState;
	};
};
#endif