#ifndef ShaderResourceViewConfig_h
#define ShaderResourceViewConfig_h

#include "PCH.h"

namespace Sand
{
	/*
		struct D3D11_SHADER_RESOURCE_VIEW_DESC
		{
			DXGI_FORMAT Format;
			D3D11_SRV_DIMENSION ViewDimension;
			
			union
			{
				D3D11_BUFFER_SRV Buffer;
				D3D11_TEX1D_SRV Texture1D;
				D3D11_TEX1D_ARRAY_SRV Texture1DArray;
				D3D11_TEX2D_SRV Texture2D;
				D3D11_TEX2D_ARRAY_SRV Texture2DArray;
				D3D11_TEX2DMS_SRV Texture2DMS;
				D3D11_TEX2DMS_ARRAY_SRV Texture2DMSArray;
				D3D11_TEX3D_SRV Texture3D;
				D3D11_TEXCUBE_SRV TextureCube;
				D3D11_TEXCUBE_ARRAY_SRV TextureCubeArray;
				D3D11_BUFFEREX_SRV BufferEx;
			};
		}
	*/
	class ShaderResourceViewConfig
	{
	public:
		ShaderResourceViewConfig();
		virtual ~ShaderResourceViewConfig();

		//************************************
		// Method:    SetDefaults
		// FullName:  Sand::ShaderResourceViewConfig::SetDefaults
		// Access:    public 
		// Returns:   void
		// Qualifier: 创建默认的ShaderResourceView描述
		//************************************
		void SetDefaults();

		void SetFormat( DXGI_FORMAT Format );
		void SetViewDimension( D3D11_SRV_DIMENSION ViewDimension );

		void SetBuffer( D3D11_BUFFER_SRV Buffer );
		void SetTexture1D( D3D11_TEX1D_SRV Texture1D );
		void SetTexture1DArray( D3D11_TEX1D_ARRAY_SRV Texture1DArray );
		void SetTexture2D( D3D11_TEX2D_SRV Texture2D );
		void SetTexture2DArray( D3D11_TEX2D_ARRAY_SRV Texture2DArray );
		void SetTexture2DMS( D3D11_TEX2DMS_SRV Texture2DMS );
		void SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_SRV Texture2DMSArray );
		void SetTexture3D( D3D11_TEX3D_SRV Texture3D );
		void SetTextureCube( D3D11_TEXCUBE_SRV TextureCbue );
		void SetTextureCubeArray( D3D11_TEXCUBE_ARRAY_SRV TextureCubeArray );
		void SetBufferEx( D3D11_BUFFEREX_SRV BufferEx );

		D3D11_BUFFER_SRV& GetBufferRef();
		D3D11_TEX1D_SRV& GetTexture1DRef();
		D3D11_TEX1D_ARRAY_SRV& GetTexture1DArrayRef();
		D3D11_TEX2D_SRV& GetTexture2DRef();
		D3D11_TEX2D_ARRAY_SRV& GetTexture2DArrayRef();
		D3D11_TEX2DMS_SRV& GetTexture2DMSRef();
		D3D11_TEX2DMS_ARRAY_SRV& GetTexture2DMSArrayRef();
		D3D11_TEX3D_SRV& GetTexture3DRef();
		D3D11_TEXCUBE_SRV& GetTextureCubRefe();
		D3D11_TEXCUBE_ARRAY_SRV& GetTextureCubeArrayRef();
		D3D11_BUFFEREX_SRV& GetBufferExRef();

		D3D11_SHADER_RESOURCE_VIEW_DESC& GetDesc();

	protected:
		D3D11_SHADER_RESOURCE_VIEW_DESC m_State;

		friend class Renderer;
	};
}

#endif