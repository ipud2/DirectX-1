#include "PCH.h"
#include "BaseNumericTypeRenderParameter.h"

using namespace Sand;

BaseNumericTypeRenderParameter::BaseNumericTypeRenderParameter( std::wstring name )
	:RenderParameter( name )
{
	m_Identifier = 0;
}

BaseNumericTypeRenderParameter::BaseNumericTypeRenderParameter( BaseNumericTypeRenderParameter& copy )
	: RenderParameter( copy )
{

}

BaseNumericTypeRenderParameter::~BaseNumericTypeRenderParameter()
{

}

unsigned int BaseNumericTypeRenderParameter::GetIdentifier()
{
	return m_Identifier;
}