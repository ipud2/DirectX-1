#include "PCH.h"
#include "RenderParameter.h"

using namespace Sand;

RenderParameter::RenderParameter( std::wstring name )
{
	m_Name = name;
}

RenderParameter::RenderParameter( RenderParameter & copy )
{
	m_Name = copy.m_Name;
}

RenderParameter::~RenderParameter()
{

}

std::wstring& RenderParameter::GetName()
{
	return m_Name;
}