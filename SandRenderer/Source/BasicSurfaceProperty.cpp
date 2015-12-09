#include "PCH.h"
#include "BasicSurfaceProperty.h"

using namespace Sand;


BasicSurfaceProperty::BasicSurfaceProperty()
	:m_pData( nullptr )
{
	// 创建StructureParameterWriter对象
	m_pSurfacePropertyStructureWriter = Parameters.GetStructureParameterWriter( L"BasicSurfaceProperty" , sizeof( BasicSurfacePropertyStructure ) );

	m_pData = new BasicSurfacePropertyStructure;
}

BasicSurfaceProperty::~BasicSurfaceProperty()
{
	
}

void BasicSurfaceProperty::SetSurfaceProperty( const Vector4f& AmbientMaterial , const Vector4f& DiffuseMaterial , const Vector4f& SpecularMaterial , const Vector4f& Reflect )
{
	m_pData->AmbientMaterial = AmbientMaterial;

	m_pData->DiffuseMaterial = DiffuseMaterial;

	m_pData->SpecularMaterial = SpecularMaterial;

	m_pData->ReflectMaterial = Reflect;

	m_pSurfacePropertyStructureWriter->SetValue( reinterpret_cast< char* >( m_pData ) , sizeof( BasicSurfacePropertyStructure ) );
}