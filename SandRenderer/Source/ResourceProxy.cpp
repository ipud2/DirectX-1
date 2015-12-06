#include "PCH.h"
#include "ShaderResourceViewConfig.h"
#include "RenderTargetViewConfig.h"
#include "UnorderedAccessViewConfig.h"
#include "DepthStencilViewConfig.h"

#include "Texture2DConfig.h"

#include "Renderer.h"

#include "ResourceProxy.h"

#include "BufferConfig.h"

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
	// ��ȡ��Դ����
	D3D11_TEXTURE2D_DESC  desc = pConfig->GetTextureDesc();
	// ����BindFlagsΪ����Դ������Ӧ��View
	CommonConstructor( desc.BindFlags , ResourceID , pRenderer , pShaderResourceViewConfig , pRenderTargetViewConfig , pUnorderedAccessViewConfig , pDepthStencilViewConfig );

	/*
		���  
		��ֻ��m_pTexture2DConfig = pConfig�Ļ�
		��m_pTexture2DConfigֻ��ָ����pConfigָ����Ǹ�����
		���������ⲿ�����٣���m_pTexture2DConfig����Ч��
	*/
	m_pTexture2DConfig = new Texture2DConfig;
	*m_pTexture2DConfig = *pConfig;
}


ResourceProxy::ResourceProxy( int ResourceID , BufferConfig* pConfig , Renderer* pRenderer , ShaderResourceViewConfig* pShaderResourceViewConfig /* = nullptr  */ , RenderTargetViewConfig* pRenderTargetViewConfig /* = nullptr  */ , UnorderedAccessViewConfig* pUnorderedAccessViewConfig /* = nullptr  */ , DepthStencilViewConfig* pDepthStencilViewConfig /* = nullptr */ )
{
	// ��ȡ��Դ����
	D3D11_BUFFER_DESC desc = pConfig->GetBufferDesc();

	CommonConstructor( desc.BindFlags , ResourceID , pRenderer , pShaderResourceViewConfig , pRenderTargetViewConfig , pUnorderedAccessViewConfig , pDepthStencilViewConfig );

	/*
		���
		��ֻ��m_pBufferConfig = pConfig�Ļ�
		��m_pTexture2DConfigֻ��ָ����pConfigָ����Ǹ�����
		���������ⲿ�����٣���m_pTexture2DConfig����Ч��
	*/
	m_pBufferConfig = new BufferConfig;
	*m_pBufferConfig = *pConfig;
}

ResourceProxy::~ResourceProxy()
{

}

