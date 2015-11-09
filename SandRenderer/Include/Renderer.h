#ifndef Renderer_h
#define Renderer_h

#include "PCH.h"
#include "ResourceProxy.h"

namespace Sand
{
	typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContextComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Texture2D> Texturte2DComPtr;

	typedef Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceViewComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetViewComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilViewComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> UnorderedAccessViewComPtr;

	typedef Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayoutComPtr;

	typedef Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerStateComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11BlendState> BlendStateComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilStateComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerStateComPtr;

	typedef Microsoft::WRL::ComPtr<ID3D11Buffer> BufferComPtr;

	// ------------资源配置----------------
	class SwapChainConfig;
	class Texture2DConfig;
	class BufferConfig;

	// -------------资源类----------------
	class Resource;		// 资源类的基类
	class Texture2D;	

	// ------------视图类-------------
	class ShaderResourceView;
	class RenderTargetView;
	class UnorderedAccessView;
	class DepthStencilView;

	class SwapChain;

	class ViewPort;

	class PipelineManager;

	class BlendStateConfig;
	class RasterizerStateConfig;
	class DepthStencilStateConfig;
	class SampleStateConfig;

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

		// ----------------------------------------------------------框架函数------------------------------------------------------
		//************************************
		// Method:    Initialize
		// FullName:  Sand::Renderer::Initialize
		// Access:    public 
		// Returns:   bool
		// Qualifier: 初始化函数，创建Device , DeviceContext
		// Parameter: D3D_DRIVER_TYPE DriveType
		// Parameter: D3D_FEATURE_LEVEL FeatureLevel
		//************************************
		bool Initialize( D3D_DRIVER_TYPE DriveType , D3D_FEATURE_LEVEL FeatureLevel );

		//************************************
		// Method:    Shutdown
		// FullName:  Sand::Renderer::Shutdown
		// Access:    public 
		// Returns:   void
		// Qualifier: 销毁资源
		//************************************
		void Shutdown();

		//************************************
		// Method:    Present
		// FullName:  Sand::Renderer::Present
		// Access:    public 
		// Returns:   void
		// Qualifier: 显示图像
		// Parameter: int SwapChainID
		// Parameter: UINT SyncInterval
		// Parameter: UINT PresentFlags
		//************************************
		void Present( int SwapChainID = -1 , UINT SyncInterval = 0 , UINT PresentFlags = 0 );

		//------------------------------------------------------------------------------------------------------------------------------------------------
		//************************************
		// Method:    GetAvailableFeatureLevel
		// FullName:  Sand::Renderer::GetAvailableFeatureLevel
		// Access:    public 
		// Returns:   D3D_FEATURE_LEVEL
		// Qualifier: 获取可用的特征级别
		// Parameter: D3D_DRIVER_TYPE DriveType
		//************************************
		D3D_FEATURE_LEVEL GetAvailableFeatureLevel( D3D_DRIVER_TYPE DriveType );


		//************************************
		// Method:    GetCurrentFeatureLevel
		// FullName:  Sand::Renderer::GetCurrentFeatureLevel
		// Access:    public 
		// Returns:   D3D_FEATURE_LEVEL
		// Qualifier: 获取当前的特征级别
		//************************************
		D3D_FEATURE_LEVEL GetCurrentFeatureLevel();

		//************************************
		// Method:    GetAvailableVideoMemory
		// FullName:  Sand::Renderer::GetAvailableVideoMemory
		// Access:    public 
		// Returns:   UINT64
		// Qualifier: 获取可用显存大小
		//************************************
		UINT64 GetAvailableVideoMemory();
		//-------------------------------------------------------------------------------------------------------------------------------------


		// --------------------------------------------------------Swap Chain------------------------------------------------------------------
		//************************************
		// Method:    CreateSwapChain
		// FullName:  Sand::Renderer::CreateSwapChain
		// Access:    public 
		// Returns:   int
		// Qualifier: 根据传入的交换链描述，创建交换链对象，将其保存在交换链仓库中，返回其索引
		// Parameter: SwapChainConfig * pConfig
		//************************************
		int CreateSwapChain( SwapChainConfig* pConfig );

