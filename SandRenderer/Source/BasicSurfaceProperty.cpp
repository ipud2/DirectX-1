#include "PCH.h"
#include "BasicSurfaceProperty.h"

using namespace Sand;


BasicSurfaceProperty::BasicSurfaceProperty()
{
	m_pAmbientMaterialWriter = Parameters.SetValueToVectorParameterWriter( L"AmbientMaterial" , Vector4f( 0.5f , 0.5f , 0.5f , 1.0f ) );
	m_pDiffuseMaterialWriter = Parameters.SetValueToVectorParameterWriter( L"DiffuseMaterial" , Vector4f( 1.0f , 1.0f , 1.0f , 1.0f ) );
	m_pSpecularMaterialWriter = Parameters.SetValueToVectorParameterWriter( L"SpecularMaterial" , Vector4f( 0.6f , 0.6f , 0.6f , 16.0f ) );
}

BasicSurfaceProperty::~BasicSurfaceProperty()
{
	m_pAmbientMaterialWriter = nullptr;
	m_pDiffuseMaterialWriter = nullptr;
	m_pSpecularMaterialWriter = nullptr;
}

void BasicSurfaceProperty::SetSurfaceAmbientProperty( const Vector4f& value )
{
	m_pAmbientMaterialWriter->SetValue( value );
}

void BasicSurfaceProperty::SetSurfaceDiffuseProperty( const Vector4f& value )
{
	m_pDiffuseMaterialWriter->SetValue( value );
}

void BasicSurfaceProperty::SetSurfaceSpecularProperty( const Vector4f& value )
{
	m_pSpecularMaterialWriter->SetValue( value );
}