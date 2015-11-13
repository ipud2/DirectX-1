#include "PCH.h"
#include "MatrixParameterWriter.h"

using namespace Sand;

MatrixParameterWriter::MatrixParameterWriter()
{
	m_Value.MakeIdentity();
}

MatrixParameterWriter::~MatrixParameterWriter()
{

}

void MatrixParameterWriter::SetRenderParameterRef( MatrixParameter* pParam )
{
	m_pParameter = pParam;
}

void MatrixParameterWriter::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetMatrixParameterData( m_pParameter , &m_Value );
}

void MatrixParameterWriter::InitializeParameter()
{
	m_pParameter->InitializeParameterData( &m_Value );
}

RenderParameter* MatrixParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void MatrixParameterWriter::SetValue( const Matrix4f& value )
{
	m_Value = value;
}

Matrix4f MatrixParameterWriter::GetValue()
{
	return m_Value;
}