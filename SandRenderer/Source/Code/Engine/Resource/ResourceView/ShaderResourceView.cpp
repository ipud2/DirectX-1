#include <Engine/PCH.h>
#include "Engine/Resource/ResourceView/ShaderResoruceView.h"

using namespace Sand;

ShaderResourceView::ShaderResourceView( Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView )
{
	m_ShaderResourceView = pShaderResourceView;
}

ShaderResourceView::~ShaderResourceView()
{

}

ID3D11ShaderResourceView* ShaderResourceView::Get()
{
	return m_ShaderResourceView.Get();
}