#include <Engine/PCH.h>
#include "SwapChainConfig.h"

using namespace Sand;

SwapChainConfig::SwapChainConfig()
{
	SetDefaults();
}

SwapChainConfig::~SwapChainConfig()
{

}

void SwapChainConfig::SetDefaults()
{
	m_State.BufferDesc.Width = 1;
	m_State.BufferDesc.Height = 1;
	m_State.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_State.BufferDesc.RefreshRate.Numerator = 60;		// 默认60帧
	m_State.BufferDesc.RefreshRate.Denominator = 1;
	m_State.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// 未指定
	m_State.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 未指定

	m_State.BufferCount = 2;

	m_State.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 如果要创建全屏Swap Chain的话，可能需要指定Flags为DXGI_SWAP_CHAIN_FLAG_MODE_SWITCH
	m_State.Flags = 0;

	m_State.OutputWindow = 0;

	m_State.SampleDesc.Count = 1;
	m_State.SampleDesc.Quality = 0;

	m_State.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	m_State.Windowed = true;
}

void SwapChainConfig::SetWidth( UINT width )
{
	m_State.BufferDesc.Width = width;
}

void SwapChainConfig::SetHeight( UINT height )
{
	m_State.BufferDesc.Height = height;
}

void SwapChainConfig::SetScanlineOrder( DXGI_MODE_SCANLINE_ORDER ScanlinOrdering )
{
	m_State.BufferDesc.ScanlineOrdering = ScanlinOrdering;
}

void SwapChainConfig::SetFormat( DXGI_FORMAT Format )
{
	m_State.BufferDesc.Format = Format;
}

void SwapChainConfig::SetRefreshRateNumerator( UINT numerator )
{
	m_State.BufferDesc.RefreshRate.Numerator = numerator;
}

void SwapChainConfig::SetRefreshRataDenominator( UINT denominator )
{
	m_State.BufferDesc.RefreshRate.Denominator = denominator;
}

void SwapChainConfig::SetScaling( DXGI_MODE_SCALING Scaling )
{
	m_State.BufferDesc.Scaling = Scaling;
}

void SwapChainConfig::SetBufferDesc( DXGI_MODE_DESC BufferDesc )
{
	m_State.BufferDesc = BufferDesc;
}

void SwapChainConfig::SetBufferCount( UINT BufferCount )
{
	m_State.BufferCount = BufferCount;
}

void SwapChainConfig::SetBufferUsage( DXGI_USAGE BufferUsage )
{
	m_State.BufferUsage = BufferUsage;
}

void SwapChainConfig::SetOutputWindow( HWND OutputWindow )
{
	m_State.OutputWindow = OutputWindow;
}

void SwapChainConfig::SetSampleDesc( DXGI_SAMPLE_DESC SampleDesc )
{
	m_State.SampleDesc = SampleDesc;
}

void SwapChainConfig::SetSwapEffect( DXGI_SWAP_EFFECT SwapEffect )
{
	m_State.SwapEffect = SwapEffect;
}

void SwapChainConfig::SetWindowed( bool Windowed )
{
	m_State.Windowed = Windowed;
}

void SwapChainConfig::SetFlags( UINT Flags )
{
	m_State.Flags = Flags;
}

DXGI_SWAP_CHAIN_DESC SwapChainConfig::GetSwapChainDesc()
{
	return m_State;
}