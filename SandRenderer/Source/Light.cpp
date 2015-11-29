#include "PCH.h"
#include "Light.h"

using namespace Sand;

Light::Light()
	:LightParameters() ,
	m_DiffuseWriter( nullptr ) ,
	m_AmbientWriter( nullptr ) ,
	m_SpecularWriter( nullptr )
{
	m_AmbientWriter = LightParameters.SetValueToVectorParameterWriter( L"AmbientLight" , Vector4f( 0.25f , 0.25f , 0.25f , 0.25f ) );
	m_DiffuseWriter = LightParameters.SetValueToVectorParameterWriter( L"DiffuseLight" , Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) );
	m_SpecularWriter = LightParameters.SetValueToVectorParameterWriter( L"SpecularLight" , Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) );
}

Light::~Light()
{

}

void Light::SetDiffuse( const Vector4f& Value )
{
	m_DiffuseWriter->SetValue( Value );
}

void Light::SetAmbient( const Vector4f& Value )
{
	m_AmbientWriter->SetValue( Value );
}

void Light::SetSpecular( const Vector4f& Value )
{
	m_SpecularWriter->SetValue( Value );
}

Vector4f Light::GetDiffuse() const
{
	return m_DiffuseWriter->GetValue();
}

Vector4f Light::GetAmbient() const
{
	return m_AmbientWriter->GetValue();
}

Vector4f Light::GetSpecular() const
{
	return m_SpecularWriter->GetValue();
}

void Light::SetRenderParams( IParameterManager* pParamMgr )
{
	LightParameters.SetRenderParams( pParamMgr );
}