void ResourceProxy::CommonConstructor( UINT BindFlags , int ResourceID , 
									   Renderer* pRenderer , 
									   ShaderResourceViewConfig* pShaderResourceViewConfig , 
									   RenderTargetViewConfig* pRenderTargetViewConfig , 
									   UnorderedAccessViewConfig* pUnorderedAccessViewConfig , 
									   DepthStencilViewConfig* pDepthStencilViewConfig )
{

	// ��ʼ��
	m_ResourceID = ResourceID;

	m_ShaderResourceViewID = 0;
	m_RenderTargetViewID = 0;
	m_DepthStencilViewID = 0;
	m_UnorderedAccessViewID = 0;

	m_pTexture2DConfig = nullptr;
	m_pBufferConfig = nullptr;

	m_pShaderResourceViewConfig = nullptr;
	m_pRenderTargetViewConfig = nullptr;
	m_pUnorderedAccessViewConfig = nullptr;
	m_pDepthStencilViewConfig = nullptr;

	// ֻ����BindFlagsָ������ͼ
	if( ( BindFlags & D3D11_BIND_RENDER_TARGET ) != D3D11_BIND_RENDER_TARGET )
	{
		// ˵��δָ��D3D11_BIND_RENDER_TARGET
		m_pRenderTargetViewConfig = nullptr;
	}
	else
	{
		D3D11_RENDER_TARGET_VIEW_DESC* Desc = nullptr;

		if( pRenderTargetViewConfig )
		{
			// ˵��ָ����D3D11_BIND_RENDER_TARGET
			m_pRenderTargetViewConfig = new RenderTargetViewConfig;
			*m_pRenderTargetViewConfig = *pRenderTargetViewConfig;

			Desc = &pRenderTargetViewConfig->GetDesc();
		}
		
		m_RenderTargetViewID = pRenderer->CreateRenderTargetView( m_ResourceID , Desc );
	}

	if( ( BindFlags & D3D11_BIND_SHADER_RESOURCE ) != D3D11_BIND_SHADER_RESOURCE )
	{
		// ˵��δָ��D3D11_BIND_SHADER_RESOURCE
		m_pShaderResourceViewConfig = nullptr;
	}
	else
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC* Desc = nullptr;

		if( pShaderResourceViewConfig )
		{
			// ˵��ָ����D3D11_BIND_SHADER_RESOURCE
			m_pShaderResourceViewConfig = new ShaderResourceViewConfig;
			*m_pShaderResourceViewConfig = *pShaderResourceViewConfig;

			Desc = &pShaderResourceViewConfig->GetDesc();
		}

		m_ShaderResourceViewID = pRenderer->CreateShaderResourceView( m_ResourceID , Desc );
	}

	if( ( BindFlags & D3D11_BIND_UNORDERED_ACCESS ) != D3D11_BIND_UNORDERED_ACCESS )
	{
		// ˵��δָ��D3D11_BIND_UNORDERED_ACCESS
		m_pUnorderedAccessViewConfig = nullptr;
	}
	else
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc = nullptr;

		if( pUnorderedAccessViewConfig )
		{
			// ˵��ָ����D3D11)_BIND_UNORDERED_ACCESS
			m_pUnorderedAccessViewConfig = new UnorderedAccessViewConfig;
			*m_pUnorderedAccessViewConfig = *pUnorderedAccessViewConfig;

			Desc = &pUnorderedAccessViewConfig->GetDesc();
		}

		m_UnorderedAccessViewID = pRenderer->CreateUnorderedAccessView( m_ResourceID , Desc );
	}

	if( ( BindFlags & D3D11_BIND_DEPTH_STENCIL ) != D3D11_BIND_DEPTH_STENCIL )
	{
		// ˵��δָ��D3D11_BIND_DEPTH_STENCIL
		m_pDepthStencilViewConfig = nullptr;
	}
	else
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC* Desc = nullptr;

		if( pDepthStencilViewConfig )
		{
			// ˵��ָ����D3D11_BIND_DEPTH_STENCIL
			m_pDepthStencilViewConfig = new DepthStencilViewConfig;
			*m_pDepthStencilViewConfig = *pDepthStencilViewConfig;

			Desc = &pDepthStencilViewConfig->GetDesc();
		}

		m_DepthStencilViewID = pRenderer->CreateDepthStencilView( m_ResourceID , Desc );
	}
}

int ResourceProxy::GetResourceID()
{
	return m_ResourceID;
}

int ResourceProxy::GetDepthStencilViewID()
{
	return m_DepthStencilViewID;
}

int ResourceProxy::GetRenderTargetViewID()
{
	return m_RenderTargetViewID;
}

int ResourceProxy::GetShaderResourceViewID()
{
	return m_ShaderResourceViewID;
}

int ResourceProxy::GetUnorderedAccessViewID()
{
	return m_UnorderedAccessViewID;
}

ShaderResourceViewConfig* ResourceProxy::GetShaderResourceViewConfig()
{
	return m_pShaderResourceViewConfig;
}

DepthStencilViewConfig* ResourceProxy::GetDepthStencilViewConfig()
{
	return m_pDepthStencilViewConfig;
}

RenderTargetViewConfig* ResourceProxy::GetRenderTargetViewConfig()
{
	return m_pRenderTargetViewConfig;
}

UnorderedAccessViewConfig* ResourceProxy::GetUnorderedAccessViewConfig()
{
	return m_pUnorderedAccessViewConfig;
}

Texture2DConfig* ResourceProxy::GetTexture2dConfig()
{
	return m_pTexture2DConfig;
}

BufferConfig* ResourceProxy::GetBufferConfig()
{
	return m_pBufferConfig;
}