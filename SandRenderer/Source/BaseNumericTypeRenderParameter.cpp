#include "PCH.h"
#include "BaseNumericTypeRenderParameter.h"

using namespace Sand;

BaseNumericTypeRenderParameter::BaseNumericTypeRenderParameter()
{
	m_IdentifierChange = 0;
}

BaseNumericTypeRenderParameter::BaseNumericTypeRenderParameter( BaseNumericTypeRenderParameter& copy )
{

}

BaseNumericTypeRenderParameter::~BaseNumericTypeRenderParameter()
{

}

unsigned int BaseNumericTypeRenderParameter::GetValueID()
{
	return m_IdentifierChange;
}