#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/ScalarWriter/BoolParameterWriter.h"

using namespace Sand;

BoolParameterWriter::BoolParameterWriter()
	:m_Value( false )
{

}

BoolParameterWriter::~BoolParameterWriter()
{

}

RenderParameter* BoolParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void BoolParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetBoolParameterData( m_pParameter , &m_Value );
}

void BoolParameterWriter::InitializeParameter()
{
	m_pParameter->SetParameterData( &m_Value );
}

void BoolParameterWriter::SetValue( const bool& value )
{
	m_Value = value;
}

bool BoolParameterWriter::GetValue()
{
	return m_Value;
}

void BoolParameterWriter::SetRenderParameterRef( BoolParameter* pParam )
{
	m_pParameter = pParam;
}