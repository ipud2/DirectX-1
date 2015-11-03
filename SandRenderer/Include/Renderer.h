#ifndef Renderer_h
#define Renderer_h

#include "PCH.h"

namespace Sand
{
	typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContextComPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Texture2D> Texturte2DComPtr;

	typedef Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceViewPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetViewPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilViewPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> UnorderedAccessViewPtr;

	// ------------��Դ����----------------
	class SwapChainConfig;
	class Texture2DConfig;

	// -------------��Դ��----------------
	class Resource;		// ��Դ��Ļ���
	class Texture2D;	

	// ------------��ͼ��-------------
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

		// ��һʵ��
		static Renderer* Get();

		// ��ܺ���
		bool Initialize( D3D_DRIVER_TYPE DriveType , D3D_FEATURE_LEVEL FeatureLevel );
		void Shutdown();
		void Present( int SwapChainID = -1 , UINT SyncInterval = 0 , UINT PresentFlags = 0 );

		// ��ȡ�������Լ��𼰵�ǰ���Լ���
		D3D_FEATURE_LEVEL GetAvailableFeatureLevel( D3D_DRIVER_TYPE DriveType );
		D3D_FEATURE_LEVEL GetCurrentFeatureLevel();

		// ��ȡ�����Դ�
		UINT64 GetAvailableVideoMemory();

		//************************************
		// Method:    CreateSwapChain
		// FullName:  Sand::Renderer::CreateSwapChain
		// Access:    public 
		// Returns:   int
		// Qualifier: ���ݴ���Ľ������������������������󣬽��䱣���ڽ������ֿ��У�����������
		// Parameter: SwapChainConfig * pConfig
		//************************************
		int CreateSwapChain( SwapChainConfig* pConfig );

		

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

		// ��ͼ����ֿ�
		std::vector<ShaderResourceView> m_vShaderResourceView;
		std::vector<RenderTargetView> m_vRenderTargetView;
		std::vector<UnorderedAccessView> m_vUnorderedAccessView;
		std::vector<DepthStencilView> m_vDepthStencilView;

	};
}

#endif