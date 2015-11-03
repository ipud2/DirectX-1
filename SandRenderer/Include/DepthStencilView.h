#ifndef DepthStencilView_h
#define DepthStencilView_h

#include "PCH.h"

namespace Sand
{
	class DepthStencilView
	{
	public:
		DepthStencilView( Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView );
		virtual ~DepthStencilView();

		ID3D11DepthStencilView* Get();

	protected:
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;

		friend class DepthStencilView;
	};
}

#endif