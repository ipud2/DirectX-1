#include "ShaderResourceViewConfig.h"
#include "RenderTargetViewConfig.h"
#include "UnorderedAccessViewConfig.h"
#include "DepthStencilViewConfig.h"

#include "Texture2DConfig.h"

#include "Renderer.h"

#include "ResourceProxy.h"

using namespace Sand;

ResourceProxy::ResourceProxy()
{
	m_ResourceID = -1;

	m_ShaderResourceViewID = -1;
	m_RenderTargetViewID = -1;
	m_UnorderedAccessViewID = -1;
	m_DepthStencilViewID = -1;

	m_pShaderResourceViewConfig = nullptr;
	m_pRenderTargetViewConfig = nullptr;
	m_pDepthStencilViewConfig = nullptr;
	m_pUnorderedAccessViewConfig = nullptr;

	m_pTexture2DConfig = nullptr;
}

ResourceProxy::ResourceProxy( int ResourceID , Texture2DConfig* pConfig ,
							  Renderer* pRenderer ,
							  ShaderResourceViewConfig* pShaderResourceViewConfig ,
							  RenderTargetViewConfig* pRenderTargetViewConfig ,
							  UnorderedAccessViewConfig* pUnorderedAccessViewConfig ,
							  DepthStencilViewConfig* pDepthStencilViewConfig )

{
	// 获取资源描述
	D3D11_TEXTURE2D_DESC  desc = pConfig->GetTextureDesc();
	// 根据BindFlags为该资源创建相应的View
	CommonConstructor( desc.BindFlags , ResourceID , pRenderer , pShaderResourceViewConfig , pRenderTargetViewConfig , pUnorderedAccessViewConfig , pDepthStencilViewConfig );

	/*
		深拷贝  
		若只是m_pTexture2DConfig = pConfig的话
		则m_pTexture2DConfig只是指向了pConfig指向的那个对象
		若对象在外部被销毁，则m_pTexture2DConfig就无效了
	*/
	m_pTexture2DConfig = new Texture2DConfig;
	*m_pTexture2DConfig = *pConfig;
}

ResourceProxy::~ResourceProxy()
{

}

void ResourceProxy::CommonConstructor( UINT BindFlags , int ResourceID , 
									   Renderer* pRenderer , 
									   ShaderResourceViewConfig* pShaderResourceViewConfig , 
									   RenderTargetViewConfig* pRenderTargetViewConfig , 
									   UnorderedAccessViewConfig* pUnorderedAccessViewConfig , 
									   DepthStencilViewConfig* pDepthStencilView )
{

	// 初始化
	m_ResourceID = ResourceID;

	m_ShaderResourceViewID = 0;
	m_RenderTargetViewID = 0;
	m_DepthStencilViewID = 0;
	m_UnorderedAccessViewID = 0;

	m_pTexture2DConfig = nullptr;
	
	m_pShaderResourceViewConfig = nullptr;
	m_pRenderTargetViewConfig = nullptr;
	m_pUnorderedAccessViewConfig = nullptr;
	m_pDepthStencilViewConfig = nullptr;

	// 只创建BindFlags指定的视图
	if( ( BindFlags & D3D11_BIND_RENDER_TARGET ) != D3D11_BIND_RENDER_TARGET )
	{
		// 说明未指定D3D11_BIND_RENDER_TARGET
		m_pRenderTargetViewConfig = nullptr;
	}
	else
	{
		// 说明指定了D3D11_BIND_RENDER_TARGET
		m_pRenderTargetViewConfig = new RenderTargetViewConfig;
		*m_pRenderTargetViewConfig = *m_pRenderTargetViewConfig;

		D3D11_RENDER_TARGET_VIEW_DESC* Desc = pRenderTargetViewConfig ? &pRenderTargetViewConfig->GetDesc() : nullptr;
		m_RenderTargetViewID = pRenderer->CreateRenderTargetView( m_ResourceID , Desc );
	}

	if( ( BindFlags & D3D11_BIND_SHADER_RESOURCE ) != D3D11_BIND_SHADER_RESOURCE )
	{
		// 说明未指定D3D11_BIND_SHADER_RESOURCE
		m_pShaderResourceViewConfig = nullptr;
	}
	else
	{
		// 说明指定了D3D11_BIND_SHADER_RESOURCE
		m_pShaderResourceViewConfig = new ShaderResourceViewConfig;
		*m_pShaderResourceViewConfig = *pShaderResourceViewConfig;

		D3D11_SHADER_RESOURCE_VIEW_DESC* Desc = pShaderResourceViewConfig ? &pShaderResourceViewConfig->GetDesc() : nullptr;
		m_ShaderResourceViewID = pRenderer->CreateShaderResourceView( m_ResourceID , Desc );
	}

	if( ( BindFlags & D3D11_BIND_UNORDERED_ACCESS ) != D3D11_BIND_UNORDERED_ACCESS )
	{
		// 说明未指定D3D11_BIND_UNORDERED_ACCESS
		m_pUnorderedAccessViewConfig = nullptr;
	}
	else
	{
		// 说明指定了D3D11)_BIND_UNORDERED_ACCESS
		m_pUnorderedAccessViewConfig = new UnorderedAccessViewConfig;
		*m_pUnorderedAccessViewConfig = *pUnorderedAccessViewConfig;

		D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc = pUnorderedAccessViewConfig ? &pUnorderedAccessViewConfig->GetDesc() : nullptr;
		m_UnorderedAccessViewID = pRenderer->CreateUnorderedAccessView( m_ResourceID , Desc );
	}

	if( ( BindFlags & D3D11_BIND_DEPTH_STENCIL ) != D3D11_BIND_DEPTH_STENCIL )
	{
		// 说明未指定D3D11_BIND_DEPTH_STENCIL
		m_pDepthStencilViewConfig = nullptr;
	}
	else
	{
		// 说明指定了D3D11_BIND_DEPTH_STENCIL
		m_pDepthStencilViewConfig = new DepthStencilViewConfig;
		*m_pDepthStencilViewConfig = *pDepthStencilView;

		D3D11_DEPTH_STENCIL_VIEW_DESC* Desc = pDepthStencilView ? &pDepthStencilView->GetDesc() : nullptr;
		m_DepthStencilViewID = pRenderer->CreateDepthStencilView( m_ResourceID , Desc );
	}
}