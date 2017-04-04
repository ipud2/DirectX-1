#include <Engine/PCH.h>
#include "Engine/Resource/Texture/Texture2DConfig.h"

using namespace Sand;

Texture2DConfig::Texture2DConfig()
{
	SetDefaults();
}

Texture2DConfig::~Texture2DConfig()
{

}

void Texture2DConfig::SetDefaults()
{
	m_State.Width = 1;
	m_State.Height = 1;
	m_State.MipLevels = 1;
	m_State.ArraySize = 1;
	m_State.MiscFlags = 0;
	m_State.CPUAccessFlags = 0;
	m_State.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	m_State.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_State.SampleDesc.Count = 1;
	m_State.SampleDesc.Quality = 0;
	m_State.Usage = D3D11_USAGE_DEFAULT;
}

void Texture2DConfig::SetDepthBuffer( UINT width , UINT height )
{
	m_State.Width = width;
	m_State.Height = height;
	m_State.MipLevels = 1;
	m_State.ArraySize = 1;
	m_State.MiscFlags = 0;
	m_State.CPUAccessFlags = 0;
	m_State.Format = DXGI_FORMAT_D32_FLOAT;
	m_State.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_State.SampleDesc.Count = 1;
	m_State.SampleDesc.Quality = 0;
	m_State.Usage = D3D11_USAGE_DEFAULT;
}

void Sand::Texture2DConfig::SetColorBuffer( UINT width , UINT height )
{
	m_State.Width = width;
	m_State.Height = height;
	m_State.MipLevels = 1;
	m_State.ArraySize = 1;
	m_State.MiscFlags = 0;
	m_State.CPUAccessFlags = 0;
	m_State.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	m_State.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_State.SampleDesc.Count = 1;
	m_State.SampleDesc.Quality = 0;
	m_State.Usage = D3D11_USAGE_DEFAULT;
}

void Sand::Texture2DConfig::SetWidth( UINT state )
{
	m_State.Width = state;
}

void Sand::Texture2DConfig::SetHeight( UINT state )
{
	m_State.Height = state;
}

void Sand::Texture2DConfig::SetMipLevels( UINT state )
{
	m_State.MipLevels = state;
}

void Sand::Texture2DConfig::SetArraySize( UINT state )
{
	m_State.ArraySize = state;
}

void Sand::Texture2DConfig::SetFormat( DXGI_FORMAT state )
{
	m_State.Format = state;
}

void Sand::Texture2DConfig::SetUsage( D3D11_USAGE state )
{
	m_State.Usage = state;
}

void Sand::Texture2DConfig::SetBindFlags( UINT state )
{
	m_State.BindFlags = state;
}

void Sand::Texture2DConfig::SetCPUAccessFlags( UINT state )
{
	m_State.CPUAccessFlags = state;
}

void Sand::Texture2DConfig::SetMiscFlags( UINT state )
{
	m_State.MiscFlags = state;
}

void Sand::Texture2DConfig::SetSampleDesc( DXGI_SAMPLE_DESC state )
{
	m_State.SampleDesc.Count = state.Count;
	m_State.SampleDesc.Quality = state.Quality;
}

DXGI_FORMAT Texture2DConfig::GetFormat()
{
	return m_State.Format;
}

UINT Texture2DConfig::GetArraySize()
{
	return m_State.ArraySize;
}

UINT Texture2DConfig::GetMipLevels()
{
	return m_State.MipLevels;
}

UINT Texture2DConfig::GetHeight()
{
	return m_State.Height;
}

UINT Texture2DConfig::GetWidth()
{
	return m_State.Width;
}

D3D11_USAGE Texture2DConfig::GetUsage()
{
	return m_State.Usage;
}

UINT Texture2DConfig::GetBindFlags()
{
	return m_State.BindFlags;
}

UINT Texture2DConfig::GetCPUAccessFlags()
{
	return m_State.CPUAccessFlags;
}

UINT Texture2DConfig::GetMiscFlags()
{
	return m_State.MiscFlags;
}

DXGI_SAMPLE_DESC Texture2DConfig::GetSampleDesc()
{
	return m_State.SampleDesc;
}

D3D11_TEXTURE2D_DESC Sand::Texture2DConfig::GetTextureDesc()
{
	return m_State;
}