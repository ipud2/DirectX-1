#include "PCH.h"
#include "Renderer.h"

#include "DXGIAdapter.h"
#include "DXGIOutput.h"

#include "SwapChainConfig.h"
#include "Texture2DConfig.h"
#include "BufferConfig.h"

#include "Texture2D.h"

#include "ResourceProxy.h"

#include "ShaderResoruceView.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "UnorderedAccessView.h"

#include "SwapChain.h"

#include "Log.h"

#include "PipelineManager.h"
#include "ParameterManager.h"

#include "BlendStateConfig.h"
#include "RasterizerStateConfig.h"
#include "DepthStencilStateConfig.h"
#include "SamplerStateConfig.h"

#include "ViewPort.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "ShaderFactory.h"

#include "VertexShader.h"
#include "HullShader.h"
#include "DomainShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "ComputeShader.h"

#include "ShaderReflectionGenerator.h"

#include "FileSystem.h"

#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

#include "Task.h"

#pragma comment(lib , "d3d11.lib")
#pragma comment(lib , "DXGI.lib")

using namespace Sand;
using Microsoft::WRL::ComPtr;

Renderer* Renderer::m_spRenderer = 0;

Renderer::Renderer()
{
	if( m_spRenderer == 0 )
	{
		m_spRenderer = this;
	}


	m_DriveType = D3D_DRIVER_TYPE_NULL;

	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	m_pPipelineManager = nullptr;
	m_pParameterManager = nullptr;
}

Renderer::~Renderer()
{

}

Renderer* Renderer::Get()
{
	return m_spRenderer;
}

bool Renderer::Initialize( D3D_DRIVER_TYPE DriverType , D3D_FEATURE_LEVEL FeatureLevel )
{
	// 创建Device

	HRESULT hr = S_OK;

	ComPtr<IDXGIFactory1> pFactory;
	hr = CreateDXGIFactory( __uuidof( IDXGIFactory ) , reinterpret_cast< void** >( pFactory.GetAddressOf() ) );

	ComPtr<IDXGIAdapter1> pCurrentAdapter;
	std::vector<DXGIAdapter> vAdapter;

	while( pFactory->EnumAdapters1( static_cast< UINT >( vAdapter.size() ) , pCurrentAdapter.ReleaseAndGetAddressOf() ) != DXGI_ERROR_NOT_FOUND )
	{
		vAdapter.push_back( pCurrentAdapter );

		DXGI_ADAPTER_DESC1 desc;
		pCurrentAdapter->GetDesc1( &desc );

		// 输出adapter描述(通常是显卡)
		Log::Get().Error( desc.Description );
	}

	UINT CreateDeviceFlags = 0;

	DeviceContextComPtr pContext;

	D3D_FEATURE_LEVEL level[] = { FeatureLevel };
	D3D_FEATURE_LEVEL CreateLevel;

	if( DriverType == D3D_DRIVER_TYPE_HARDWARE )
	{
		for( auto pAdapter : vAdapter )
		{
			hr = D3D11CreateDevice( pAdapter.m_pAdapter.Get() ,
									D3D_DRIVER_TYPE_UNKNOWN ,
									nullptr ,
									CreateDeviceFlags ,
									level ,
									1 ,
									D3D11_SDK_VERSION ,
									m_pDevice.GetAddressOf() ,
									&CreateLevel ,
									pContext.GetAddressOf() );

			if( hr == S_OK )
			{
				break;
			}
		}
	}
	else
	{
		hr = D3D11CreateDevice( nullptr ,
								DriverType ,
								nullptr ,
								CreateDeviceFlags ,
								level ,
								1 ,
								D3D11_SDK_VERSION ,
								m_pDevice.GetAddressOf() ,
								&CreateLevel ,
								pContext.GetAddressOf() );
	}

	if( FAILED( hr ) )
	{
		return false;
	}

	// 获取debug接口
	hr = m_pDevice.CopyTo( m_pDebugger.GetAddressOf() );

	if( FAILED( hr ) )
	{
		// 输出错误信息
		Log::Get().Error( L"can't getch ID3D11Debug Interface from Devices" );
	}

	m_FeatureLevel = m_pDevice->GetFeatureLevel();

	m_pPipelineManager = new PipelineManager;
	m_pPipelineManager->SetDeviceContext(pContext , m_FeatureLevel); 
	m_pParameterManager = new ParameterManager;

	// ----------------------初始化默认状态------------------------------------
	// 将光栅化阶段和输出装配阶段的状态设为默认状态，并且使得Renderer中相应状态容器的0号索引的状态为默认值
	RasterizerStateConfig RSConfig;
	m_pPipelineManager->GetRasterizerStageRef().DesiredState.RasterizerStates.SetState( CreateRasterizerState( &RSConfig ) );

	BlendStateConfig BSConfig;
	m_pPipelineManager->GetOutputMergeStageRef().DesiredState.BlendStates.SetState( CreateBlendState( &BSConfig ) );

	DepthStencilStateConfig DSSConfig;
	m_pPipelineManager->GetOutputMergeStageRef().DesiredState.DepthStencilStates.SetState( CreateDepthStencilState( &DSSConfig ) );

	/*
		添加一个默认的视图对象

		为何要添加这个默认对象？
		比如shader中：
		TextureCube SkyboxTexture; 用于实现物体对天空的反射
		但是并不是所有物体都需要反射天空
		这个时候就没必要所有的物体都创建一张纹理，然后传递进去，因此可以使用该默认值
		这样我们就只需为需要反射天空的物体添加天空纹理即可

		修改各视图对象默认id
	*/
	m_vShaderResourceViews.emplace_back( ShaderResourceViewComPtr() );
	m_vRenderTargetViews.emplace_back( RenderTargetViewComPtr() );
	m_vUnorderedAccessViews.emplace_back( UnorderedAccessViewComPtr() );
	m_vDepthStencilViews.emplace_back( DepthStencilViewComPtr() );

	return true;
}

