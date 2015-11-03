#ifndef ResourceProxy_h
#define ResourceProxy_h

#include "PCH.h"

namespace Sand
{
	class ShaderResourceViewConfig;
	class RenderTargetViewConfig;
	class UnorderedAccessViewConfig;
	class DepthStencilViewConfig;

	class Texture2DConfig;

	class Renderer;

	/*
		为各种资源根据BindFlags创建对应视图
	*/
	class ResourceProxy
	{
	public:
		ResourceProxy();

		ResourceProxy( int ResourceID , Texture2DConfig* pConfig ,
					   Renderer* pRenderer ,
					   ShaderResourceViewConfig* pShaderResourceViewConfig = nullptr ,
					   RenderTargetViewConfig* pRenderTargetViewConfig = nullptr ,
					   UnorderedAccessViewConfig* pUnorderedAccessViewConfig = nullptr ,
					   DepthStencilViewConfig* pDepthStencilViewConfig = nullptr );

		virtual ~ResourceProxy();

	public:
		int m_ResourceID;
		int m_ShaderResourceViewID;
		int m_UnorderedAccessViewID;
		int m_DepthStencilViewID;
		int m_RenderTargetViewID;

		ShaderResourceViewConfig* m_pShaderResourceViewConfig;
		RenderTargetViewConfig* m_pRenderTargetViewConfig;
		UnorderedAccessViewConfig* m_pUnorderedAccessViewConfig;
		DepthStencilViewConfig* m_pDepthStencilViewConfig;

		Texture2DConfig* m_pTexture2DConfig;

	protected:
		void CommonConstructor( UINT BindFlags , int ResourceID , Renderer* pRenderer ,
								ShaderResourceViewConfig* pShaderResourceViewConfig = nullptr ,
								RenderTargetViewConfig* pRenderTargetViewConfig = nullptr ,
								UnorderedAccessViewConfig* pUnorderedAccessViewConfig = nullptr ,
								DepthStencilViewConfig* pDepthStencilView = nullptr );
	};

	typedef std::shared_ptr<ResourceProxy> ResourceProxyPtr;
};

#endif