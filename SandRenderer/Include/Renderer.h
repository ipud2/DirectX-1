#ifndef Renderer_h
#define Renderer_h

#include "PCH.h"

namespace Sand
{
	typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContextComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Texture2D> Texturte2DComPtr;

	// ------------资源配置----------------
	class SwapChainConfig;
	class Texture2DConfig;

	// -------------资源类----------------
	class Resource;		// 资源类的基类
	class Texture2D;	

	// ------------视图类-------------
	class ShaderResourceView;
	class RenderTargetView;
	class UnorderedAccessView;
	class DepthStencilView;

	class ResourceProxy;

	class SwapChain;

	enum ResourceType
	{
		// ---------Buffer------------------
		RT_VERTEXBUFFER , 
		RT_INDEXBUFFER ,
		RT_CONSTANTBUFFER , 
		RT_STRUCTUREDBUFFER , 

		// ----------Texture----------------
		RT_TEXTURE1D ,
		RT_TEXTURE2D ,
		RT_TEXTURE3D
	};


	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		// 单一实例
		static Renderer* Get();

		// 框架函数
		bool Initialize( D3D_DRIVER_TYPE DriveType , D3D_FEATURE_LEVEL FeatureLevel );
		void Shutdown();
		void Present( HWND hwnd = 0 , int SwapChain = -1 , UINT SyncInterval = 0 , UINT PresentFlags = 0 );

		// 获取可用特性级别及当前特性级别
		D3D_FEATURE_LEVEL GetAvailableFeatureLevel( D3D_DRIVER_TYPE DriveType );
		D3D_FEATURE_LEVEL GetCurrentFeatureLevel();

		// 获取可用显存
		UINT64 GetAvailableVideoMemory();

		//************************************
		// Method:    CreateSwapChain
		// FullName:  Sand::Renderer::CreateSwapChain
		// Access:    public 
		// Returns:   int
		// Qualifier: 根据传入的交换链描述，创建交换链对象，将其保存在交换量仓库中，返回其索引
		// Parameter: SwapChainConfig * pConfig
		//************************************
		int CreateSwapChain( SwapChainConfig* pConfig );

		
		//************************************
		// Method:    StoreNewResource
		// FullName:  Sand::Renderer::StoreNewResource
		// Access:    public 
		// Returns:   int
		// Qualifier: 将资源对象保存到资源仓库中，返回其索引
		// Parameter: Resource * pResource
		//************************************
		int StoreNewResource( Resource* pResource );


		//************************************
		// Method:    CreateShaderResourceView
		// FullName:  Sand::Renderer::CreateShaderResourceView
		// Access:    public 
		// Returns:   int
		// Qualifier: 为编号为ResourceID的资源，创建视图描述为Desc的ShaderResourceView
		// Parameter: int ResourceID
		// Parameter: D3D11_SHADER_RESOURCE_VIEW_DESC Desc
		//************************************
		int CreateShaderResourceView( int ResourceID , D3D11_SHADER_RESOURCE_VIEW_DESC* Desc );


		//************************************
		// Method:    CreateRenderTargetView
		// FullName:  Sand::Renderer::CreateRenderTargetView
		// Access:    public 
		// Returns:   int
		// Qualifier: 为编号为ResourceID的资源，创建视图描述为Desc的RenderTargetView
		// Parameter: int ResourceID
		// Parameter: D3D11_RENDER_TARGET_VIEW_DESC Desc
		//************************************
		int CreateRenderTargetView( int ResourceID , D3D11_RENDER_TARGET_VIEW_DESC* Desc );


		//************************************
		// Method:    CreateUnorderedAccessView
		// FullName:  Sand::Renderer::CreateUnorderedAccessView
		// Access:    public 
		// Returns:   int
		// Qualifier: 为编号为ResourceID的资源，创建视图描述为Desc的UnorderedAccessView
		// Parameter: int ResourceID
		// Parameter: D3D11_UNORDERED_ACCESS_VIEW_DESC Desc
		//************************************
		int CreateUnorderedAccessView( int ResourceID , D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc );


		//************************************
		// Method:    CreateDepthStencilView
		// FullName:  Sand::Renderer::CreateDepthStencilView
		// Access:    public 
		// Returns:   int
		// Qualifier: 为编号为ResourceID的资源，创建视图描述为Desc的DepthStencilView
		// Parameter: int ResourceID
		// Parameter: D3D11_DEPTH_STENCIL_VIEW_DESC Desc
		//************************************
		int CreateDepthStencilView( int ResourceID , D3D11_DEPTH_STENCIL_VIEW_DESC* Desc );

	protected:
		Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
		Microsoft::WRL::ComPtr<ID3D11Debug> m_pDebugger;
		
		D3D_DRIVER_TYPE m_DriveType;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		// 单一实例对象
		static Renderer* m_spRenderer;

		// 交换链仓库，交换链对象都保存在这里
		std::vector<SwapChain*> m_vSwapChain;

		// 资源仓库，资源对象都保存在这里
		std::vector<Resource*> m_vResource;

		// 视图对象仓库
		std::vector<ShaderResourceView> m_vShaderResourceView;
		std::vector<RenderTargetView> m_vRenderTargetView;
		std::vector<UnorderedAccessView> m_vUnorderedAccessView;
		std::vector<DepthStencilView> m_vDepthStencilView;

	};
}

#endif