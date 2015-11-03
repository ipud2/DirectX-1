#ifndef RenderTargetViewConfig_h
#define RenderTargetViewConfig_h

#include "PCH.h"

namespace Sand
{
	/*
		struct D3D11_RENDER_TARGET_VIEW_DESC
		{
			DXGI_FORMAT Format;
			D3D11_RTV_DIMENSION ViewDimension;

			union
			{
				D3D11_BUFFER_RTV Buffer;
				D3D11_TEX1D_RTV Texture1D;
				D3D11_TEX1D_ARRAY_RTV Texture1DArray;
				D3D11_TEX2D_RTV Texture2D;
				D3D11_TEX2D_ARRAY_RTV Texture2DArray;
				D3D11_TEX2DMS_RTV Texture2DMS;
				D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray;
				D3D11_TEX3D_RTV Texture3D;
			};
		}
	*/
	class RenderTargetViewConfig
	{
	public:
		RenderTargetViewConfig();
		virtual ~RenderTargetViewConfig();

		//************************************
		// Method:    SetDefaults
		// FullName:  Sand::RenderTargetViewConfig::SetDefaults
		// Access:    public 
		// Returns:   void
		// Qualifier: …Ë÷√ƒ¨»œµƒRenderTargetView√Ë ˆ
		//************************************
		void SetDefaults();

		void SetFormat( DXGI_FORMAT Format );
		void SetViewDimension( D3D11_RTV_DIMENSION ViewDimension );

		void SetBuffer( D3D11_BUFFER_RTV Buffer );
		void SetTexture1D( D3D11_TEX1D_RTV Texture1D );
		void SetTexture1DArray( D3D11_TEX1D_ARRAY_RTV Texture1DArray );
		void SetTexture2D( D3D11_TEX2D_RTV Texture2D );
		void SetTexture2DArray( D3D11_TEX2D_ARRAY_RTV Texture2DArray );
		void SetTexture2DMS( D3D11_TEX2DMS_RTV Texture2DMS );
		void SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray );
		void SetTexture3D( D3D11_TEX3D_RTV Texture3D );

		D3D11_RENDER_TARGET_VIEW_DESC& GetDesc();

	protected:
		D3D11_RENDER_TARGET_VIEW_DESC m_State;

		friend class Renderer;
	};
}

#endif