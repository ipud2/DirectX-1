#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/ObjectWriter/ShaderResourceParameterWriter.h"

using namespace Sand;

ShaderResourceParameterWriter::ShaderResourceParameterWriter()
{

}

ShaderResourceParameterWriter::~ShaderResourceParameterWriter()
{

}

void ShaderResourceParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetShaderResourceParameterData( m_pParameter , m_Value );
}

void ShaderResourceParameterWriter::InitializeParameter()
{
	int ResourceID = m_Value->GetResourceID();
	m_pParameter->SetParameterData( &ResourceID );
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