void Renderer::Shutdown()
{
	// 释放PipelineManager对象
	SAFE_DELETE( m_pPipelineManager );

	// -------------Resource View--------------------
	m_vShaderResourceViews.clear();
	m_vRenderTargetViews.clear();
	m_vDepthStencilViews.clear();
	m_vUnorderedAccessViews.clear();

	// -------------------State------------------
	m_vBlendStates.clear();
	m_vRasterizerStates.clear();
	m_vDepthStencilStates.clear();
	m_vSamplerStates.clear();

	// -------View Port---------------------
	m_vViewPorts.clear();

	// -----------Input Layout-----------------
	m_vInputLayouts.clear();

	// ------------Resource----------------------
	for( auto pResource : m_vResource )
	{
		delete pResource;
	}

	// -----------SwapChain-------------------
	for( auto pSwapChain : m_vSwapChain )
	{
		if( pSwapChain->m_SwapChain!= nullptr )
		{
			pSwapChain->m_SwapChain->SetFullscreenState( false , NULL );
		}

		delete pSwapChain;
	}
}

void Renderer::Present( int SwapChainID /* = -1  */ , UINT SyncInterval /* = 0  */ , UINT PresentFlags /* = 0 */ )
{
	unsigned int index = static_cast< unsigned int >( SwapChainID );

	if( index < m_vSwapChain.size() )
	{
		// 获取相应的交换链显示图像
		SwapChain* pSwapChain = m_vSwapChain[SwapChainID];

		HRESULT hr = pSwapChain->m_SwapChain->Present( SyncInterval , PresentFlags );
	}
	else
	{
		// 输出错误信息
		Log::Get().Error( L"交换链索引无效！" );
	}
}

D3D_FEATURE_LEVEL Renderer::GetAvailableFeatureLevel( D3D_DRIVER_TYPE DriverType )
{
	D3D_FEATURE_LEVEL FeatureLevel;
	HRESULT hr;

	if( m_pDevice )
	{
		FeatureLevel = m_pDevice->GetFeatureLevel();
	}
	else
	{
		// 创建Device
		hr = D3D11CreateDevice(
			nullptr ,
			DriverType ,
			nullptr ,
			0 ,
			nullptr ,
			0 ,
			D3D11_SDK_VERSION ,
			nullptr ,
			&FeatureLevel ,
			nullptr
			);

		if( FAILED( hr ) )
		{
			Log::Get().Error( L"GetAvailableFeatureLevel函数创建Device失败" );
		}
	}

	return FeatureLevel;
}

D3D_FEATURE_LEVEL Renderer::GetCurrentFeatureLevel()
{
	return m_FeatureLevel;
}

UINT64 Renderer::GetAvailableVideoMemory()
{
	ComPtr<IDXGIDevice> pDXGIDevice;
	ComPtr<IDXGIAdapter> pDXGIAdapter;

	HRESULT hr = m_pDevice.CopyTo( pDXGIDevice.GetAddressOf() );
	pDXGIDevice->GetAdapter( pDXGIAdapter.GetAddressOf() );

	DXGI_ADAPTER_DESC AdapterDesc;
	pDXGIAdapter->GetDesc( &AdapterDesc );

	UINT64 AvaliableVideoMemory = 0;

	if( AdapterDesc.DedicatedVideoMemory )
	{
		// 显存大小
		AvaliableVideoMemory = AdapterDesc.DedicatedVideoMemory;
	}
	else
	{
		// 共享的系统内存数，系统内存中可以被adapter使用的最大值
		AvaliableVideoMemory = AdapterDesc.SharedSystemMemory;
	}

	return AvaliableVideoMemory;
}

