#include "PCH.h"
#include "ViewPort.h"

using namespace Sand;

ViewPort::ViewPort()
{
	m_ViewPort.Width = 1.0f;
	m_ViewPort.Height = 1.0f;
	m_ViewPort.TopLeftX = 0.0f;
	m_ViewPort.TopLeftY = 0.0f;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
}

ViewPort::ViewPort( D3D11_VIEWPORT viewport )
{
	m_ViewPort = viewport;
}

ViewPort::~ViewPort()
{

}

float ViewPort::GetWidth() const
{
	return m_ViewPort.Width;
}

float ViewPort::GetHeight() const
{
	return m_ViewPort.Height;
}

Vector2f ViewPort::GetScreenSpacePosition( const Vector2f& clip ) const
{
	/*
		http://lonelywaiting.github.io/clip%20and%20screen%20space/
	*/
	return( Vector2f( ( clip.x / 2.0f + 0.5f ) * m_ViewPort.Width ,
		( -clip.y / 2.0f + 0.5f ) * m_ViewPort.Height ) );
}

Vector2f ViewPort::GetClipSpacePosition( const Vector2f& screen ) const
{
	/*
		http://lonelywaiting.github.io/clip%20and%20screen%20space/
	*/
	return( Vector2f( ( ( screen.x / m_ViewPort.Width ) - 0.5f ) * 2.0f ,
		-( ( screen.y / m_ViewPort.Height ) - 0.5f ) * 2.0f ) );
}