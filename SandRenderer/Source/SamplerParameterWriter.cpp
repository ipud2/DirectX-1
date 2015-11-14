#include "PCH.h"
#include "SamplerParameterWriter.h"

using namespace Sand;

SamplerParameterWriter::SamplerParameterWriter()
{

}

SamplerParameterWriter::~SamplerParameterWriter()
{

}

void SamplerParameterWriter::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetSamplerStateParameterData( m_pParameter , &m_Value );
}

void SamplerParameterWriter::InitializeParameter()
{
	m_pParameter->InitializeParameterData( &m_Value );
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