int Renderer::CreateSwapChain( SwapChainConfig* pConfig )
{
	ComPtr<IDXGIDevice> pDXGIDevice;
	HRESULT hr = m_pDevice.CopyTo( pDXGIDevice.GetAddressOf() );

	ComPtr<IDXGIAdapter> pDXGIAdapter;
	hr = pDXGIDevice->GetParent( __uuidof( IDXGIAdapter ) , reinterpret_cast< void** >( pDXGIAdapter.GetAddressOf() ) );

	ComPtr<IDXGIFactory> pFactory;
	pDXGIAdapter->GetParent( __uuidof( IDXGIFactory ) , reinterpret_cast< void** >( pFactory.GetAddressOf() ) );


	// 创建交换链对象
	ComPtr<IDXGISwapChain> pSwapChain;
	hr = pFactory->CreateSwapChain( m_pDevice.Get() , &pConfig->m_State , pSwapChain.GetAddressOf() );


	if( FAILED( hr ) )
	{
		Log::Get().Error( L"交换链创建失败" );

		return -1;
	}

	// 获取back buffer接口
	Texturte2DComPtr BackBuffer;
	hr = pSwapChain->GetBuffer( 0 , __uuidof( ID3D11Texture2D ) , reinterpret_cast< void** >( BackBuffer.GetAddressOf() ) );

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"交换链相关联的缓存获取失败" );

		return -1;
	}
	
	// 保存资源对象
	int ResoureID = StoreNewResource( new Texture2D( BackBuffer ) );

	
	// 获取back buffer的描述，以便为其创建相应的view
	// swap chain的back buffer的bindflags为D3D11_BIND_RENDER_TARGET
	Texture2DConfig TextureConfig;
	BackBuffer->GetDesc( &TextureConfig.m_State );

	// 为该资源根据BindFlags创建相应的视图
	ResourceProxyPtr proxy( new ResourceProxy( ResoureID , &TextureConfig , this ) );

	m_vSwapChain.push_back( new SwapChain( pSwapChain , proxy ) );

	return ( ( int )m_vSwapChain.size() - 1 );
}

void Renderer::ResizeSwapChain( int SID , int width , int height )
{
	unsigned int index = static_cast< unsigned int >( SID );

	if ( !( index < m_vSwapChain.size() ) )
	{
		Log::Get().Error( L"Error trying to resize swap chain" );
		return;
	}

	SwapChain* pSwapChain = m_vSwapChain[index];

	Texture2D* pBackBuffer = reinterpret_cast< Texture2D* >( GetResourceByIndex( pSwapChain->m_ResourceProxy->GetResourceID() ) );
	pBackBuffer->m_Texture.Reset();

	ResourceProxyPtr proxy = GetSwapChainResource( index );

	RenderTargetView& RTV = m_vRenderTargetViews[pSwapChain->m_ResourceProxy->GetRenderTargetViewID()];

	DXGI_SWAP_CHAIN_DESC SwapDesc;
	pSwapChain->GetResoruce()->GetDesc( &SwapDesc );

	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
	RTV.GetRenderTargetView()->GetDesc( &RTVDesc );
	RTV.m_RenderTargetView.Reset();

	/*DepthStencilView& DSV = m_vDepthStencilViews[pSwapChain->m_ResourceProxy->GetDepthStencilViewID()];
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
	DSV.Get()->GetDesc( &DSVDesc );
	DSV.m_DepthStencilView.Reset();*/

	HRESULT hr = pSwapChain->GetResoruce()->ResizeBuffers( 1 , width , height , DXGI_FORMAT_R8G8B8A8_UNORM , 0 );
	if ( FAILED( hr ) )
	{
		return;
	}

	hr = pSwapChain->GetResoruce()->GetBuffer( 0 , __uuidof( ID3D11Texture2D ) , reinterpret_cast< void** >( pBackBuffer->m_Texture.GetAddressOf() ) );

	if ( FAILED( hr ) )
	{
		Log::Get().Error( L"交换链相关联的缓存获取失败" );

		return;
	}

	hr = m_pDevice->CreateRenderTargetView( pBackBuffer->GetResource() , &RTVDesc , RTV.m_RenderTargetView.GetAddressOf() );
	if ( FAILED( hr ) )
	{
		Log::Get().Error( L"RenderTarget创建失败" );

		return;
	}

	/*hr = m_pDevice->CreateDepthStencilView( pBackBuffer->GetResource() , &DSVDesc , DSV.m_DepthStencilView.GetAddressOf() );
	if ( FAILED( hr ) )
	{
		Log::Get().Write( L"DepthStencil创建失败" );
		
		return;
	}*/
}

int Renderer::CreateShaderResourceView( int ResourceID , D3D11_SHADER_RESOURCE_VIEW_DESC* Desc )
{
	// 获取资源对象， 判断资源对象是否为nullptr
	// 判断资源对象对应的D3D资源是否存在
	// 若存在，则为其创建相应的视图
	// 若视图创建成功，则将视图保存至视图仓库
	// 返回其索引

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			ShaderResourceViewComPtr pShaderResourceView;
			HRESULT hr = m_pDevice->CreateShaderResourceView( pRawResource , Desc , pShaderResourceView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vShaderResourceViews.push_back( pShaderResourceView );
				return ( ( int )m_vShaderResourceViews.size() - 1 );
			}
		}
	}

	// 创建失败返回-1
	return -1;
}

