#ifndef RenderTargetView_h
#define RenderTargetView_h

#include <Engine/PCH.h>

namespace Sand
{
	class RenderTargetView
	{
	public:
		RenderTargetView( Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView );
		virtual ~RenderTargetView();

		ID3D11RenderTargetView* GetRenderTargetView();

	protected:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		friend class Renderer;
	};
};
#endif