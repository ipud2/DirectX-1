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

		virtual void OnMouseDown( WPARAM buttonState , int x , int y );
		virtual void OnMouseUp( WPARAM buttonState , int x , int y );
		virtual void OnMouseMove( WPARAM buttonState , int x , int y );

		// ---------------------------------------------
		void CreateShaderEffect();
		void CreateSurfaceMaterial();

	protected:
		Win32RenderWindow* m_pWindow;

		Renderer* m_pRenderer;

		// ������
		int m_iSwapChain;

		// ��ȾĿ����ͼ
		ResourceProxyPtr m_pRenderTarget;
		// ���ģ����ͼ
		ResourceProxyPtr m_pDepthStencilTarget;

		// �����
		MainCamera* m_pCameras;

		ViewPerspective* m_pRenderView;

		// ----------Sky------------
		Skybox* m_pSkyBox;

		// ---------Scene Object------------
		Actor* m_pActor;
		Entity* m_pBox;				// ����
		Entity* m_pGrid;			// ƽ��
		Entity*	m_pCylinder[10];	// Բ��
		Entity* m_pSphere[10];		// ��
		Entity* m_pSkull;			// ͷ��

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

		// -----------------------Shadow Map���---------------------------------
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