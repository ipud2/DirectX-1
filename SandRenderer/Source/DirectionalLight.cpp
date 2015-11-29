#include "PCH.h"
#include "DirectionalLight.h"

using namespace Sand;

DirectionalLight::DirectionalLight()
	:m_pLightDirectionWriter(nullptr)
{
	m_pLightDirectionWriter = LightParameters.SetValueToVectorParameterWriter( L"LightDirection" , Vector4f( 0.707f , -0.707f , 0.0f , 1.0f ) );
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::SetLightDirection( const Vector4f& value )
{
	m_pLightDirectionWriter->SetValue( value );
}