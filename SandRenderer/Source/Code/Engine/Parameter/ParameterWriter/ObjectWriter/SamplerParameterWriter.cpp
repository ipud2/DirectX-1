#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/ObjectWriter/SamplerParameterWriter.h"

using namespace Sand;

SamplerParameterWriter::SamplerParameterWriter()
{
	m_pParameter = nullptr;
	m_Value = -1;
}

SamplerParameterWriter::~SamplerParameterWriter()
{

}

void SamplerParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetSamplerStateParameterData( m_pParameter , &m_Value );
}

void SamplerParameterWriter::InitializeParameter()
{
	m_pParameter->SetParameterData( &m_Value );
}

RenderParameter* SamplerParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void SamplerParameterWriter::SetRenderParameterRef( SamplerParameter* pParamRef )
{
	m_pParameter = pParamRef;
}

void SamplerParameterWriter::SetValue( int Value )
{
	m_Value = Value;
}