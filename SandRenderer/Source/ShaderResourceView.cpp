#include "ShaderResoruceView.h"

using namespace Sand;

ShaderResourceView::ShaderResourceView( ID3D11ShaderResourceView* pShaderResourceView )
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