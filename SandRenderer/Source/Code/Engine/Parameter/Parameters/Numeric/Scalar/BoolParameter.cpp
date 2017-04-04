#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Numeric/Scalar/BoolParameter.h"

using namespace Sand;

BoolParameter::BoolParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	m_Value = false;
}

BoolParameter::BoolParameter( BoolParameter& copy )
	: BaseNumericTypeRenderParameter( copy )
{
	m_Value = copy.m_Value;
}

BoolParameter::~BoolParameter()
{

}

void BoolParameter::SetParameterData( void* pData )
{
	if ( 0 != memcmp( pData , &m_Value , sizeof( bool ) ) )
	{
		m_Identifier++;
		m_Value = *reinterpret_cast< bool* >( pData );
	}
}

const ParameterType BoolParameter::GetParameterType()
{
	return PT_BOOL;
}

bool BoolParameter::GetValue()
{
	return m_Value;
}

void BoolParameter::SetValue( bool value )
{
	m_Value = value;
}