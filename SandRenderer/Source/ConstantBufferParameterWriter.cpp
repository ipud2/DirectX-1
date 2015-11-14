#include "PCH.h"
#include "ConstantBufferParameterWriter.h"

using namespace Sand;

ConstantBufferParameterWriter::ConstantBufferParameterWriter()
{
	
}

ConstantBufferParameterWriter::~ConstantBufferParameterWriter()
{

}

void ConstantBufferParameterWriter::SetRenderParameterRef( ConstantBufferParameter* pParam )
{
	m_pParameter = pParam;
}

void ConstantBufferParameterWriter::SetValue( ResourceProxyPtr Value )
{
	m_Value = Value;
}

void ConstantBufferParameterWriter::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetConstantBufferParameterData( m_pParameter , m_Value );
}

void ConstantBufferParameterWriter::InitializeParameter()
{
	int ResourceID = m_Value->GetResourceID();
	m_pParameter->InitializeParameterData( &ResourceID );
}

RenderParameter* ConstantBufferParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}