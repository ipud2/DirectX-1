#include <Engine/PCH.h>
#include "Engine/Parameter/ParameterWriter/MatrixWriter/MatrixArrayParameterWriter.h"

using namespace Sand;

MatrixArrayParameterWriter::MatrixArrayParameterWriter()
	: m_pValue( nullptr ) ,
	m_iCount( 0 )
{

}

MatrixArrayParameterWriter::~MatrixArrayParameterWriter()
{

}

void MatrixArrayParameterWriter::InitializeParameter()
{
	m_pParameter->SetParameterData( &m_pValue );
}

void MatrixArrayParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetMatrixArrayParameterData( m_pParameter , m_pValue );
}

void MatrixArrayParameterWriter::SetRenderParameterRef( MatrixArrayParameter* pParameter )
{
	m_pParameter = pParameter;
}

void MatrixArrayParameterWriter::SetValue( Matrix4f* pValue , int Count )
{
	m_pValue = pValue;

	m_iCount = Count;
}

RenderParameter* MatrixArrayParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}
