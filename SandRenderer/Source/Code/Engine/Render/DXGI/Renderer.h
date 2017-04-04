#ifndef Renderer_h
#define Renderer_h

#include <Engine/PCH.h>
#include "Engine/Resource/ResourceProxy.h"
#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Shader.h"

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

	// ------------��Դ����----------------
	class SwapChainConfig;
	class Texture2DConfig;
	class BufferConfig;

	// -------------��Դ��----------------
	class Resource;		// ��Դ��Ļ���
	class Texture2D;	
	class ConstantBuffer;
	class VertexBuffer;
	class IndexBuffer;

	// ------------��ͼ��-------------
	class ShaderResourceView;
	class RenderTargetView;
	class UnorderedAccessView;
	class DepthStencilView;

	class SwapChain;

	class ViewPort;

	class PipelineManager;
	class IParameterManager;

	class BlendStateConfig;
	class RasterizerStateConfig;
	class DepthStencilStateConfig;
	class SamplerStateConfig;

	class Shader;

	class Task;

	enum ResourceType
	{
		// ---------Buffer------------------
		RT_VERTEXBUFFER , 
		RT_INDEXBUFFER ,
		RT_CONSTANT_BUFFER , 
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

		// ��һʵ��
		static Renderer* Get();

		// ----------------------------------------------------------��ܺ���------------------------------------------------------
		//************************************
		// Method:    Initialize
		// FullName:  Sand::Renderer::Initialize
		// Access:    public 
		// Returns:   bool
		// Qualifier: ��ʼ������������Device , DeviceContext
		// Parameter: D3D_DRIVER_TYPE DriveType
		// Parameter: D3D_FEATURE_LEVEL FeatureLevel
		//************************************
		bool Initialize( D3D_DRIVER_TYPE DriveType , D3D_FEATURE_LEVEL FeatureLevel );

		//************************************
		// Method:    Shutdown
		// FullName:  Sand::Renderer::Shutdown
		// Access:    public 
		// Returns:   void
		// Qualifier: ������Դ
		//************************************
		void Shutdown();

		//************************************
		// Method:    Present
		// FullName:  Sand::Renderer::Present
		// Access:    public 
		// Returns:   void
		// Qualifier: ��ʾͼ��
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
		// Qualifier: ��ȡ���õ���������
		// Parameter: D3D_DRIVER_TYPE DriveType
		//************************************
		D3D_FEATURE_LEVEL GetAvailableFeatureLevel( D3D_DRIVER_TYPE DriveType );


		//************************************
		// Method:    GetCurrentFeatureLevel
		// FullName:  Sand::Renderer::GetCurrentFeatureLevel
		// Access:    public 
		// Returns:   D3D_FEATURE_LEVEL
		// Qualifier: ��ȡ��ǰ����������
		//************************************
		D3D_FEATURE_LEVEL GetCurrentFeatureLevel();

		//************************************
		// Method:    GetAvailableVideoMemory
		// FullName:  Sand::Renderer::GetAvailableVideoMemory
		// Access:    public 
		// Returns:   UINT64
		// Qualifier: ��ȡ�����Դ��С
		//************************************
		UINT64 GetAvailableVideoMemory();
		//-------------------------------------------------------------------------------------------------------------------------------------


		// --------------------------------------------------------Swap Chain------------------------------------------------------------------
		//************************************
		// Method:    CreateSwapChain
		// FullName:  Sand::Renderer::CreateSwapChain
		// Access:    public 
		// Returns:   int
		// Qualifier: ���ݴ���Ľ������������������������󣬽��䱣���ڽ������ֿ��У�����������
		// Parameter: SwapChainConfig * pConfig
		//************************************
		int CreateSwapChain( SwapChainConfig* pConfig );

		//************************************
		// Method:    GetSwapChainResource
		// FullName:  Sand::Renderer::GetSwapChainResource
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: ����������ȡ�뽻�������������ȾĿ��
		// Parameter: int index
		//************************************
		ResourceProxyPtr GetSwapChainResource( int index );


		void ResizeSwapChain( int index , int width , int height );

		// ---------------------------------------------------------Resource---------------------------------------------------------------------
		
		//************************************
		// Method:    DeleteResource
		// FullName:  Sand::Renderer::DeleteResource
		// Access:    public 
		// Returns:   void
		// Qualifier: ɾ������Ϊindex����Դ����
		// Parameter: int index
		//************************************
		void DeleteResource( int index );


		//************************************
		// Method:    DeleteResource
		// FullName:  Sand::Renderer::DeleteResource
		// Access:    public 
		// Returns:   void
		// Qualifier: ����Դ�ֿ���ɾ������Դ
		// Parameter: ResourcePtr pResource
		//************************************
		void DeleteResource( ResourceProxyPtr pResource );

		//************************************
		// Method:    StoreNewResource
		// FullName:  Sand::Renderer::StoreNewResource
		// Access:    public 
		// Returns:   int
		// Qualifier: ����Դ���󱣴浽��Դ�ֿ��У�����������
		// Parameter: Resource * pResource
		//************************************
		int StoreNewResource( Resource* pResource );

		//************************************
		// Method:    GetUnusedResourceIndex
		// FullName:  Sand::Renderer::GetUnusedResourceIndex
		// Access:    public 
		// Returns:   int
		// Qualifier: ����Ԫ��Ϊnullptr��λ��
		//************************************
		int GetUnusedResourceIndex();

		//************************************
		// Method:    GetResource
		// FullName:  Sand::Renderer::GetResource
		// Access:    public 
		// Returns:   ID3D11Resource*
		// Qualifier: ����������ȡ��Դ����
		// Parameter: int index
		//************************************
		Resource* GetResourceByIndex( int index );



		// ---------------------------------------------------------Resource View-----------------------------------------------------------

		//************************************
		// Method:    CreateShaderResourceView
		// FullName:  Sand::Renderer::CreateShaderResourceView
		// Access:    public 
		// Returns:   int
		// Qualifier: Ϊ���ΪResourceID����Դ��������ͼ����ΪDesc��ShaderResourceView
		// Parameter: int ResourceID
		// Parameter: D3D11_SHADER_RESOURCE_VIEW_DESC Desc
		//************************************
		int CreateShaderResourceView( int ResourceID , D3D11_SHADER_RESOURCE_VIEW_DESC* Desc );


		//************************************
		// Method:    CreateRenderTargetView
		// FullName:  Sand::Renderer::CreateRenderTargetView
		// Access:    public 
		// Returns:   int
		// Qualifier: Ϊ���ΪResourceID����Դ��������ͼ����ΪDesc��RenderTargetView
		// Parameter: int ResourceID
		// Parameter: D3D11_RENDER_TARGET_VIEW_DESC Desc
		//************************************
		int CreateRenderTargetView( int ResourceID , D3D11_RENDER_TARGET_VIEW_DESC* Desc );


		//************************************
		// Method:    CreateUnorderedAccessView
		// FullName:  Sand::Renderer::CreateUnorderedAccessView
		// Access:    public 
		// Returns:   int
		// Qualifier: Ϊ���ΪResourceID����Դ��������ͼ����ΪDesc��UnorderedAccessView
		// Parameter: int ResourceID
		// Parameter: D3D11_UNORDERED_ACCESS_VIEW_DESC Desc
		//************************************
		int CreateUnorderedAccessView( int ResourceID , D3D11_UNORDERED_ACCESS_VIEW_DESC* Desc );


		//************************************
		// Method:    CreateDepthStencilView
		// FullName:  Sand::Renderer::CreateDepthStencilView
		// Access:    public 
		// Returns:   int
		// Qualifier: Ϊ���ΪResourceID����Դ��������ͼ����ΪDesc��DepthStencilView
		// Parameter: int ResourceID
		// Parameter: D3D11_DEPTH_STENCIL_VIEW_DESC Desc
		//************************************
		int CreateDepthStencilView( int ResourceID , D3D11_DEPTH_STENCIL_VIEW_DESC* Desc );


		//************************************
		// Method:    GetRenderTargetViewByIndex
		// FullName:  Sand::Renderer::GetRenderTargetViewByIndex
		// Access:    public 
		// Returns:   Sand::RenderTargetView
		// Qualifier: ����������ȡ��ӦRender Target View
		// Parameter: int id
		//************************************
		RenderTargetView GetRenderTargetViewByIndex( int id );

		//************************************
		// Method:    GetDepthStencilViewByIndex
		// FullName:  Sand::Renderer::GetDepthStencilViewByIndex
		// Access:    public 
		// Returns:   Sand::DepthStencilView
		// Qualifier: ����������ȡ��Ӧ��Depth Stencil View
		// Parameter: int id
		//************************************
		DepthStencilView GetDepthStencilViewByIndex( int id );

		//************************************
		// Method:    GetUnorderedAccessViewByIndex
		// FullName:  Sand::Renderer::GetUnorderedAccessViewByIndex
		// Access:    public 
		// Returns:   Sand::UnorderedAccessView
		// Qualifier: ����������ȡ��Ӧ��UnorderedAccessView
		// Parameter: int id
		//************************************
		UnorderedAccessView GetUnorderedAccessViewByIndex( int id );

		//************************************
		// Method:    GetShaderResourceViewByIndex
		// FullName:  Sand::Renderer::GetShaderResourceViewByIndex
		// Access:    public 
		// Returns:   Sand::ShaderResourceView
		// Qualifier: ����������ȡ��Ӧ��ShaderResourceView����
		// Parameter: int id
		//************************************
		ShaderResourceView GetShaderResourceViewByIndex( int id );

		// -------------------------------------------------------������Դ��������---------------------------------------------------------------------
		
		ResourceProxyPtr LoadTexture( std::wstring filename , bool sRGB = false );
		ResourceProxyPtr LoadTexture( void* pData , SIZE_T SizeInBytes );

		//************************************
		// Method:    CreateTexture2D
		// FullName:  Sand::Renderer::CreateTexture2D
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: ����Texture2D������󣬲�Ϊ�䴴����Ӧ����ͼ����
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
		// Qualifier: ����Vertex Buffer������ResourceProxyPtr����
		// Parameter: BufferConfig * pConfig
		// Parameter: D3D11_SUBRESOURCE_DATA * pData
		//************************************
		ResourceProxyPtr CreateVertexBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData );


		//************************************
		// Method:    CreateIndexBuffer
		// FullName:  Sand::Renderer::CreateIndexBuffer
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: ����Index Buffer������ResourceProxyPtr����
		// Parameter: BufferConfig * pConfig
		// Parameter: D3D11_SUBRESOURCE_DATA * pData
		//************************************
		ResourceProxyPtr CreateIndexBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData );


		//************************************
		// Method:    CreateConstantBuffer
		// FullName:  Sand::Renderer::CreateConstantBuffer
		// Access:    public 
		// Returns:   Sand::ResourceProxyPtr
		// Qualifier: ���������������
		// Parameter: BufferConfig * pConfig
		// Parameter: D3D11_SUBRESOURCE_DATA * pData
		//************************************
		ResourceProxyPtr CreateConstantBuffer( BufferConfig* pConfig , D3D11_SUBRESOURCE_DATA* pData );


		//************************************
		// Method:    GetConstantBufferByIndex
		// FullName:  Sand::Renderer::GetConstantBufferByIndex
		// Access:    public 
		// Returns:   ConstantBuffer*
		// Qualifier: ����������ȡConstant Buffer��Դ
		// Parameter: int index
		//************************************
		ConstantBuffer* GetConstantBufferByIndex( int index );

		//************************************
		// Method:    GetVertexBufferByIndex
		// FullName:  Sand::Renderer::GetVertexBufferByIndex
		// Access:    public 
		// Returns:   VertexBuffer*
		// Qualifier: ��ȡVertexBuffer
		// Parameter: int ID
		//************************************
		VertexBuffer* GetVertexBufferByIndex( int ID );

		//************************************
		// Method:    GetIndexBufferByIndex
		// FullName:  Sand::Renderer::GetIndexBufferByIndex
		// Access:    public 
		// Returns:   IndexBuffer*
		// Qualifier: ��ȡIndexBuffer
		// Parameter: int ID
		//************************************
		IndexBuffer* GetIndexBufferByIndex( int ID );


		// -------------------------------------------------״̬--------------------------------------------
		//************************************
		// Method:    GetRasterizerState
		// FullName:  Sand::Renderer::GetRasterizerState
		// Access:    public 
		// Returns:   Sand::RasterizerStateComPtr
		// Qualifier: ����index��ȡ��Ӧ�Ĺ�դ��״̬��index������ʱ������Ĭ�Ϲ�դ��״̬
		// Parameter: int index
		//************************************
		RasterizerStateComPtr GetRasterizerState( int index );

		//************************************
		// Method:    GetBlendState
		// FullName:  Sand::Renderer::GetBlendState
		// Access:    public 
		// Returns:   Sand::BlendStateComPtr
		// Qualifier: ����index��ȡ��Ӧ�Ļ��״̬��index��Χ������ʱ������Ĭ�ϻ��״̬
		// Parameter: int index
		//************************************
		BlendStateComPtr GetBlendState( int index );

		//************************************
		// Method:    GetDepthStencilState
		// FullName:  Sand::Renderer::GetDepthStencilState
		// Access:    public 
		// Returns:   Sand::DepthStencilStateComPtr
		// Qualifier: ����index��ȡ��Ӧ�����ģ��״̬��index��Χ������ʱ������Ĭ�����ģ��״̬
		// Parameter: int index
		//************************************
		DepthStencilStateComPtr GetDepthStencilState( int index );

		//************************************
		// Method:    GetSamplerState
		// FullName:  Sand::Renderer::GetSamplerState
		// Access:    public 
		// Returns:   Sand::SamplerStateComPtr
		// Qualifier:
		// Parameter: int index
		//************************************
		SamplerStateComPtr GetSamplerState( int index );

		//************************************
		// Method:    CreateBlendState
		// FullName:  Sand::Renderer::CreateBlendState
		// Access:    public 
		// Returns:   int
		// Qualifier: �������״̬������������
		// Parameter: int index
		//************************************
		int CreateBlendState( BlendStateConfig* pConfig );

		//************************************
		// Method:    CreateDepthStencilState
		// FullName:  Sand::Renderer::CreateDepthStencilState
		// Access:    public 
		// Returns:   int
		// Qualifier: �������ģ��״̬������������
		// Parameter: int index
		//************************************
		int CreateDepthStencilState( DepthStencilStateConfig* pConfig );

		//************************************
		// Method:    CreateRasterizerState
		// FullName:  Sand::Renderer::CreateRasterizerState
		// Access:    public 
		// Returns:   int
		// Qualifier: ������դ��״̬���󣬲���������
		// Parameter: int index
		//************************************
		int CreateRasterizerState( RasterizerStateConfig* pConfig );

		//************************************
		// Method:    CreateSampleState
		// FullName:  Sand::Renderer::CreateSampleState
		// Access:    public 
		// Returns:   int
		// Qualifier: ��������״̬���󣬲���������
		// Parameter: SampleStateConfig * pConfig
		//************************************
		int CreateSamplerState( SamplerStateConfig* pConfig );


		//************************************
		// Method:    GetViewPort
		// FullName:  Sand::Renderer::GetViewPort
		// Access:    public 
		// Returns:   Sand::ViewPort
		// Qualifier: ��������index��ȡ��Ӧ��Viewport����
		// Parameter: int index
		//************************************
		const ViewPort& GetViewPort( int index );

		//************************************
		// Method:    CreateViewPort
		// FullName:  Sand::Renderer::CreateViewPort
		// Access:    public 
		// Returns:   int
		// Qualifier: ����viewport��ӵ��ӿ������У�����������
		// Parameter: D3D11_VIEWPORT viewport
		//************************************
		int CreateViewPort( D3D11_VIEWPORT viewport );

		//************************************
		// Method:    ResizeViewport
		// FullName:  Sand::Renderer::ResizeViewport
		// Access:    public 
		// Returns:   void
		// Qualifier: �����ӿڴ�С
		// Parameter: int ID
		// Parameter: UINT width
		// Parameter: UINT height
		//************************************
		void ResizeViewport( int ID , UINT width , UINT height );

		//************************************
		// Method:    CreateInputLayout
		// FullName:  Sand::Renderer::CreateInputLayout
		// Access:    public 
		// Returns:   int
		// Qualifier: ����InputLayout����
		// Parameter: std::vector<D3D11_INPUT_ELEMENT_DESC> & m_InputElementDesc
		// Parameter: int ShaderID
		//************************************
		int CreateInputLayout( std::vector<D3D11_INPUT_ELEMENT_DESC>& InputElementDesc , int ShaderID );
		
		//************************************
		// Method:    GetInputLayout
		// FullName:  Sand::Renderer::GetInputLayout
		// Access:    public 
		// Returns:   Sand::InputLayoutComPtr
		// Qualifier: ��ȡInputLayout����
		// Parameter: int index
		//************************************
		InputLayoutComPtr GetInputLayout( int index );

		// ----------------------------------------Shader-----------------------------------------------
		Shader* GetShader( int index );

		int LoadShader( ShaderType Type , std::wstring& Filename , std::wstring& Function , std::wstring& Model , bool EnableLogging = true );
		int LoadShader( ShaderType Type , std::wstring& Filename , std::wstring& Function , std::wstring& Model , const D3D_SHADER_MACRO* pDefines , bool EnableLogging = true );

		void QueueTask( Task* pTask );
		void ProcessTaskQueue();

		ID3D11Device* GetDevice();

	protected:
		Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
		Microsoft::WRL::ComPtr<ID3D11Debug> m_pDebugger;
		
		D3D_DRIVER_TYPE m_DriveType;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		// ��һʵ������
		static Renderer* m_spRenderer;

		// �������ֿ⣬���������󶼱���������
		std::vector<SwapChain*> m_vSwapChain;

		// ��Դ�ֿ⣬��Դ���󶼱���������
		std::vector<Resource*> m_vResource;
		// ���ⲿ���ص�������󣬼�ͨ���ļ������صģ������Ϳ��Ա����μ���ͬһ�������ļ�
		std::map<std::wstring , ResourceProxyPtr> m_vExternalTexture;

		// ��ͼ����ֿ�
		std::vector<ShaderResourceView> m_vShaderResourceViews;
		std::vector<RenderTargetView> m_vRenderTargetViews;
		std::vector<UnorderedAccessView> m_vUnorderedAccessViews;
		std::vector<DepthStencilView> m_vDepthStencilViews;

		// ״̬�ֿ�
		std::vector<RasterizerStateComPtr> m_vRasterizerStates;
		std::vector<DepthStencilStateComPtr> m_vDepthStencilStates;
		std::vector<BlendStateComPtr> m_vBlendStates;
		std::vector<SamplerStateComPtr> m_vSamplerStates;

		std::vector<InputLayoutComPtr> m_vInputLayouts;
		std::vector<ViewPort> m_vViewPorts;

		// Shader�ֿ�
		std::vector<Shader*> m_vShaders;

		std::vector<Task*> m_vQueuedTasks;

	public:
		PipelineManager* GetPipelineManagerRef();
		IParameterManager* GetParameterManagerRef();

	protected:
		PipelineManager* m_pPipelineManager;
		IParameterManager* m_pParameterManager;
	};
};
#endif