int Renderer::CreateRenderTargetView( int ResourceID , D3D11_RENDER_TARGET_VIEW_DESC* Desc )
{
	// 获取资源对象， 判断资源对象是否为nullptr
	// 判断资源对象对应的D3D资源是否存在
	// 若存在，则为其创建相应的视图
	// 若视图创建成功，则将视图保存至视图仓库
	// 返回其索引

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			RenderTargetViewComPtr pRenderTargetView;
			HRESULT hr = m_pDevice->CreateRenderTargetView( pRawResource , Desc , pRenderTargetView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vRenderTargetViews.push_back( pRenderTargetView );
				return ( ( int )m_vRenderTargetViews.size() - 1 );
			}
		}
	}

	// 创建失败返回-1
	return -1;
}

int Renderer::CreateDepthStencilView( int ResourceID , D3D11_DEPTH_STENCIL_VIEW_DESC* Desc )
{
	// 获取资源对象， 判断资源对象是否为nullptr
	// 判断资源对象对应的D3D资源是否存在
	// 若存在，则为其创建相应的视图
	// 若视图创建成功，则将视图保存至视图仓库
	// 返回其索引

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			DepthStencilViewComPtr pDepthStencilView;
			HRESULT hr = m_pDevice->CreateDepthStencilView( pRawResource , Desc , pDepthStencilView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vDepthStencilViews.push_back( pDepthStencilView );
				return ( ( int )m_vDepthStencilViews.size() - 1 );
			}
		}
	}

	// 创建失败返回-1
	return -1;
}

int Renderer::CreateUnorderedAccessView( int ResourceID , D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc )
{
	// 获取资源对象， 判断资源对象是否为nullptr
	// 判断资源对象对应的D3D资源是否存在
	// 若存在，则为其创建相应的视图
	// 若视图创建成功，则将视图保存至视图仓库
	// 返回其索引

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			UnorderedAccessViewComPtr pUnorderedAccessView;
			HRESULT hr = m_pDevice->CreateUnorderedAccessView( pRawResource , Desc , pUnorderedAccessView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vUnorderedAccessViews.push_back( pUnorderedAccessView );
				return ( ( int )m_vUnorderedAccessViews.size() - 1 );
			}
		}
	}

	// 创建失败返回-1
	return -1;
}

int Renderer::StoreNewResource( Resource* pResource )
{
	// 从资源列表中查找是否有元素为nullptr的位置，若存在，则将该资源插入其位置
	// 若无，则将该资源插入最后

	int index = GetUnusedResourceIndex();

	if( index == -1 )
	{
		// 说明资源容器中并无元素为nullptr，因此将该资源插入列表最后方
		m_vResource.push_back( pResource );
		index = ( int )m_vResource.size() - 1;
	}
	else
	{
		m_vResource[index] = pResource;
	}

	int innerID = ( int )pResource->GetInnerID() << 16;
	index = index + innerID;

	return index;
}

Resource* Renderer::GetResourceByIndex( int index )
{
	Resource* pResource = nullptr;

	
	int inner = ( index & 0xffff0000 ) >> 16;
	unsigned int id = static_cast<unsigned int>( index & 0xffff );

	if( id < m_vResource.size() )
	{
		// 根据ID获取相应的Resource
		pResource = m_vResource[id];

		// 验证inner ID
		if( pResource->GetInnerID() != inner )
		{
			// 输出错误信息
			Log::Get().Error( L"资源的InnerID与索引的InnerID不一致" );
		}
	}

	return pResource;
}

void Sand::Renderer::DeleteResource( int index )
{
	// 获取该资源对象
	Resource* pResource = GetResourceByIndex( index );

	if( pResource != nullptr )
	{
		delete pResource;

		m_vResource[index & 0xffff] = nullptr;
	}
}

Sand::ResourceProxyPtr Sand::Renderer::CreateTexture2D( Texture2DConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData ,
														ShaderResourceViewConfig* pShaderResourceViewConfig /*= NULL */ ,
														RenderTargetViewConfig* pRenderTargetViewConfig /*= NULL */ ,
														UnorderedAccessViewConfig* pUnorderedAccessViewConfig /*= NULL */ ,
														DepthStencilViewConfig* pDepthStencilViewConfig /*= NULL */ )
{
	// 创建ID3D11Texture2D纹理对象
	Texturte2DComPtr pTexture;
	HRESULT hr = m_pDevice->CreateTexture2D( &( pConfig->m_State ) , pData , pTexture.GetAddressOf() );

	if( pTexture )
	{
		// 创建Texture2D对象
		Texture2D* pTex = new Texture2D( pTexture );
		pTex->SetDesiredDescription( pConfig->GetTextureDesc() );

		// 保存纹理对象
		int id = StoreNewResource( pTex );

		// 创建相应视图
		ResourceProxyPtr Proxy( new ResourceProxy( id , pConfig , this , pShaderResourceViewConfig , pRenderTargetViewConfig , pUnorderedAccessViewConfig , pDepthStencilViewConfig ) );

		return Proxy;
	}

	return ResourceProxyPtr( new ResourceProxy() );
}

