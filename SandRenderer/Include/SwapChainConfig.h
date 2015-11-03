#ifndef SwapChainConfig_h
#define SwapChainConfig_h

#include "PCH.h"

namespace Sand
{
	/*
		DXGI_MODE_DESC BufferDesc;
		{
			UINT Width;
			UINT Height;
			DXGI_RATIONAL RefreshRate;
			{
				UINT Numerator;
				UINT Denominator;
			}
			DXGI_FORMAT Format;
			DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
			DXGI_MODE_SCALING Scaling;
		}

		DXGI_SAMPLE_DESC SampleDesc
		{
			UINT Count;
			UINT Quality;
		}

		DXGI_USAGE BufferUsage;
		UINT BufferCount;
		HWND OutputWindow;
		BOOL Windowed;
		DXGI_SWAP_EFFECT SwapEffect;
		UINT Flags;
	*/
	class SwapChainConfig
	{
	public:
		SwapChainConfig();
		virtual ~SwapChainConfig();

		//************************************
		// Method:    SetDefaults
		// FullName:  Sand::SwapChainConfig::SetDefaults
		// Access:    public 
		// Returns:   void
		// Qualifier: ÃÓ≥‰ƒ¨»œΩªªª¡¥√Ë ˆ
		//************************************
		void SetDefaults();

		// Buffer Desc
		void SetWidth( UINT width );
		void SetHeight( UINT height );
		void SetRefreshRateNumerator( UINT numerator );
		void SetRefreshRataDenominator( UINT denominator );
		void SetFormat( DXGI_FORMAT Format );
		void SetScanlineOrder( DXGI_MODE_SCANLINE_ORDER ScanlineOrdering );
		void SetScaling( DXGI_MODE_SCALING Scaling );

		void SetBufferDesc( DXGI_MODE_DESC BufferDesc );
		void SetSampleDesc( DXGI_SAMPLE_DESC SampleDesc );
		void SetBufferUsage( DXGI_USAGE BufferUsage );
		void SetBufferCount( UINT BufferCount );
		void SetOutputWindow( HWND OutputWindow );
		void SetWindowed( bool Windowed );
		void SetSwapEffect( DXGI_SWAP_EFFECT SwapEffect );
		void SetFlags( UINT Flags );

		DXGI_SWAP_CHAIN_DESC GetSwapChainDesc();

	protected:
		DXGI_SWAP_CHAIN_DESC m_State;

		friend class Renderer;
	};
};

#endif