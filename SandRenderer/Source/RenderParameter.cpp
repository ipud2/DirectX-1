#include "PCH.h"
#include "RenderParameter.h"

using namespace Sand;

RenderParameter::RenderParameter()
{

}

RenderParameter::RenderParameter( RenderParameter & copy )
{
	m_Name = copy.m_Name;
}

RenderParameter::~RenderParameter()
{

}

void RenderParameter::SetName( const std::wstring & name )
{
	m_Name = name;
}

std::wstring& RenderParameter::GetName()
{
	return m_Name;
}

void RenderParameter::InitializeParameterData( void* pData )
{
	SetParameterData( pData );
}