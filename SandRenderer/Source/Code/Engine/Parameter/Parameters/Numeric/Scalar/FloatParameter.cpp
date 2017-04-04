#include <Engine/PCH.h>
#include "Engine/Parameter/Parameters/Numeric/Scalar/FloatParameter.h"

using namespace Sand;

FloatParameter::FloatParameter( std::wstring name )
	:BaseNumericTypeRenderParameter( name )
{
	m_Value = 0;
}

FloatParameter::FloatParameter( FloatParameter& copy )
	: BaseNumericTypeRenderParameter( copy )
{
	m_Value = copy.m_Value;
}

FloatParameter::~FloatParameter()
{

}

void FloatParameter::SetParameterData( void* pData )
{
	if ( 0 != memcmp( pData , &m_Value , sizeof( float ) ) )
	{
		// 非0表示是不一样的数据
		m_Identifier++;
		m_Value = *reinterpret_cast< float* >( pData );
	}
}

const ParameterType FloatParameter::GetParameterType()
{
	return PT_FLOAT;
}

float FloatParameter::GetValue()
{
	return m_Value;
}

void FloatParameter::SetValue( float value )
{
	m_Value = value;
}