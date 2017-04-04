#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/ObjectWriter/UnorderedAccessParameterWriter.h"

using namespace Sand;

UnorderedAccessParameterWriter::UnorderedAccessParameterWriter()
{

}

UnorderedAccessParameterWriter::~UnorderedAccessParameterWriter()
{

}

void UnorderedAccessParameterWriter::SetRenderParameterRef( UnorderedAccessParameter* pParam )
{
	m_pParameter = pParam;
}

void UnorderedAccessParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetUnorderedAccessParameterData( m_pParameter , m_Value );
}

void UnorderedAccessParameterWriter::InitializeParameter()
{
	int ResourceID = m_Value->GetResourceID();
	m_pParameter->SetParameterData( &ResourceID );
}

RenderParameter* UnorderedAccessParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void UnorderedAccessParameterWriter::SetValue( ResourceProxyPtr Value )
{
	m_Value = Value;
}

void UnorderedAccessParameterWriter::SetInitCount( int Count )
{
	m_iCount = Count;
}