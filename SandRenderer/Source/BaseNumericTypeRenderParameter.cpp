#include "PCH.h"
#include "BaseNumericTypeRenderParameter.h"

using namespace Sand;

BaseNumericTypeRenderParameter::BaseNumericTypeRenderParameter( std::wstring name )
	:RenderParameter( name )
{
	m_IdentifierChange = 0;
}

BaseNumericTypeRenderParameter::BaseNumericTypeRenderParameter( BaseNumericTypeRenderParameter& copy )
	: RenderParameter( copy )
{

}

BaseNumericTypeRenderParameter::~BaseNumericTypeRenderParameter()
{

}

unsigned int BaseNumericTypeRenderParameter::GetValueID()
{
	return m_IdentifierChange;
}