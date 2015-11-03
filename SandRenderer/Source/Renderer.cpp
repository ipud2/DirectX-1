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

#include "Log.h"

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
	// ����Device

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

		// ���adapter����(ͨ�����Կ�)
		Log::Get().Write( desc.Description );
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

	// ��ȡdebug�ӿ�
	hr = m_pDevice.CopyTo( m_pDebugger.GetAddressOf() );

	if( FAILED( hr ) )
	{
		// ���������Ϣ
		Log::Get().Write( L"�޷���Device��ȡID3D11Debug�ӿڶ���" );
	}

	m_FeatureLevel = m_pDevice->GetFeatureLevel();
}

void Renderer::Shutdown()
{

}

void Renderer::Present( int SwapChainID /* = -1  */ , UINT SyncInterval /* = 0  */ , UINT PresentFlags /* = 0 */ )
{
	unsigned int index = static_cast< unsigned int >( SwapChainID );

	if( index < m_vSwapChain.size() )
	{
		// ��ȡ��Ӧ�Ľ�������ʾͼ��
		SwapChain* pSwapChain = m_vSwapChain[SwapChainID];

		HRESULT hr = pSwapChain->m_SwapChain->Present( SyncInterval , PresentFlags );
	}
	else
	{
		// ���������Ϣ
	}
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


	// ��������������
	ComPtr<IDXGISwapChain> pSwapChain;
	hr = pFactory->CreateSwapChain( m_pDevice.Get() , &pConfig->m_State , pSwapChain.GetAddressOf() );


	if( FAILED( hr ) )
	{
		Log::Get().Write( L"����������ʧ��" );

		return -1;
	}

	// ��ȡback buffer�ӿ�
	Texturte2DComPtr BackBuffer;
	hr = pSwapChain->GetBuffer( 0 , __uuidof( ID3D11Texture2D ) , reinterpret_cast< void** >( BackBuffer.GetAddressOf() ) );

	if( FAILED( hr ) )
	{
		Log::Get().Write( L"������������Ļ����ȡʧ��" );

		return -1;
	}
	
	// ������Դ����
	int ResoureID = StoreNewResource( new Texture2D( BackBuffer ) );

	
	// ��ȡback buffer���������Ա�Ϊ�䴴����Ӧ��view
	// swap chain��back buffer��bindflagsΪD3D11_BIND_RENDER_TARGET
	Texture2DConfig TextureConfig;
	BackBuffer->GetDesc( &TextureConfig.m_State );

	// Ϊ����Դ����BindFlags������Ӧ����ͼ
	ResourceProxyPtr proxy( new ResourceProxy( ResoureID , &TextureConfig , this ) );

	m_vSwapChain.push_back( new SwapChain( pSwapChain , proxy ) );

	return ( m_vSwapChain.size() - 1 );
}

int Renderer::CreateShaderResourceView( int ResourceID , D3D11_SHADER_RESOURCE_VIEW_DESC* Desc )
{
	// ��ȡ��Դ���� �ж���Դ�����Ƿ�Ϊnullptr
	// �ж���Դ�����Ӧ��D3D��Դ�Ƿ����
	// �����ڣ���Ϊ�䴴����Ӧ����ͼ
	// ����ͼ�����ɹ�������ͼ��������ͼ�ֿ�
	// ����������

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			ShaderResourceViewPtr pShaderResourceView;
			HRESULT hr = m_pDevice->CreateShaderResourceView( pRawResource , Desc , pShaderResourceView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vShaderResourceView.push_back( pShaderResourceView );
				return ( m_vShaderResourceView.size() - 1 );
			}
		}
	}

	// ����ʧ�ܷ���-1
	return -1;
}

