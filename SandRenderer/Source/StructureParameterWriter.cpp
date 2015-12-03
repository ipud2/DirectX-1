#include "PCH.h"
#include "StructureParameterWriter.h"

using namespace Sand;

StructureParameterWriter::StructureParameterWriter()
	:	m_pStructureParamter( nullptr ) ,
		m_pData( nullptr )
{

}

StructureParameterWriter::~StructureParameterWriter()
{

}

void StructureParameterWriter::InitializeParameter()
{
	m_pStructureParamter->SetParameterData( m_pData );
}

void StructureParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetStructureParameterData( m_pStructureParamter , m_pData );
}

RenderParameter* StructureParameterWriter::GetRenderParameterRef()
{
	return m_pStructureParamter;
}

void StructureParameterWriter::SetRenderParameterRef( StructureParameter* pParameter )
{
	m_pStructureParamter = pParameter;
}

void StructureParameterWriter::SetValue( char* pData , int Size )
{
	if ( m_pData )
	{
		delete m_pData;
		m_pData = nullptr;
	}

	m_pData = new char[Size];

	memcpy( m_pData , pData , Size );
}