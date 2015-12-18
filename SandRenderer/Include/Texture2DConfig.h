#ifndef Texture2DConfig_h
#define Texture2DConfig_h

#include "PCH.h"

namespace Sand
{
	/*
		UINT Width;
		UINT Height;
		UINT MipLevels;
		UINT ArraySize;
		DXGI_FORMAT Format;
		DXGI_SAMPLE_DESC SampleDesc;
		D3D11_USAGE Usage;
		UINT BindFlags;
		UINT CPUAccessFlags;
		UINT MiscFlags;
	*/
	class Texture2DConfig
	{
	public:
		Texture2DConfig();
		virtual ~Texture2DConfig();

		//************************************
		// Method:    SetDefaults
		// FullName:  Sand::Texture2DConfig::SetDefaults
		// Access:    public 
		// Returns:   void
		// Qualifier: 格式为R32G32B32A32，默认绑定到shader资源视图
		//************************************
		void SetDefaults();

		//************************************
		// Method:    SetDepthBuffer
		// FullName:  Sand::Texture2DConfig::SetDepthBuffer
		// Access:    public 
		// Returns:   void
		// Qualifier: 用于保存深度值，格式R32，可绑定到深度缓存视图
		// Parameter: UINT width
		// Parameter: UINT height
		//************************************
		void SetDepthBuffer( UINT width , UINT height );


		//************************************
		// Method:    SetColorBuffer
		// FullName:  Sand::Texture2DConfig::SetColorBuffer
		// Access:    public 
		// Returns:   void
		// Qualifier: 格式为R16G16B16A16，可绑定到shader资源视图
		// Parameter: UINT width
		// Parameter: UINT height
		//************************************
		void SetColorBuffer( UINT width , UINT height );

		void SetWidth( UINT state );
		void SetHeight( UINT state );
		void SetMipLevels( UINT state );
		void SetArraySize( UINT state );
		void SetFormat( DXGI_FORMAT state );
		void SetUsage( D3D11_USAGE state );
		void SetBindFlags( UINT state );
		void SetCPUAccessFlags( UINT state );
		void SetMiscFlags( UINT state );
		void SetSampleDesc( DXGI_SAMPLE_DESC state );

		UINT GetWidth();
		UINT GetHeight();
		UINT GetMipLevels();
		UINT GetArraySize();
		DXGI_FORMAT GetFormat();
		D3D11_USAGE GetUsage();
		UINT GetBindFlags();
		UINT GetCPUAccessFlags();
		UINT GetMiscFlags();
		DXGI_SAMPLE_DESC GetSampleDesc();

		D3D11_TEXTURE2D_DESC GetTextureDesc();

	protected:
		D3D11_TEXTURE2D_DESC m_State;

		friend class Renderer;
	};
}

#endif