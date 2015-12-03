#include "PCH.h"
#include "BasicSurfaceProperty.h"

using namespace Sand;


BasicSurfaceProperty::BasicSurfaceProperty()
	:m_pData( nullptr )
{
	m_pData = new BasicSurfacePropertyStructure;

	// ÓÃÓÚ²âÊÔ
	m_pData->AmbientMaterial = Vector4f( 0.5f , 0.5f , 0.5f , 1.0f );

	m_pData->DiffuseMaterial = Vector4f( 1.0f , 1.0f , 1.0f , 1.0f );

	m_pData->SpecularMaterial = Vector4f( 0.6f , 0.6f , 0.6f , 16.0f );

	m_pSurfacePropertyStructureWriter = Parameters.SetValueToStructureParameterWriter( L"BasicSurfaceProperty" , reinterpret_cast< char* >( m_pData ) , sizeof( BasicSurfacePropertyStructure ) );

	

	m_pSurfacePropertyStructureWriter->SetValue( reinterpret_cast< char* >( m_pData ) , sizeof( BasicSurfacePropertyStructure ) );
}

BasicSurfaceProperty::~BasicSurfaceProperty()
{
	
}

void BasicSurfaceProperty::SetSurfaceProperty( const Vector4f& AmbientMaterial , const Vector4f& DiffuseMaterial , const Vector4f& SpecularMaterial )
{
	m_pData->AmbientMaterial = AmbientMaterial;

	m_pData->DiffuseMaterial = DiffuseMaterial;

	m_pData->SpecularMaterial = SpecularMaterial;

	m_pSurfacePropertyStructureWriter->SetValue( reinterpret_cast< char* >( m_pData ) , sizeof( BasicSurfacePropertyStructure ) );
}