RasterizerStateComPtr Renderer::GetRasterizerState( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	if( index >= 0 && index < m_vRasterizerStates.size())
	{
		return m_vRasterizerStates[index];
	}
	else
	{
		// 默认光栅化状态
		return m_vRasterizerStates[0];
	}
}

SamplerStateComPtr Renderer::GetSamplerState( int index )
{	
	// Sampler State不存在默认状态

	return m_vSamplerStates[index];
}

const ViewPort& Sand::Renderer::GetViewPort( int index )
{
	unsigned int id = static_cast< unsigned int >( index );

	assert( id < m_vViewPorts.size() );

	return m_vViewPorts[id];
}

Sand::RenderTargetView Sand::Renderer::GetRenderTargetViewByIndex( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	assert( index < m_vRenderTargetViews.size() );

	return m_vRenderTargetViews[index];
}

Sand::DepthStencilView Sand::Renderer::GetDepthStencilViewByIndex( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	assert( index < m_vDepthStencilViews.size() );

	return m_vDepthStencilViews[index];
}

Sand::UnorderedAccessView Sand::Renderer::GetUnorderedAccessViewByIndex( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	assert( index < m_vUnorderedAccessViews.size() );

	return m_vUnorderedAccessViews[index];
}

ShaderResourceView Renderer::GetShaderResourceViewByIndex( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	assert( index < m_vShaderResourceViews.size() );

	return m_vShaderResourceViews[index];
}
Sand::BlendStateComPtr Sand::Renderer::GetBlendState( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	if( index < m_vBlendStates.size() )
	{
		return m_vBlendStates[index];
	}
	else
	{
		return m_vBlendStates[0];
	}
}

Sand::DepthStencilStateComPtr Sand::Renderer::GetDepthStencilState( int id )
{
	unsigned int index = static_cast< unsigned int >( id );

	if( index < m_vDepthStencilStates.size() )
	{
		return m_vDepthStencilStates[index];
	}
	else
	{
		return m_vDepthStencilStates[0];
	}
}

int Sand::Renderer::CreateBlendState( BlendStateConfig* pConfig )
{
	BlendStateComPtr pState;
	HRESULT hr = m_pDevice->CreateBlendState( dynamic_cast< D3D11_BLEND_DESC* >( pConfig ) , pState.GetAddressOf() );

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"创建BlendState失败" );
		return -1;
	}

	m_vBlendStates.push_back( pState );

	return ( int )m_vBlendStates.size() - 1;
}

int Sand::Renderer::CreateDepthStencilState( DepthStencilStateConfig* pConfig )
{
	DepthStencilStateComPtr pState;
	HRESULT hr = m_pDevice->CreateDepthStencilState( dynamic_cast< D3D11_DEPTH_STENCIL_DESC* >( pConfig ) , pState.GetAddressOf() );

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"创建深度模板状态失败" );

		return -1;
	}

	m_vDepthStencilStates.push_back( pState );

	return ( ( int )m_vDepthStencilStates.size() - 1 );
}

int Sand::Renderer::CreateRasterizerState( RasterizerStateConfig* pConfig )
{
	RasterizerStateComPtr pState;
	HRESULT hr = m_pDevice->CreateRasterizerState( dynamic_cast< D3D11_RASTERIZER_DESC* >( pConfig ) , pState.GetAddressOf() );

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"创建光栅化状态失败" );
		return -1;
	}

	m_vRasterizerStates.push_back( pState );

	return ( ( int )m_vRasterizerStates.size() - 1 );
}

int Sand::Renderer::CreateSamplerState( SamplerStateConfig* pConfig )
{
	SamplerStateComPtr pState;
	HRESULT hr = m_pDevice->CreateSamplerState( dynamic_cast< D3D11_SAMPLER_DESC* >( pConfig ) , pState.GetAddressOf() );

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"创建采样状态失败" );

		return -1;
	}

	m_vSamplerStates.push_back( pState );

	return ( ( int )m_vSamplerStates.size() - 1 );
}

int Sand::Renderer::CreateViewPort( D3D11_VIEWPORT viewport )
{
	m_vViewPorts.emplace_back( viewport );

	return ( ( int )m_vViewPorts.size() - 1 );
}

