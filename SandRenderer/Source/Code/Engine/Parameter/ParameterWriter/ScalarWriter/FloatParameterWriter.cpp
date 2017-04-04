#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/ScalarWriter/FloatParameterWriter.h"

using namespace Sand;

FloatParameterWriter::FloatParameterWriter()
	:m_Value( 0.0f )
{

}

FloatParameterWriter::~FloatParameterWriter()
{

}

RenderParameter* FloatParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void FloatParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetFloatParameterData( m_pParameter , &m_Value );
}

void FloatParameterWriter::InitializeParameter()
{
	m_pParameter->SetParameterData( &m_Value );
}

void FloatParameterWriter::SetValue( const float& value )
{
	m_Value = value;
}

float FloatParameterWriter::GetValue()
{
	return m_Value;
}

void FloatParameterWriter::SetRenderParameterRef( FloatParameter* pParam )
{
	m_pParameter = pParam;
}