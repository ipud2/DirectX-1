#ifndef ViewPort_h
#define ViewPort_h

#include <Engine/PCH.h>
#include "Engine/Math/Vector2f.h"

namespace Sand
{
	/*
		��װ��D3D11_VIEWPORT����
		���ṩ��һЩGetXXX()���������ڻ�ȡ����
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