#ifndef DepthStencilViewConfig_h
#define DepthStencilViewConfig_h

#include <Engine/PCH.h>

namespace Sand
{

	/*
		struct D3D11_DEPTH_STENCIL_VIEW_DESC
		{
			DXGI_FORMAT Format;
			D3D11_DSV_DIMENSION ViewDimension;
			UINT Flags;
			
			union
			{
				D3D11_TEX1D_DSV Texture1D;
				D3D11_TEX1D_ARRAY_DSV Texture1DArray;
				D3D11_TEX2D_DSV Texture2D;
				D3D11_TEX2D_ARRAY_DSV Texture2DArray;
				D3D11_TEX2DMS_DSV Texture2DMS;
				D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray;
			};
		};
	*/
	class DepthStencilViewConfig
	{
	public:
		DepthStencilViewConfig();
		virtual ~DepthStencilViewConfig();

		//************************************
		// Method:    SetDefaults
		// FullName:  Sand::DepthStencilViewConfig::SetDefaults
		// Access:    public 
		// Returns:   void
		// Qualifier: …Ë÷√ƒ¨»œµƒDepthStencilView√Ë ˆ
		//************************************
		void SetDefaults();

		void SetFormat( DXGI_FORMAT state );
		void SetViewDimensions( D3D11_DSV_DIMENSION state );
		void SetFlags( UINT state );

		void SetTexture1D( D3D11_TEX1D_DSV Texture1D );
		void SetTexture1DArray( D3D11_TEX1D_ARRAY_DSV Texture1DArray );
		void SetTexture2D( D3D11_TEX2D_DSV Texture2D );
		void SetTexture2DArray( D3D11_TEX2D_ARRAY_DSV Texture2DArray );
		void SetTexture2DMS( D3D11_TEX2DMS_DSV Texture2DMS );
		void SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray );

		D3D11_TEX1D_DSV& GetTexture1DRef();
		D3D11_TEX1D_ARRAY_DSV& GetTexture1DArrayRef();
		D3D11_TEX2D_DSV& GetTexture2DRef();
		D3D11_TEX2D_ARRAY_DSV& GetTexture2DArrayRef();
		D3D11_TEX2DMS_DSV& GetTexture2DMSRef();
		D3D11_TEX2DMS_ARRAY_DSV& GetTexture2DMSArray();

		D3D11_DEPTH_STENCIL_VIEW_DESC& GetDesc();
		
	protected:
		D3D11_DEPTH_STENCIL_VIEW_DESC m_State;

		friend class Renderer;
	};
};
#endif