#ifndef Texture2D_h
#define Texture2D_h

#include "Engine/Resource/Resource.h"

namespace Sand
{
	class Texture2D : public Resource
	{
	public:
		Texture2D( Microsoft::WRL::ComPtr<ID3D11Texture2D> pTex );
		virtual ~Texture2D();

		D3D11_TEXTURE2D_DESC GetActualDescription();
		D3D11_TEXTURE2D_DESC GetDesiredDescription();
		void SetDesiredDescription( D3D11_TEXTURE2D_DESC Desc );

		virtual ResourceType GetType();
		virtual ID3D11Resource* GetResource();

	protected:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;

		D3D11_TEXTURE2D_DESC m_DesiredDesc;
		D3D11_TEXTURE2D_DESC m_ActualDesc;

		friend class Renderer;
	};
}

#endif