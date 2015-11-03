#include "PCH.h"
#include "Renderer.h"

#include "DXGIAdapter.h"
#include "DXGIOutput.h"

#include "SwapChainConfig.h"
#include "Texture2DConfig.h"

#include "Texture2D.h"

#include "ResourceProxy.h"

#include "ShaderResoruceView.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "UnorderedAccessView.h"

#include "SwapChain.h"

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
	// 创建Device和Device Context

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
	}

	UINT CreateDeviceFlags = 0;
#ifdef _DEBUG
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

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
	}

	m_FeatureLevel = m_pDevice->GetFeatureLevel();
}

void Renderer::Shutdown()
{

}

void Renderer::Present( HWND hwnd /* = 0  */ , int SwapChain /* = -1  */ , UINT SyncInterval /* = 0  */ , UINT PresentFlags /* = 0 */ )
{

}

D3D_FEATURE_LEVEL Renderer::GetAvailableFeatureLevel( D3D_DRIVER_TYPE DriveType )
{

}

D3D_FEATURE_LEVEL Renderer::GetCurrentFeatureLevel()
{

}

UINT64 Renderer::GetAvailableVideoMemory()
{

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
		return -1;
	}

	// 获取back buffer接口
	Texturte2DComPtr BackBuffer;
	hr = pSwapChain->GetBuffer( 0 , __uuidof( ID3D11Texture2D ) , reinterpret_cast< void** >( BackBuffer.GetAddressOf() ) );

	if( FAILED( hr ) )
	{
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

	return ( m_vSwapChain.size() - 1 );
}

int Renderer::CreateShaderResourceView( int ResourceID , D3D11_SHADER_RESOURCE_VIEW_DESC* Desc )
{

}

int Renderer::CreateRenderTargetView( int ResourceID , D3D11_RENDER_TARGET_VIEW_DESC* Desc )
{

}

int Renderer::CreateDepthStencilView( int ResourceID , D3D11_DEPTH_STENCIL_VIEW_DESC* Desc )
{

}

int Renderer::CreateUnorderedAccessView( int ResourceID , D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc )
{

}

int Renderer::StoreNewResource( Resource* pResource )
{

}