		//************************************
		// Method:    GetSwapChainResource
		// FullName:  Sand::Renderer::GetSwapChainResource
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: 根据索引获取与交换链相关联的渲染目标
		// Parameter: int index
		//************************************
		ResourceProxyPtr GetSwapChainResource( int index );


		// ---------------------------------------------------------Resource---------------------------------------------------------------------
		
		//************************************
		// Method:    DeleteResource
		// FullName:  Sand::Renderer::DeleteResource
		// Access:    public 
		// Returns:   void
		// Qualifier: 删除索引为index的资源对象
		// Parameter: int index
		//************************************
		void DeleteResource( int index );


		//************************************
		// Method:    DeleteResource
		// FullName:  Sand::Renderer::DeleteResource
		// Access:    public 
		// Returns:   void
		// Qualifier: 从资源仓库中删除该资源
		// Parameter: ResourcePtr pResource
		//************************************
		void DeleteResource( ResourceProxyPtr pResource );

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
		// Method:    GetUnusedResourceIndex
		// FullName:  Sand::Renderer::GetUnusedResourceIndex
		// Access:    public 
		// Returns:   int
		// Qualifier: 查找元素为nullptr的位置
		//************************************
		int GetUnusedResourceIndex();

		//************************************
		// Method:    GetResource
		// FullName:  Sand::Renderer::GetResource
		// Access:    public 
		// Returns:   ID3D11Resource*
		// Qualifier: 根据索引获取资源对象
		// Parameter: int index
		//************************************
		Resource* GetResourceByIndex( int index );



		// ---------------------------------------------------------Resource View-----------------------------------------------------------

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


		//************************************
		// Method:    GetRenderTargetViewByIndex
		// FullName:  Sand::Renderer::GetRenderTargetViewByIndex
		// Access:    public 
		// Returns:   Sand::RenderTargetView
		// Qualifier: 根据索引获取对应Render Target View
		// Parameter: int id
		//************************************
		RenderTargetView GetRenderTargetViewByIndex( int id );

		//************************************
		// Method:    GetDepthStencilViewByIndex
		// FullName:  Sand::Renderer::GetDepthStencilViewByIndex
		// Access:    public 
		// Returns:   Sand::DepthStencilView
		// Qualifier: 根据索引获取对应的Depth Stencil View
		// Parameter: int id
		//************************************
		DepthStencilView GetDepthStencilViewByIndex( int id );

		//************************************
		// Method:    GetUnorderedAccessViewByIndex
		// FullName:  Sand::Renderer::GetUnorderedAccessViewByIndex
		// Access:    public 
		// Returns:   Sand::UnorderedAccessView
		// Qualifier: 根据索引获取对应的UnorderedAccessView
		// Parameter: int id
		//************************************
		UnorderedAccessView GetUnorderedAccessViewByIndex( int id );


		// -------------------------------------------------------各类资源创建方法---------------------------------------------------------------------
		
		//************************************
		// Method:    CreateTexture2D
		// FullName:  Sand::Renderer::CreateTexture2D
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: 创建Texture2D纹理对象，并为其创建相应的视图对象
		// Parameter: Texture2DConfig * pConfig
		// Parameter: D3D11_SUBRESOURCE_DATA * pData
		// Parameter: ShaderResourceViewConfig * pShaderResourceViewConfig
		// Parameter: RenderTargetViewConfig * pRenderTargetViewConfig
		// Parameter: UnorderedAccessViewConfig * pUnorderedAccessViewConfig
		// Parameter: DepthStencilViewConfig * pDepthStencilViewConfig
		//************************************
		ResourceProxyPtr CreateTexture2D( Texture2DConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData ,
										  ShaderResourceViewConfig* pShaderResourceViewConfig = NULL ,
										  RenderTargetViewConfig* pRenderTargetViewConfig = NULL ,
										  UnorderedAccessViewConfig* pUnorderedAccessViewConfig = NULL ,
										  DepthStencilViewConfig* pDepthStencilViewConfig = NULL );

