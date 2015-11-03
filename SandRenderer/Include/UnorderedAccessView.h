#ifndef UnorderedAccessView_h
#define UnorderedAccessView_h

#include "PCH.h"

namespace Sand
{
	class UnorderedAccessView
	{
	public:
		UnorderedAccessView( ID3D11UnorderedAccessView* pUnorderedAccessView );
		virtual ~UnorderedAccessView();

		ID3D11UnorderedAccessView* Get();

	protected:
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_UnorderedAccessView;

		friend class Renderer;
	};
}

#endif