void Sand::Renderer::ResizeViewport( int ID , UINT width , UINT height )
{
	unsigned int index = static_cast< unsigned int >( ID );

	if ( !( index < m_vViewPorts.size() ) )
	{
		Log::Get().Error( L"Error trying to resize viewport" );
	}

	ViewPort& pViewport = m_vViewPorts[index];
	pViewport.m_ViewPort.Width = static_cast< float >( width );
	pViewport.m_ViewPort.Height = static_cast< float >( height );
}

ResourceProxyPtr Renderer::LoadTexture( std::wstring filename , bool sRGB /*= false */ )
{
	ComPtr<ID3D11Resource> pResource;

	FileSystem fs;
	filename = fs.GetTextureFolder() + filename;

	if ( m_vExternalTexture[filename] != nullptr )
	{
		// 即该文件名对应的纹理已存在
		return m_vExternalTexture[filename];
	}

	// check whether file format is dds
	std::wstring extension = filename.substr( filename.size() - 3 , 3 );
	// transform to lower case letters
	std::transform( extension.begin() , extension.end() , extension.begin() , ::tolower );

	HRESULT hr = S_OK;

	if( extension == L"dds" )
	{
		hr = DirectX::CreateDDSTextureFromFile( m_pDevice.Get() , 
												filename.c_str() , 
												pResource.GetAddressOf() , 
												nullptr );
	}
	else
	{
		hr = DirectX::CreateWICTextureFromFileEx( m_pDevice.Get() , 
												  m_pPipelineManager->GetDeviceContext() , 
												  filename.c_str() , 
												  0 , 
												  D3D11_USAGE_DEFAULT , 
												  D3D11_BIND_SHADER_RESOURCE , 
												  0 , 
												  0 , 
												  sRGB , 
												  pResource.GetAddressOf() , 
												  0 );
	}

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"Failed to load texture from file" );

		return ResourceProxyPtr( new ResourceProxy );
	}


	ComPtr<ID3D11Texture2D> pTexture;
	pResource.CopyTo( pTexture.GetAddressOf() );

	int ResourceID = StoreNewResource( new Texture2D( pTexture ) );

	Texture2DConfig TextureConfig;
	pTexture->GetDesc( &TextureConfig.m_State );

	m_vExternalTexture[filename] = ResourceProxyPtr( new ResourceProxy( ResourceID , &TextureConfig , this ) );

	return m_vExternalTexture[filename];
}

ResourceProxyPtr Renderer::LoadTexture( void* pData , SIZE_T SizeInByte )
{
	ComPtr<ID3D11Resource> pResource;

	HRESULT hr = DirectX::CreateWICTextureFromMemory( m_pDevice.Get() ,
													  m_pPipelineManager->m_pContext.Get() ,
													  static_cast< uint8_t* >( pData ) ,
													  SizeInByte ,
													  pResource.GetAddressOf() ,
													  0 );

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"Failed to load texture from file" );
		return ResourceProxyPtr( new ResourceProxy );
	}

	ComPtr<ID3D11Texture2D> pTexture;
	pResource.CopyTo( pTexture.GetAddressOf() );

	// store resource
	int ResourceID = StoreNewResource( new Texture2D( pTexture ) );

	Texture2DConfig TextureConfig;
	pTexture->GetDesc( &TextureConfig.m_State );

	return ( ResourceProxyPtr( new ResourceProxy( ResourceID , &TextureConfig , this ) ) );
}

ConstantBuffer* Renderer::GetConstantBufferByIndex( int index )
{
	Resource* pResource = GetResourceByIndex( index );

	if( pResource != nullptr )
	{
		if( pResource->GetType() == RT_CONSTANT_BUFFER )
		{
			return reinterpret_cast< ConstantBuffer* >( pResource );
		}
	}
	
	return nullptr;
}

ResourceProxyPtr Renderer::CreateConstantBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData )
{
	BufferComPtr pBuffer;
	HRESULT hr = m_pDevice->CreateBuffer( &pConfig->GetBufferDesc() , pData , pBuffer.GetAddressOf() );

	if( pBuffer )
	{
		// 将资源保存到资源仓库中
		// 我们需要创建ConstantBuffer对象，因此ConstantBuffer类是继承自Buffer类，Buffer类是继承自Resource类
		ConstantBuffer* pCBuffer = new ConstantBuffer( pBuffer );
		pCBuffer->SetDesiredBufferDesc( pConfig->GetBufferDesc() );

		int ResourceID = StoreNewResource( pCBuffer );

		// 创建ResourceProxyPtr
		return ResourceProxyPtr( new ResourceProxy( ResourceID , pConfig , this ) );
	}

	return ResourceProxyPtr( new ResourceProxy() );
}

