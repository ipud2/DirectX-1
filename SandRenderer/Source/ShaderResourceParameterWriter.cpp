#include "PCH.h"
#include "ShaderResourceParameterWriter.h"

using namespace Sand;

ShaderResourceParameterWriter::ShaderResourceParameterWriter()
{

}

ShaderResourceParameterWriter::~ShaderResourceParameterWriter()
{

}

void ShaderResourceParameterWriter::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetShaderResourceParameterData( m_pParameter , m_Value );
}

void ShaderResourceParameterWriter::InitializeParameter()
{
	int ResourceID = m_Value->GetResourceID();
	m_pParameter->InitializeParameterData( &ResourceID );
}

RenderParameter* ShaderResourceParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void ShaderResourceParameterWriter::SetRenderParameterRef( ShaderResourceParameter* pParamRef )
{
	m_pParameter = pParamRef;
}

void ShaderResourceParameterWriter::SetValue( ResourceProxyPtr value )
{
	m_Value = value;
}