		//************************************
		// Method:    CreateVertexBuffer
		// FullName:  Sand::Renderer::CreateVertexBuffer
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: 创建Vertex Buffer并返回ResourceProxyPtr对象
		// Parameter: BufferConfig * pConfig
		// Parameter: D3D11_SUBRESOURCE_DATA * pData
		//************************************
		ResourceProxyPtr CreateVertexBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData );


		//************************************
		// Method:    CreateIndexBuffer
		// FullName:  Sand::Renderer::CreateIndexBuffer
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: 创建Index Buffer并返回ResourceProxyPtr对象
		// Parameter: BufferConfig * pConfig
		// Parameter: D3D11_SUBRESOURCE_DATA * pData
		//************************************
		ResourceProxyPtr CreateIndexBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData );


		// -------------------------------------------------状态--------------------------------------------
		//************************************
		// Method:    GetRasterizerState
		// FullName:  Sand::Renderer::GetRasterizerState
		// Access:    public 
		// Returns:   Sand::RasterizerStateComPtr
		// Qualifier: 根据index获取相应的光栅化状态，index不合理时，返回默认光栅化状态
		// Parameter: int index
		//************************************
		RasterizerStateComPtr GetRasterizerState( int index );

		//************************************
		// Method:    GetBlendState
		// FullName:  Sand::Renderer::GetBlendState
		// Access:    public 
		// Returns:   Sand::BlendStateComPtr
		// Qualifier: 根据index获取相应的混合状态，index范围不合理时，返回默认混合状态
		// Parameter: int index
		//************************************
		BlendStateComPtr GetBlendState( int index );

		//************************************
		// Method:    GetDepthStencilState
		// FullName:  Sand::Renderer::GetDepthStencilState
		// Access:    public 
		// Returns:   Sand::DepthStencilStateComPtr
		// Qualifier: 根据index获取相应的深度模板状态，index范围不合理时，返回默认深度模板状态
		// Parameter: int index
		//************************************
		DepthStencilStateComPtr GetDepthStencilState( int index );

		//************************************
		// Method:    CreateBlendState
		// FullName:  Sand::Renderer::CreateBlendState
		// Access:    public 
		// Returns:   int
		// Qualifier: 创建混合状态，并返回索引
		// Parameter: int index
		//************************************
		int CreateBlendState( BlendStateConfig* pConfig );

		//************************************
		// Method:    CreateDepthStencilState
		// FullName:  Sand::Renderer::CreateDepthStencilState
		// Access:    public 
		// Returns:   int
		// Qualifier: 创建深度模板状态，并返回索引
		// Parameter: int index
		//************************************
		int CreateDepthStencilState( DepthStencilStateConfig* pConfig );

		//************************************
		// Method:    CreateRasterizerState
		// FullName:  Sand::Renderer::CreateRasterizerState
		// Access:    public 
		// Returns:   int
		// Qualifier: 创建光栅化状态对象，并返回索引
		// Parameter: int index
		//************************************
		int CreateRasterizerState( RasterizerStateConfig* pConfig );

		//************************************
		// Method:    CreateSampleState
		// FullName:  Sand::Renderer::CreateSampleState
		// Access:    public 
		// Returns:   int
		// Qualifier: 创建采样状态对象，并返回索引
		// Parameter: SampleStateConfig * pConfig
		//************************************
		int CreateSampleState( SampleStateConfig* pConfig );


		//************************************
		// Method:    GetViewPort
		// FullName:  Sand::Renderer::GetViewPort
		// Access:    public 
		// Returns:   Sand::ViewPort
		// Qualifier: 根据索引index获取相应的Viewport对象
		// Parameter: int index
		//************************************
		const ViewPort& GetViewPort( int index );

		//************************************
		// Method:    CreateViewPort
		// FullName:  Sand::Renderer::CreateViewPort
		// Access:    public 
		// Returns:   int
		// Qualifier: 将该viewport添加到视口容器中，返回其索引
		// Parameter: D3D11_VIEWPORT viewport
		//************************************
		int CreateViewPort( D3D11_VIEWPORT viewport );

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

		// 状态仓库
		std::vector<RasterizerStateComPtr> m_vRasterizerStates;
		std::vector<DepthStencilStateComPtr> m_vDepthStencilStates;
		std::vector<BlendStateComPtr> m_vBlendStates;
		std::vector<SamplerStateComPtr> m_vSamplerStates;

		std::vector<InputLayoutComPtr> m_vInputLayouts;
		std::vector<ViewPort> m_vViewPorts;

	public:
		PipelineManager* m_pPipelineManager;
	};
}

#endif