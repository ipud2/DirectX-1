#ifndef ShaderResourceView_h
#define ShaderResourceView_h

#include "PCH.h"

namespace Sand
{
	class ShaderResourceView
	{
	public:
		ShaderResourceView( ID3D11ShaderResourceView* pShaderResourceView );
		virtual ~ShaderResourceView();

		ID3D11ShaderResourceView* Get();

	protected:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;

		friend class Renderer;
	};
};

#endif