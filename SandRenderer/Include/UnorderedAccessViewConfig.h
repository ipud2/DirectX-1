#ifndef UnorderedAccessViewConfig_h
#define UnorderedAccessViewConfig_h

#include "PCH.h"

namespace Sand
{
	/*
		struct D3D11_UNORDERED_ACCESS_VIEW_DESC
		{
			DXGI_FORMAT Format;
			D3D11_UAV_DIMENSION ViewDimension;
				
			union
			{
				D3D11_BUFFER_UAV Buffer;
				D3D11_TEX1D_UAV Texture1D;
				D3D11_TEX1D_ARRAY_UAV Texture1DArray;
				D3D11_TEX2D_UAV Texture2D;
				D3D11_TEX2D_ARRAY_UAV Texture2DArray;
				D3D11_TEX3D_UAV Texture3D;
			};
		};
	*/
	class UnorderedAccessViewConfig
	{
	public:
		UnorderedAccessViewConfig();
		virtual ~UnorderedAccessViewConfig();

		//************************************
		// Method:    SetDefaults
		// FullName:  Sand::UnorderedAccessViewConfig::SetDefaults
		// Access:    public 
		// Returns:   void
		// Qualifier: ´´½¨Ä¬ÈÏUnorderedAccessViewÃèÊö
		//************************************
		void SetDefaults();

		void SetFormat( DXGI_FORMAT Format );
		void SetViewDimension( D3D11_UAV_DIMENSION ViewDimension );

		void SetBuffer( D3D11_BUFFER_UAV Buffer );
		void SetTexture1D( D3D11_TEX1D_UAV Texture1D );
		void SetTexture1DArray( D3D11_TEX1D_ARRAY_UAV Texture1DArray );
		void SetTexture2D( D3D11_TEX2D_UAV Texture2D );
		void SetTexture2DArray( D3D11_TEX2D_ARRAY_UAV Texture2DArray );
		void SetTexture3D( D3D11_TEX3D_UAV Texture3D );

		D3D11_UNORDERED_ACCESS_VIEW_DESC& GetDesc();
		
	protected:
		D3D11_UNORDERED_ACCESS_VIEW_DESC m_State;

		friend class Renderer;
	};
};
#endif