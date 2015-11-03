#ifndef RenderTargetView_h
#define RenderTargetView_h

#include "PCH.h"

namespace Sand
{
	class RenderTargetView
	{
	public:
		RenderTargetView( ID3D11RenderTargetView* pRenderTargetView );
		virtual ~RenderTargetView();

		ID3D11RenderTargetView* Get();

	protected:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		friend class RenderTargetView;
	};
};

#endif