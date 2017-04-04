#ifndef ViewPort_h
#define ViewPort_h

#include <Engine/PCH.h>
#include "Engine/Math/Vector2f.h"

namespace Sand
{
	/*
		封装了D3D11_VIEWPORT对象
		并提供了一些GetXXX()函数，用于获取属性
	*/
	class ViewPort
	{
	public:
		ViewPort();
		ViewPort( D3D11_VIEWPORT viewport );
		virtual ~ViewPort();

		float GetWidth() const;
		float GetHeight() const;
		Vector2f GetClipSpacePosition( const Vector2f& screen ) const;
		Vector2f GetScreenSpacePosition( const Vector2f& clip ) const;

	protected:
		D3D11_VIEWPORT m_ViewPort;

		friend class Renderer;
		friend class RasterizerStage;
	};
};
#endif