int Renderer::CreateRenderTargetView( int ResourceID , D3D11_RENDER_TARGET_VIEW_DESC* Desc )
{
	// ��ȡ��Դ���� �ж���Դ�����Ƿ�Ϊnullptr
	// �ж���Դ�����Ӧ��D3D��Դ�Ƿ����
	// �����ڣ���Ϊ�䴴����Ӧ����ͼ
	// ����ͼ�����ɹ�������ͼ��������ͼ�ֿ�
	// ����������

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			RenderTargetViewPtr pRenderTargetView;
			HRESULT hr = m_pDevice->CreateRenderTargetView( pRawResource , Desc , pRenderTargetView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vRenderTargetView.push_back( pRenderTargetView );
				return ( m_vRenderTargetView.size() - 1 );
			}
		}
	}

	// ����ʧ�ܷ���-1
	return -1;
}

int Renderer::CreateDepthStencilView( int ResourceID , D3D11_DEPTH_STENCIL_VIEW_DESC* Desc )
{
	// ��ȡ��Դ���� �ж���Դ�����Ƿ�Ϊnullptr
	// �ж���Դ�����Ӧ��D3D��Դ�Ƿ����
	// �����ڣ���Ϊ�䴴����Ӧ����ͼ
	// ����ͼ�����ɹ�������ͼ��������ͼ�ֿ�
	// ����������

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			DepthStencilViewPtr pDepthStencilView;
			HRESULT hr = m_pDevice->CreateDepthStencilView( pRawResource , Desc , pDepthStencilView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vDepthStencilView.push_back( pDepthStencilView );
				return ( m_vDepthStencilView.size() - 1 );
			}
		}
	}

	// ����ʧ�ܷ���-1
	return -1;
}

int Renderer::CreateUnorderedAccessView( int ResourceID , D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc )
{
	// ��ȡ��Դ���� �ж���Դ�����Ƿ�Ϊnullptr
	// �ж���Դ�����Ӧ��D3D��Դ�Ƿ����
	// �����ڣ���Ϊ�䴴����Ӧ����ͼ
	// ����ͼ�����ɹ�������ͼ��������ͼ�ֿ�
	// ����������

	Resource* pResource = GetResourceByIndex( ResourceID );

	if( pResource )
	{
		ID3D11Resource* pRawResource = pResource->GetResource();

		if( pRawResource )
		{
			UnorderedAccessViewPtr pUnorderedAccessView;
			HRESULT hr = m_pDevice->CreateUnorderedAccessView( pRawResource , Desc , pUnorderedAccessView.GetAddressOf() );

			if( SUCCEEDED( hr ) )
			{
				m_vUnorderedAccessView.push_back( pUnorderedAccessView );
				return ( m_vUnorderedAccessView.size() - 1 );
			}
		}
	}

	// ����ʧ�ܷ���-1
	return -1;
}

int Renderer::StoreNewResource( Resource* pResource )
{
	// ����Դ�б��в����Ƿ���Ԫ��Ϊnullptr��λ�ã������ڣ��򽫸���Դ������λ��
	// ���ޣ��򽫸���Դ�������

	int index = GetUnusedResourceIndex();

	if( index == -1 )
	{
		// ˵����Դ�����в���Ԫ��Ϊnullptr����˽�����Դ�����б����
		m_vResource.push_back( pResource );
		return ( m_vResource.size() - 1 );
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
	int id = ( index & 0xffff );

	if( id < m_vResource.size() )
	{
		// ����ID��ȡ��Ӧ��Resource
		pResource = m_vResource[id];

		// ��֤inner ID
		if( pResource->GetInnerID() != inner )
		{
			// ���������Ϣ
			Log::Get().Write( L"��Դ��InnerID��������InnerID��һ��" );
		}
	}

	return pResource;
}

void Sand::Renderer::DeleteResource( int index )
{
	// ��ȡ����Դ����
	Resource* pResource = GetResourceByIndex( index );

	if( pResource != nullptr )
	{
		delete pResource;

		m_vResource[index & 0xffff] = nullptr;
	}
}

void Renderer::DeleteResource( ResourceProxyPtr pResource )
{
	DeleteResource( pResource->m_ResourceID );
}

int Renderer::GetUnusedResourceIndex()
{
	int index = -1;

	for( int i = 0; i < m_vResource.size() - 1; i++ )
	{
		if( m_vResource[i] == nullptr )
		{
			index = i;
			break;
		}
	}

	return -1;
}