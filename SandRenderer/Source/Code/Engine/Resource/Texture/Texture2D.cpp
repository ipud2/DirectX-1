#include <Engine/PCH.h>
#include "Engine/Resource/Texture/Texture2D.h"

using namespace Sand;


Sand::Texture2D::Texture2D( Microsoft::WRL::ComPtr<ID3D11Texture2D> pTex )
{
	m_Texture = pTex;

	// Çå¿Õ
	ZeroMemory( &m_DesiredDesc , sizeof( D3D11_TEXTURE2D_DESC ) );
	ZeroMemory( &m_ActualDesc , sizeof( D3D11_TEXTURE2D_DESC ) );
}

Sand::Texture2D::~Texture2D()
{

}

D3D11_TEXTURE2D_DESC Sand::Texture2D::GetActualDescription()
{
	ZeroMemory( &m_ActualDesc , sizeof( D3D11_TEXTURE2D_DESC ) );

	// »ñÈ¡ÃèÊö
	if( m_Texture )
	{
		m_Texture->GetDesc( &m_ActualDesc );
	}

	return m_ActualDesc;
}

D3D11_TEXTURE2D_DESC Sand::Texture2D::GetDesiredDescription()
{
	return m_DesiredDesc;
}

void Sand::Texture2D::SetDesiredDescription( D3D11_TEXTURE2D_DESC Desc )
{
	m_DesiredDesc = Desc;
}

Sand::ResourceType Sand::Texture2D::GetType()
{
	return RT_TEXTURE2D;
}

ID3D11Resource* Sand::Texture2D::GetResource()
{
	return m_Texture.Get();
}
