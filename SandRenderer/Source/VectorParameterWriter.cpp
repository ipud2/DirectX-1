#include "PCH.h"
#include "VectorParameterWriter.h"

using namespace Sand;

VectorParameterWriter::VectorParameterWriter()
	:m_Value( 0.0f , 0.0f , 0.0f , 0.0f )
{

}

VectorParameterWriter::~VectorParameterWriter()
{

}

RenderParameter* VectorParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void VectorParameterWriter::InitializeParameter()
{
	m_pParameter->InitializeParameterData( &m_Value );
}

void VectorParameterWriter::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetVectorParameterData( m_pParameter , &m_Value );
}

void VectorParameterWriter::SetValue( const Vector4f& Value )
{
	m_Value = Value;
}

Vector4f VectorParameterWriter::GetValue()
{
	return m_Value;
}

void VectorParameterWriter::SetRenderParameterRef( VectorParameter* pParam )
{
	m_pParameter = pParam;
}