int Renderer::CreateInputLayout( std::vector<D3D11_INPUT_ELEMENT_DESC>& InputElementDesc , int ShaderID )
{
	// 将InputElementDesc中的数据全部拷贝出来
	D3D11_INPUT_ELEMENT_DESC* pInputElementDesc = new D3D11_INPUT_ELEMENT_DESC[InputElementDesc.size()];
	for( int i = 0; i < ( int )InputElementDesc.size(); i++ )
	{
		pInputElementDesc[i] = InputElementDesc[i];
	}

	// 获取shader的CompilerShader
	Shader* pShader = GetShader( ShaderID );
	ID3DBlob* pCompiledShader = pShader->GetCompiledShader();

	// 创建ID3D11InputLayout对象
	InputLayoutComPtr pInputLayout;
	HRESULT hr = m_pDevice->CreateInputLayout( pInputElementDesc , ( UINT )InputElementDesc.size() , pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , pInputLayout.GetAddressOf() );

	delete[] pInputElementDesc;

	if( FAILED( hr ) )
	{
		Log::Get().Error( L"创建InputLayout失败！！" );
	}

	m_vInputLayouts.push_back( pInputLayout );
	
	return ( ( int )m_vInputLayouts.size() - 1 );
}

ResourceProxyPtr Renderer::GetSwapChainResource( int index )
{
	unsigned int id = static_cast< unsigned int >( index );

	if( id < m_vSwapChain.size() )
	{
		return m_vSwapChain[id]->m_ResourceProxy;
	}

	Log::Get().Error( L"交换链索引无效" );

	// 返回一个默认ResourceProxyPtr对象
	// 资源，资源视图都为nullptr
	return ResourceProxyPtr( new ResourceProxy() );
}

void Renderer::DeleteResource( ResourceProxyPtr pResource )
{
	DeleteResource( pResource->GetResourceID() );
}

int Renderer::GetUnusedResourceIndex()
{
	int index = -1;

	for( int i = 0; i < ( int )m_vResource.size(); i++ )
	{
		if( m_vResource[i] == nullptr )
		{
			index = i;
			break;
		}
	}

	return index;
}

ResourceProxyPtr Renderer::CreateVertexBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData )
{
	BufferComPtr pBuffer;
	HRESULT hr = m_pDevice->CreateBuffer( &pConfig->GetBufferDesc() , pData , pBuffer.GetAddressOf() );

	if( pBuffer )
	{
		// 创建VertexBuffe类对象，因为VertexBuffer是继承自Buffer，Buffer是继承自Resource
		// 因此我们可以将其保存到资源仓库中
		VertexBuffer* pVertexBuffer = new VertexBuffer( pBuffer );
		pVertexBuffer->SetDesiredBufferDesc( pConfig->GetBufferDesc() );

		// 保存Vertex Buffer到资源仓库
		int ResourceID = StoreNewResource( pVertexBuffer );

		return ResourceProxyPtr( new ResourceProxy( ResourceID , pConfig , this ) );
	}

	return ResourceProxyPtr( new ResourceProxy() );
}

ResourceProxyPtr Renderer::CreateIndexBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData )
{
	// 创建Index Buffer
	BufferComPtr pBuffer;
	HRESULT hr = m_pDevice->CreateBuffer( &pConfig->GetBufferDesc() , pData , pBuffer.GetAddressOf() );

	if( pBuffer )
	{
		// 创建Index Buffer类对象，因为Index Buffer是继承自Buffer , Buffer是继承自Resource
		// 因此我们可以将其保存到资源仓库中
		IndexBuffer* pIndexBuffer = new IndexBuffer( pBuffer );
		pIndexBuffer->SetDesiredBufferDesc( pConfig->GetBufferDesc() );

		// 保存至资源仓库
		int ResourceID = StoreNewResource( pIndexBuffer );

		return ResourceProxyPtr( new ResourceProxy( ResourceID , pConfig , this ) );
	}

	return ResourceProxyPtr( new ResourceProxy() );
}

PipelineManager* Renderer::GetPipelineManagerRef()
{
	return m_pPipelineManager;
}

IParameterManager* Renderer::GetParameterManagerRef()
{
	return m_pParameterManager;
}

Shader* Renderer::GetShader( int index )
{
	unsigned int ID = static_cast< unsigned int >( index );

	if( ID < m_vShaders.size() )
	{
		return m_vShaders[ID];
	}
	else
	{
		return nullptr;
	}
	
}

InputLayoutComPtr Renderer::GetInputLayout( int index )
{
	return m_vInputLayouts[index];
}

VertexBuffer* Renderer::GetVertexBufferByIndex( int ID )
{
	VertexBuffer* pResult = nullptr;

	Resource* pResource = GetResourceByIndex( ID );

	if( pResource != nullptr )
	{
		if( pResource->GetType() != RT_VERTEXBUFFER )
		{
			Log::Get().Error( L"Trying to access a non-vertex buffer resource!!" );
		}
		else
		{
			pResult = reinterpret_cast< VertexBuffer* >( pResource );
		}
	}

	return pResult;
}

IndexBuffer* Renderer::GetIndexBufferByIndex( int ID )
{
	IndexBuffer* pResult = nullptr;

	Resource* pResource = GetResourceByIndex( ID );

	if( pResource != nullptr )
	{
		if( pResource->GetType() != RT_INDEXBUFFER )
		{
			Log::Get().Error( L"Trying to access a non-index buffer resource!!!" );
		}
		else
		{
			pResult = reinterpret_cast< IndexBuffer* >( pResource );
		}
	}

	return pResult;
}

int Renderer::LoadShader( ShaderType Type , std::wstring& Filename , std::wstring& Function , std::wstring& Model , bool EnableLogging )
{
	return LoadShader( Type , Filename , Function , Model , nullptr , EnableLogging );
}

int Renderer::LoadShader( ShaderType Type , std::wstring& Filename , std::wstring& Function , std::wstring& Model , const D3D_SHADER_MACRO* pDefines , bool EnableLogging )
{
	// ------------------------------------------------------------------
	// 首先判断该shader是否已经存在
	for( unsigned int i = 0; i < m_vShaders.size(); i++ )
	{
		Shader* pShader = m_vShaders[i];

		if( pShader->GetShaderFileName().compare( Filename ) == 0 &&
			pShader->GetFunctionName().compare( Function ) == 0 &&
			pShader->GetShaderModelName().compare( Model ) == 0 )
		{
			return i;
		}
	}

	// ----------------------------------------------------------------------

	HRESULT hr = S_OK;
	ID3DBlob* pCompiledShader = nullptr;

	// 编译shader
	pCompiledShader = ShaderFactory::GenerateShader( Type , Filename , Function , Model , pDefines , EnableLogging );
	if( pCompiledShader == nullptr )
	{
		return -1;
	}


	// -------------------------创建shader----------------------
	Shader* pShaderWrapper = nullptr;

	switch( Type )
	{
		case ST_VERTEX_SHADER:
		{
			ID3D11VertexShader* pShader = nullptr;

			hr = m_pDevice->CreateVertexShader( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , nullptr , &pShader );

			pShaderWrapper = new VertexShader( pShader );
			break;
		}

		case ST_HULL_SHADER:
		{
			ID3D11HullShader* pShader = nullptr;
			hr = m_pDevice->CreateHullShader( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , nullptr , &pShader );

			pShaderWrapper = new HullShader( pShader );
			break;
		}

		case ST_DOMAIN_SHADER:
		{
			ID3D11DomainShader* pShader = nullptr;
			hr = m_pDevice->CreateDomainShader( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , nullptr , &pShader );

			pShaderWrapper = new DomainShader( pShader );
			break;
		}

		case ST_GEOMETRY_SHADER:
		{
			ID3D11GeometryShader* pShader = nullptr;
			hr = m_pDevice->CreateGeometryShader( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , nullptr , &pShader );

			pShaderWrapper = new GeometryShader( pShader );
			break;
		}

		case ST_PIXEL_SHADER:
		{
			ID3D11PixelShader* pShader = nullptr;
			hr = m_pDevice->CreatePixelShader( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , nullptr , &pShader );

			pShaderWrapper = new PixelShader( pShader );
			break;
		}

		case ST_COMPUTE_SHADER:
		{
			ID3D11ComputeShader* pShader = nullptr;
			hr = m_pDevice->CreateComputeShader( pCompiledShader->GetBufferPointer() , pCompiledShader->GetBufferSize() , nullptr , &pShader );

			pShaderWrapper = new ComputeShader( pShader );
			break;
		}
	}


	if( FAILED( hr ) )
	{
		Log::Get().Error( L"Failed to Create Shader" );
		pCompiledShader->Release();
		delete pShaderWrapper;
		return -1;
	}

	// --------------------保存shader的信息----------------------------
	pShaderWrapper->SetShaderFileName( Filename );
	pShaderWrapper->SetShaderFunctionName( Function );
	pShaderWrapper->SetShaderModelName( Model );
	pShaderWrapper->SetCompiledShader( pCompiledShader );

	m_vShaders.push_back( pShaderWrapper );

	ShaderReflection* pReflection = ShaderReflectionGenerator::GenerateReflection( pCompiledShader , Filename.substr( 0 , Filename.size() - 5 ) );

	// init constant buffer
	pReflection->InitConstantBufferParameter( m_pParameterManager );

	pShaderWrapper->SetShaderReflection( pReflection );

	return ( ( int )m_vShaders.size() - 1 );
}

void Renderer::QueueTask( Task* pTask )
{
	m_vQueuedTasks.push_back( pTask );
}

void Renderer::ProcessTaskQueue()
{
	for( int i = ( int )m_vQueuedTasks.size() - 1; i >= 0; i-- )
	{
		m_vQueuedTasks[i]->ExecuteTask( m_pPipelineManager , m_pParameterManager );
	}

	m_vQueuedTasks.clear();
}